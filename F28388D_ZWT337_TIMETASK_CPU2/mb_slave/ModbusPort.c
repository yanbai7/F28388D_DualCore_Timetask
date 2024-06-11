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
    sPort.u16RAM[sPort.pushTcnts++] = data;
    if(MBUS_BUFFER_SIZE == sPort.pushTcnts) sPort.pushTcnts = 0;
    return 1;
}

int16_t getMbusRxSize(SCI_MODBUS *mbus)
{
    return (sPort.pushRcnts != sPort.popRcnts);
}


uint16_t getMbusReadByte(SCI_MODBUS *mbus)
{
    uint16_t u16Temp = sPort.u16RAM[sPort.popRcnts++];
    if(MBUS_BUFFER_SIZE == sPort.popRcnts) sPort.popRcnts = 0;
    return u16Temp;
}
void pushRxByteToFIFO(SCI_MODBUS *mbus)
{
    if(0<mbus->getRsize(mbus->sci)) {
        uint16_t u16Temp = (mbus->rdfunc(mbus->sci) & 0x00FF);
        sPort.u16RAM[sPort.pushRcnts++] = u16Temp;
        if(MBUS_BUFFER_SIZE == sPort.pushRcnts) sPort.pushRcnts = 0;
    }
}

void popFIFOtoTxData(SCI_MODBUS *mbus)
{
    if(sPort.popTcnts != sPort.pushTcnts) {
        mbus->wrfunc(mbus->sci, sPort.u16RAM[sPort.popTcnts++]);
        if(MBUS_BUFFER_SIZE == sPort.popTcnts) sPort.popTcnts = 0;
    }
}


int16_t pollModbusPort(SCI_MODBUS *mbus)
{
    switch(mbus->evPort) {
    case _INIT_SCI_CONFIG:
        if(0 == mbus->sci) return 0;
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

