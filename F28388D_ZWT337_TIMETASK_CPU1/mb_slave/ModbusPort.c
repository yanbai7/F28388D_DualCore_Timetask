/*
 * ModbusPort.c
 *
 *  Created on: Mar 4, 2024
 *      Author: cody_chen
 */

#include "ModbusPort.h"
#include "shareram.h"

ST_FIFO sPort  = {
    .pushRcnts = 0,
    .popRcnts = 0,
    .pushTcnts = 0,
    .popTcnts = 0
};

uint16_t setMbusSendByte(SCI_MODBUS *mbus, uint16_t data)
{
    if(MBUS_BUFFER_SIZE > sPort.pushTcnts) {
        sPort.u16RAM[sPort.pushTcnts++] = data;
        return 1;
    }
    return 0;
}

uint16_t getMbusReadByte(SCI_MODBUS *mbus)
{
    if(sPort.popRcnts < sPort.pushRcnts) {
        uint16_t u16Temp = sPort.u16RAM[sPort.popRcnts++];
        if(sPort.popRcnts == sPort.pushRcnts) sPort.popRcnts = sPort.pushRcnts = 0;
        return u16Temp;
    }
    return 0;
}

int16_t getMbusRxSize(SCI_MODBUS *mbus)
{
    return (sPort.pushRcnts != sPort.popRcnts);
}

void pushRxByteToFIFO(SCI_MODBUS *mbus)
{
    if(0<mbus->getRsize(mbus->sci)) {
        uint16_t u16Temp = (mbus->rdfunc(mbus->sci) & 0x00FF);
        sAccessCPU1.u16RAM[sAccessCPU1.pushRcnts++] = u16Temp;
        if(MBUS_BUFFER_SIZE == sAccessCPU1.pushRcnts) sAccessCPU1.pushRcnts = 0;
        sPort.u16RAM[sPort.pushRcnts++] = u16Temp;
    }
}

void popFIFOtoTxData(SCI_MODBUS *mbus)
{

    if(BROADCAST_ID != mbus->rmtSlaveID) {
        if(sPort.popTcnts != sPort.pushTcnts) {
            if(SCI_FIFO_TX16 > mbus->getWsize(mbus->sci)) {
                uint16_t u16Temp = sPort.u16RAM[sPort.popTcnts];
                mbus->wrfunc(mbus->sci, u16Temp);
                sPort.popTcnts++;
                if(sPort.popTcnts == sPort.pushTcnts) sPort.popTcnts = sPort.pushTcnts = 0;
            }
        }

        if(sAccessCPU1.popTcnts != sReadCPU2.pushTcnts) {
            if(SCI_FIFO_TX16 > mbus->getWsize(mbus->sci)) {
                uint16_t u16Temp = sReadCPU2.u16RAM[sAccessCPU1.popTcnts];
                mbus->wrfunc(mbus->sci, u16Temp);
                sAccessCPU1.popTcnts++;
                if(MBUS_BUFFER_SIZE == sAccessCPU1.popTcnts) sAccessCPU1.popTcnts = 0;
            }
        }
    }
    else {
        sPort.popTcnts = sPort.pushTcnts;
        sAccessCPU1.popTcnts = sReadCPU2.pushTcnts;
    }
}


int16_t pollModbusPort(SCI_MODBUS *mbus)
{
    switch(mbus->evPort) {
    case _INIT_SCI_CONFIG:
        if(0 == mbus->sci) return 0;
        SCI_init();
        runModbus(mbus);
        mbus->evPort = _RECEIVE_DATA_FROM_SCI;

    case _RECEIVE_DATA_FROM_SCI:
        pushRxByteToFIFO(mbus);
        popFIFOtoTxData(mbus);
        break;

    default:
        break;
    }

    return mbus->state;
}

