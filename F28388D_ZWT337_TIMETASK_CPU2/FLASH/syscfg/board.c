/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	SYNC_init();
	ADC_init();
	CPUTIMER_init();
	EPWM_init();
	IPC_SYSCFG_init();
	INTERRUPT_init();

	EDIS;
}


//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	CPU2_ADCD_init();
	CPU2_ADCC_init();
}

void CPU2_ADCD_init(){
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(CPU2_ADCD_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(CPU2_ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(CPU2_ADCD_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(CPU2_ADCD_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(CPU2_ADCD_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(CPU2_ADCD_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER1
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(CPU2_ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
	ADC_clearInterruptStatus(CPU2_ADCD_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(CPU2_ADCD_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(CPU2_ADCD_BASE, ADC_INT_NUMBER1);
}
void CPU2_ADCC_init(){
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(CPU2_ADCC_BASE, ADC_CLK_DIV_4_0);
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(CPU2_ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(CPU2_ADCC_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(CPU2_ADCC_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(CPU2_ADCC_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(CPU2_ADCC_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER1
	// 		Interrupt Source: disabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(CPU2_ADCC_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
	ADC_disableContinuousMode(CPU2_ADCC_BASE, ADC_INT_NUMBER1);
	ADC_disableInterrupt(CPU2_ADCC_BASE, ADC_INT_NUMBER1);
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	SWTIRMER_init();
}

void SWTIRMER_init(){
	CPUTimer_setEmulationMode(SWTIRMER_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(SWTIRMER_BASE, 3U);
	CPUTimer_setPeriod(SWTIRMER_BASE, 50000000U);
	CPUTimer_disableInterrupt(SWTIRMER_BASE);
	CPUTimer_stopTimer(SWTIRMER_BASE);

	CPUTimer_reloadTimerCounter(SWTIRMER_BASE);
	CPUTimer_startTimer(SWTIRMER_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(DAB_PWM7_PRI_AH_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_2);	
    EPWM_setTimeBasePeriod(DAB_PWM7_PRI_AH_BASE, 0);	
    EPWM_setTimeBaseCounter(DAB_PWM7_PRI_AH_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_PWM7_PRI_AH_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);	
    EPWM_disablePhaseShiftLoad(DAB_PWM7_PRI_AH_BASE);	
    EPWM_setPhaseShift(DAB_PWM7_PRI_AH_BASE, 0);	
    EPWM_setCounterCompareValue(DAB_PWM7_PRI_AH_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM7_PRI_AH_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(DAB_PWM7_PRI_AH_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM7_PRI_AH_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM7_PRI_AH_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_PWM7_PRI_AH_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(DAB_PWM7_PRI_AH_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_PWM7_PRI_AH_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(DAB_PWM7_PRI_AH_BASE);	
    EPWM_setClockPrescaler(DAB_PWM8_PRI_AL_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_2);	
    EPWM_setTimeBasePeriod(DAB_PWM8_PRI_AL_BASE, 0);	
    EPWM_setTimeBaseCounter(DAB_PWM8_PRI_AL_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_PWM8_PRI_AL_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);	
    EPWM_disablePhaseShiftLoad(DAB_PWM8_PRI_AL_BASE);	
    EPWM_setPhaseShift(DAB_PWM8_PRI_AL_BASE, 0);	
    EPWM_setCounterCompareValue(DAB_PWM8_PRI_AL_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM8_PRI_AL_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(DAB_PWM8_PRI_AL_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM8_PRI_AL_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM8_PRI_AL_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_PWM8_PRI_AL_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(DAB_PWM8_PRI_AL_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_PWM8_PRI_AL_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(DAB_PWM8_PRI_AL_BASE);	
    EPWM_setClockPrescaler(DAB_PWM9_2ND_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_2);	
    EPWM_setTimeBasePeriod(DAB_PWM9_2ND_BASE, 0);	
    EPWM_setTimeBaseCounter(DAB_PWM9_2ND_BASE, 0);	
    EPWM_setTimeBaseCounterMode(DAB_PWM9_2ND_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);	
    EPWM_disablePhaseShiftLoad(DAB_PWM9_2ND_BASE);	
    EPWM_setPhaseShift(DAB_PWM9_2ND_BASE, 0);	
    EPWM_setCounterCompareValue(DAB_PWM9_2ND_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM9_2ND_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(DAB_PWM9_2ND_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(DAB_PWM9_2ND_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(DAB_PWM9_2ND_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(DAB_PWM9_2ND_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(DAB_PWM9_2ND_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(DAB_PWM9_2ND_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(DAB_PWM9_2ND_BASE);	
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_CPU2_ADCD_1
	Interrupt_register(INT_CPU2_ADCD_1, &INT_CPU2_ADCD_1_ISR);
	Interrupt_enable(INT_CPU2_ADCD_1);
}
//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
void IPC_SYSCFG_init(){
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
