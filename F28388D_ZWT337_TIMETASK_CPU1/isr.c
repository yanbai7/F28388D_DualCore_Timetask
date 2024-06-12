/*
 * isr.c
 *
 *  Created on: Mar 18, 2024
 *      Author: cody_chen
 */

#include <math.h>
#include "common.h"
#include "cali_system.h"
#include "lut_sigmoid.h"


ST_DRV sDrv = {
        .fgStatus = _CSTAT_INIT_DRV_PARAM,
        .sVO =  { .sLPF = DEFAULT_VREF_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = VOUT_SCALE }},
        .sVIN = { .sLPF = DEFAULT_VREF_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = VIN_SCALE}},
        .sIO =  { .sLPF = DEFAULT_IO_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = IO_SCALE }},
        .sIL =  { .sLPF = DEFAULT_IL_LPF, .sCali = {.f32Gain = 1.0f, .f32Offset = 0.0f, .f32Base = IL_SCALE }},
        .regPwm = { .u16Enable = false },

        .sLoopV = { .f32Ki = _V_LOOP_KI, .f32Kp = _V_LOOP_KP,
                    .f32Min = -1.0f, .f32Max = 1.0f, .f32Itemp = 0.0f, .f32Out = 0.0f, .u16StopUi = false},

        .sLoopI = { .f32Ki = _I_LOOP_KI, .f32Kp = _I_LOOP_KP,
                    .f32Min = -1.0f, .f32Max = 1.0f, .f32Itemp = 0.0f, .f32Out = 0.0f, .u16StopUi = false},

        .f32IrefLimitP = RATED_IOUT_P_PU,
        .f32IrefLimitN = RATED_IOUT_N_PU,
        .f32Ovp = OVP_PU,
        .f32HwOvp = CMP_DACMAX,
        .f32Ocp = OCP_PU,
        .f32HwOcp = CMP_DACMAX,
        .f32VinOvp = VIN_OVP_PU,
        .u32HeartBeat = 0,
        .sSigmoid = DEFAULT_SIGMOID,
        .sCaliSys = DEFAULT_ST_CALI_SYSTEM,
        .regPwm = { .all = 0 },
};


#ifdef _FLASH
#pragma SET_CODE_SECTION(".TI.ramfunc")
#endif //_FLASH


static inline void scanMeasurement(void)
{
    sDrv.sVO.f32Adc = VO_SENSE;
    getCaliData(sDrv.sVO.f32Adc, &sDrv.sVO.sCali);
    mLPF(sDrv.sVO.sCali.f32Out, &sDrv.sVO.sLPF);

    sDrv.sVIN.f32Adc = VIN_SENSE;
    getCaliData(sDrv.sVIN.f32Adc, &sDrv.sVIN.sCali);
    mLPF(sDrv.sVIN.sCali.f32Out, &sDrv.sVIN.sLPF);

    sDrv.sIO.f32Adc = IO_SENSE;
    getAcCaliData(sDrv.sIO.f32Adc, &sDrv.sIO.sCali);
    mLPF(sDrv.sIO.sCali.f32Out, &sDrv.sIO.sLPF);

    sDrv.sIL.f32Adc = IL_SENSE;
    getAcCaliData(sDrv.sIL.f32Adc, &sDrv.sIL.sCali);
    mLPF(sDrv.sIL.sCali.f32Out, &sDrv.sIL.sLPF);

}



static inline void scanBrownInOut(void)
{
    if(false == GET_STAT(_CSTAT_BROWN_IN, sDrv)) {
        if(VIN_BROWN_IN_PU < sDrv.sVIN.sLPF.f32Out) {
            sDrv.f32OpenGain = -1.0f;
            SET_STAT(_CSTAT_BROWN_IN, sDrv);
        }
    }
    else {

        if(VIN_BROWN_OUT_PU > sDrv.sVIN.sLPF.f32Out) {
            sDrv.regPwm.u16Enable = false;
            RST_STAT(_CSTAT_OUTPUT_READY, sDrv);
        }
        else {

            if(sDrv.f32RemoteVref != sDrv.sSigmoid.f32Ytarget) {
                sDrv.f32OpenGain = sDrv.sSigmoid.f32Youtput / (sDrv.sVIN.sLPF.f32Out * VIN2VOUT_SCALE);
                sDrv.f32OutputVref = setSigmoidStep(sDrv.f32RemoteVref, &sDrv.sSigmoid);
                sDrv.f32RemoteVref = sDrv.f32OutputVref;
            }
            else {
                if(sDrv.sSigmoid.f32Youtput == sDrv.sSigmoid.f32Ytarget) {
                    sDrv.f32OpenGain = sDrv.sVO.sLPF.f32Out / (sDrv.sVIN.sLPF.f32Out * VIN2VOUT_SCALE);
                }
                else {
                    sDrv.f32OpenGain = sDrv.sSigmoid.f32Youtput / (sDrv.sVIN.sLPF.f32Out * VIN2VOUT_SCALE);
                }
                sDrv.f32OutputVref = runSigmoidRamp(&sDrv.sSigmoid);
            }

            sDrv.u32DacVref = (uint32_t)(sDrv.f32OutputVref * 4095.0f);
            DAC_setShadowValue(myDAC0_BASE, sDrv.u32DacVref);
        }
    }

    sDrv.f32Vref = sDrv.sSigmoid.f32Youtput;

    if(sDrv.regPwm.u16Enable != sDrv.regPwm.u16Remote) {
        if(0 == sDrv.regPwm.u16Remote) {
            RST_STAT(_CSTAT_ENABLE_PWM, sDrv);
        }
        else {
            SET_STAT(_CSTAT_ENABLE_PWM, sDrv);
        }
        sDrv.regPwm.u16Enable = sDrv.regPwm.u16Remote;
    }

#if ENABLE_CYCLE_PROTECTION
    if(AND_ERR(_ALL_ERROR, sDrv)) {
        sDrv.regPwm.all = 0; //Force Disable PWM
        RST_STAT(_CSTAT_ENABLE_PWM, sDrv);
        DAC_setShadowValue(myDAC0_BASE, 0UL);
    }
#endif //#if ENABLE_CYCLE_PROTECTION

}

#if TEST_S_CMD
static inline void testScmd(void)
{
    if(sDrv.f32RemoteVref != sDrv.sSigmoid.f32Ytarget) {
        sDrv.f32OutputVref = setSigmoidStep(sDrv.f32RemoteVref, &sDrv.sSigmoid);
        sDrv.f32RemoteVref = sDrv.f32OutputVref;
    }
    else {
        sDrv.f32OutputVref = runSigmoidRamp(&sDrv.sSigmoid);
    }

    //Real S-curve Output
//    sDrv.u32DacVref = (uint32_t)(sDrv.sSigmoid.f32Youtput * 4095.0f);
    //Real S-curve Output + Trigger for Begin
    sDrv.u32DacVref = (uint32_t)(sDrv.f32OutputVref * 4095.0f);
    DAC_setShadowValue(myDAC0_BASE, sDrv.u32DacVref);
}
#endif //if TEST_S_CMD

__interrupt void INT_CPU1_ADCA_1_ISR (void)
{
#if ENABLE_FORCE_PWMOUT
    uint32_t u32Duty = (uint32_t)(((float32_t) COUNTING_MAX) * sDrv.f32RemoteVref);
    SET_HRPWMAB_DUTY(u32Duty, PWM_BASE);
    SET_PFM_PRD(u32Duty, PWM_BASE);

#elif TEST_S_CMD
    testScmd();
#else
    scanMeasurement();

    runCalibration(&sDrv.sCaliSys);
    if(GET_STAT(_CSTAT_INIT_SUCCESS, sDrv)) {
        SET_DEBUG_ADC_EOC();

        scanProtection();

        scanBrownInOut();

        if(GET_STAT(_CSTAT_OUTPUT_READY, sDrv)) {

#if (CLOSE_LOOP == LOOP_MODE)
            sDrv.sLoopV.f32Err = sDrv.f32Vref - sDrv.sVO.sCali.f32Out;
            sDrv.sLoopV.u16StopUi = ((sDrv.f32Iref != sDrv.f32Isum)||(sDrv.sLoopI.u16StopUi));
            mPI(&sDrv.sLoopV);

            sDrv.f32Isum = sDrv.sLoopV.f32Out * V2I_SCALE + sDrv.sIO.sCali.f32Out;
            sDrv.f32Iref = csatf(sDrv.f32Isum, sDrv.f32IrefLimitP, sDrv.f32IrefLimitN);
            sDrv.sLoopI.f32Err = csatSpu(sDrv.f32Iref - sDrv.sIL.sCali.f32Out);
            mPI(&sDrv.sLoopI);

            sDrv.f32Duty = cnvUpu2Spu(sDrv.f32OpenGain) + sDrv.sLoopI.f32Out;
            sDrv.f32PwmPU = csatSpu(sDrv.f32Duty);
            sDrv.sLoopI.u16StopUi = (sDrv.f32Duty != sDrv.f32PwmPU);
            uint32_t u32Duty = (uint32_t)((float32_t) COUNTING_MAX * (cnvSpu2Upu(sDrv.f32PwmPU)));

            SET_HRPWMAB_DUTY(u32Duty, PWM_BASE);
#else
            uint32_t u32Duty = (uint32_t)(((float32_t) COUNTING_MAX) * sDrv.f32RemoteVref);
            SET_HRPWMAB_DUTY(u32Duty, PWM_BASE);
#endif

        }
        else {

            rstSigmoidRamp(0.0f, &sDrv.sSigmoid);


#if (CLOSE_LOOP == LOOP_MODE)
            sDrv.sLoopV.f32Out = sDrv.sLoopV.f32Itemp = 0.0f;
            sDrv.sLoopI.f32Out = sDrv.sLoopI.f32Itemp = 0.0f;
#else

            sDrv.sLoopV.f32Out = sDrv.sLoopV.f32Itemp = -1.0f;
#endif
            RST_HRPWMAB_DUTY(PWM_BASE);
        }
    }
    else {
        RST_HRPWMAB_DUTY(PWM_BASE);
    }

#endif //ENABLE_FORCE_PWMOUT


    sDrv.u32HeartBeat++;
    sDrv.u32HeartBeat &= 0x7FFFFFFF;


    RST_DEBUG_ADC_EOC();

    // Clear the interrupt flag
    ADC_clearInterruptStatus(CPU1_ADCA_BASE, ADC_INT_NUMBER1);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INT_CPU1_ADCA_1_INTERRUPT_ACK_GROUP);

//    RST_DEBUG_ADC_EOC();
}



#ifdef _FLASH
#pragma SET_CODE_SECTION()
#endif //_FLASH



