/*
 * timetask.c
 *
 *  Created on: May 17, 2024
 *      Author: User
 */

#include "common.h"
#include "shareram.h"
#include "mb_slave/ModbusSlave.h"

void recalParameters(void)
{
    sDrv.f32TargetHwOvp = OVP_PU;
    OVP_CMPDAC(sDrv.f32HwOvp, sDrv.f32TargetHwOvp);
    sDrv.f32RemoteHwOvp = sDrv.f32TargetHwOvp;

//    OCP_CMPDAC(sDrv.f32HwOcp, OCP_PU);
//    sDrv.f32RmtHwOcp = sDrv.f32HwOcp;
}


void pollOcpParam(void);
void pollOvpParam(void);
void (*pollParams)(void) = pollOvpParam;

void pollOcpParam(void)
{
//    if(sDrv.f32TargetHwOvp != sDrv.f32RemoteHwOvp) {
//        sDrv.f32TargetHwOvp = sDrv.f32RemoteHwOvp;
//        OVP_CMPDAC(sDrv.f32HwOvp, sDrv.f32TargetHwOvp );
//    }
    pollParams = pollOvpParam;
}

void pollOvpParam(void)
{
    if(sDrv.f32TargetHwOvp != sDrv.f32RemoteHwOvp) {
        sDrv.f32TargetHwOvp = sDrv.f32RemoteHwOvp;
        OVP_CMPDAC(sDrv.f32HwOvp, sDrv.f32TargetHwOvp );
    }

    pollParams = pollOcpParam;
}



void task25msec(void * s)
{
    static uint16_t u16Cnt = 10;

    if(0<u16Cnt) {
        u16Cnt--;
        if(0 == u16Cnt) {
            u16Cnt = 10;
            if(1 == sReadCPU2.u16LED) {
                sAccessCPU1.u16LED = 0;
            }
            else {
                sAccessCPU1.u16LED = 1;
            }
        }
    }

    pollOvpParam();

    GPIO_writePin(CPU1_D10_GPIO31, sAccessCPU1.u16LED);

    if(GETn_STAT(_CSTAT_INIT_SUCCESS, sDrv)) {
        if(isCallbackReady()) {
            recalParameters();
            SET_STAT(_CSTAT_INIT_PARAMS, sDrv);
        }

        if((0 != sDrv.u32HeartBeat)&&(0 != sCLA.u32HeartBeat)) {
            SET_STAT(_CSTAT_THREAD_READY, sDrv);
        }
    }

#if ENABLE_ELOAD
    if(sDrv.regLoad.u16Enable != sDrv.regLoad.u16Remote) {
        if(0 == sDrv.regLoad.u16Remote) {
            GPIO_writePin(LP_PWM_LOAD, 0);
        }
        else {
            GPIO_writePin(LP_PWM_LOAD, 1);
            sDrv.u32LoadOffDly = 400;
        }
        sDrv.regLoad.u16Enable = sDrv.regLoad.u16Remote;
    }
    else {
        if(0<sDrv.u32LoadOffDly){
            sDrv.u32LoadOffDly--;
            if(0 == sDrv.u32LoadOffDly) sDrv.regLoad.u16Remote = 0;
        }
    }
#endif //ENABLE_ELOAD

}

void task2D5msec(void * s)
{
    if(GET_STAT(_CSTAT_INIT_SUCCESS, sDrv)) {
        scanWarning();
    }
}

ST_TIMETASK time_task[] = {
        {task2D5msec,         0,   T_2D5MS},
        {task25msec,          0,   T_25MS},
        {0, 0, 0}
};


void pollTimeTask(void)
{
    scanTimeTask(time_task, (void *)0);
}
