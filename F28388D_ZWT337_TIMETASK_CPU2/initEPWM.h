/*
 * initPWM.h
 *
 *  Created on: Mar 18, 2024
 *      Author: cody_chen
 */

#ifndef INIT_PWM_H
#define INIT_PWM_H

#include "common.h"
#include "HwConfig.h"

#define ADC_TRG_SRC     EPWM_SOC_A
#define PWM_BASE        DAB_PWM7_PRI_AH_BASE
#define PWM_KHZ         DAB_PWM_KHZ
#define T_DB_NSEC       T_DAB_PWM_DEADBAND_NSEC

#define PWM_CNTS        (uint16_t)(((uint32_t)EPWMCLK_FREQ/1000/PWM_KHZ)>>1)

#define PWM_DB_CNTS     (uint16_t)(EPWMCLK_FREQ/1000*T_DB_NSEC/1000000)

#define COUNTING_MAX    (PWM_CNTS-1)
#define DB_H_CNTS       (PWM_DB_CNTS>>1)
#define DB_L_CNTS       (PWM_CNTS - DB_H_CNTS)

#define SET_CMPA(cmp, base)   HWREG(base + EPWM_O_CMPA) = cmp;
#define SET_CMPB(cmp, base)   HWREG(base + EPWM_O_CMPB) = cmp;

#define SET_DB_PWMA(cmp) (DB_H_CNTS<cmp? (cmp - DB_H_CNTS): 0U)
#define SET_DB_PWMB(cmp) (DB_L_CNTS<cmp? PWM_CNTS: (cmp + DB_H_CNTS))

#define RST_PWMAB_DUTY(base)         SET_CMPA(0, base); \
                                     SET_CMPB(PWM_CNTS, base);

#define SET_PWMAB_DUTY(cmp, base)    SET_CMPA(SET_DB_PWMA(cmp), base); \
                                     SET_CMPB(SET_DB_PWMB(cmp), base);

#define SET_PWMA_DUTY(cmp, base)     SET_CMPA(cmp, base); \
                                     SET_CMPB(PWM_CNTS, base);

#define SET_PWMB_DUTY(cmp, base)     SET_CMPA(0, base); \
                                     SET_CMPB(cmp, base);


static inline void enableAdcTriggerbyPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(PWM_BASE, ADC_TRG_SRC);

    //
    // Configure the SOC to occur on the first up-count event
    EPWM_setADCTriggerSource(PWM_BASE, ADC_TRG_SRC, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(PWM_BASE, ADC_TRG_SRC, 1);

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(PWM_BASE, ADC_TRG_SRC);
}


static inline void initEPWMxAB(void)
{

    EPWM_setTimeBaseCounterMode(PWM_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_disablePhaseShiftLoad(PWM_BASE);
    EPWM_setClockPrescaler(PWM_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set-up TBCLK
    EPWM_setPeriodLoadMode(PWM_BASE, EPWM_PERIOD_SHADOW_LOAD);
    EPWM_selectPeriodLoadEvent(PWM_BASE, EPWM_SHADOW_LOAD_MODE_COUNTER_ZERO);
    EPWM_setTimeBasePeriod(PWM_BASE, PWM_CNTS);
    EPWM_setPhaseShift(PWM_BASE, 0U);
    EPWM_setTimeBaseCounter(PWM_BASE, 0U);

    //
    // set duty 0% initially
    EPWM_setCounterCompareValue(PWM_BASE, EPWM_COUNTER_COMPARE_A, 0);
    EPWM_setCounterCompareValue(PWM_BASE, EPWM_COUNTER_COMPARE_B, PWM_CNTS);

    //
    // ePWM1 SYNCO is generated on CTR=0
//    EPWM_setSyncOutPulseMode(PWM_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    //
    // Set up shadowing
    // Compare Value would load on count zero.
    EPWM_setCounterCompareShadowLoadMode(PWM_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(PWM_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    // CAU - Output A Low
    // CAD - Output A High
    // CBU - Output B High
    // CBD - Output B Low
    EPWM_setActionQualifierAction(PWM_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(PWM_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    EPWM_setActionQualifierAction(PWM_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setActionQualifierAction(PWM_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    //
    // Enable EPWM

    EPWM_setTimeBaseCounterMode(PWM_BASE, EPWM_COUNTER_MODE_UP_DOWN);


}

static inline void initPWM(void)
{

    //
    // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    initEPWMxAB();

    //
    // Enable sync and clock to PWM
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    enableAdcTriggerbyPWM();
}


#endif /* INIT_PWM_H */
