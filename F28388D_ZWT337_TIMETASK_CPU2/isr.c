/*
 * isr.c
 *
 *  Created on: Mar 18, 2024
 *      Author: cody_chen
 */

#include <math.h>
#include "common.h"
#include "cali_system.h"
#include "c28protection.h"


volatile ST_DRV sDrv = {
     .sVO =  { .sLPF = DEFAULT_VOUT_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = VOUT_SCALE }},
     .sOVP =  { .sLPF = DEFAULT_OVP_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = VOUT_OVP_SCALE }},
     .f32RemoteVref = 0.1f,
     .sCaliSys = DEFAULT_ST_CALI_SYSTEM
};


#ifdef _FLASH
#pragma SET_CODE_SECTION(".TI.ramfunc")
#endif //_FLASH


static inline void scanMeasurement(void)
{
    sDrv.sVO.f32Adc = VO_SENSE;
    getCaliData(sDrv.sVO.f32Adc, &sDrv.sVO.sCali);
    mLPF(sDrv.sVO.sCali.f32Out, &sDrv.sVO.sLPF);

    sDrv.sOVP.f32Adc = VO_OVP_SENSE;
    getAcCaliData(sDrv.sOVP.f32Adc, &sDrv.sOVP.sCali);
    mLPF(sDrv.sOVP.sCali.f32Out, &sDrv.sOVP.sLPF);

    runCalibration(&sDrv.sCaliSys);
}


static inline void scanBrownInOut(void)
{
#if FORCE_OUTPUT_PWM

#else
    if(false == GET_STAT(_CSTAT_BROWN_IN, sDrv)) {
        if(VIN_BROWN_IN_PU < sDrv.sVIN.sLPF.f32Out) {
            SET_STAT(_CSTAT_BROWN_IN, sDrv);
        }
    }
    else {

        if(VIN_BROWN_OUT_PU > sDrv.sVIN.sLPF.f32Out) {
            sDrv.regPwm.u16Enable = false;
            RST_STAT(_CSTAT_OUTPUT_READY, sDrv);
        }
        else {

        }
    }
#endif //#if FORCE_OUTPUT_PWM

    if(true == sDrv.regPwm.u16Enable) {
#if ENABLE_CYCLE_PROTECTION
        if(AND_ERR(_ALL_ERROR, sDrv)) {
            RST_STAT(_CSTAT_ENABLE_PWM, sDrv);
        }
        else {
            SET_STAT(_CSTAT_ENABLE_PWM, sDrv);
        }
#else
        SET_STAT(_CSTAT_ENABLE_PWM, sDrv);
#endif //ENABLE_CYCLE_PROTECTION

    }
    else {
        RST_STAT(_CSTAT_ENABLE_PWM, sDrv);
    }
}

__interrupt void INT_CPU2_ADCD_1_ISR (void)
{

    if(GET_STAT(_CSTAT_INIT_SUCCESS, sDrv)) {
        scanMeasurement();

        scanProtection();

        scanBrownInOut();

        if(GET_STAT(_CSTAT_OUTPUT_READY, sDrv)) {
            uint32_t u32Duty = (uint32_t)(((float32_t) COUNTING_MAX) * sDrv.f32RemoteVref);
        }
        else {

        }
    }
    else {

    }

    sDrv.u32HeartBeat++;
    sDrv.u32HeartBeat &= 0x7FFFFFFF;

    // Clear the interrupt flag
    ADC_clearInterruptStatus(CPU2_ADCD_BASE, ADC_INT_NUMBER1);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INT_CPU2_ADCD_1_INTERRUPT_ACK_GROUP);

}

#ifdef _FLASH
#pragma SET_CODE_SECTION()
#endif //_FLASH



