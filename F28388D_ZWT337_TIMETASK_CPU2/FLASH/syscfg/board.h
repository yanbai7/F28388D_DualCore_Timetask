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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM1 -> BUCK_PWM Pinmux
//
//
// EPWM1A - GPIO Settings
//
#define GPIO_PIN_EPWM1A 0
#define BUCK_PWM_EPWMA_GPIO 0
#define BUCK_PWM_EPWMA_PIN_CONFIG GPIO_0_EPWM1A
//
// EPWM1B - GPIO Settings
//
#define GPIO_PIN_EPWM1B 1
#define BUCK_PWM_EPWMB_GPIO 1
#define BUCK_PWM_EPWMB_PIN_CONFIG GPIO_1_EPWM1B
//
// GPIO31 - GPIO Settings
//
#define CPU1_D10_GPIO31_GPIO_PIN_CONFIG GPIO_31_GPIO31
//
// GPIO34 - GPIO Settings
//
#define CPU2_D9_GPIO34_GPIO_PIN_CONFIG GPIO_34_GPIO34

//
// SCIA -> DEBUG_SCI Pinmux
//
//
// SCIA_RX - GPIO Settings
//
#define GPIO_PIN_SCIA_RX 28
#define DEBUG_SCI_SCIRX_GPIO 28
#define DEBUG_SCI_SCIRX_PIN_CONFIG GPIO_28_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 29
#define DEBUG_SCI_SCITX_GPIO 29
#define DEBUG_SCI_SCITX_PIN_CONFIG GPIO_29_SCIA_TX

//
// EPWM7 -> DAB_PWM7_PRI_AH Pinmux
//
//
// EPWM7A - GPIO Settings
//
#define GPIO_PIN_EPWM7A 12
#define DAB_PWM7_PRI_AH_EPWMA_GPIO 12
#define DAB_PWM7_PRI_AH_EPWMA_PIN_CONFIG GPIO_12_EPWM7A

//
// EPWM8 -> DAB_PWM8_PRI_AL Pinmux
//
//
// EPWM8A - GPIO Settings
//
#define GPIO_PIN_EPWM8A 14
#define DAB_PWM8_PRI_AL_EPWMA_GPIO 14
#define DAB_PWM8_PRI_AL_EPWMA_PIN_CONFIG GPIO_14_EPWM8A

//
// EPWM9 -> DAB_PWM9_2ND Pinmux
//
//
// EPWM9A - GPIO Settings
//
#define GPIO_PIN_EPWM9A 16
#define DAB_PWM9_2ND_EPWMA_GPIO 16
#define DAB_PWM9_2ND_EPWMA_PIN_CONFIG GPIO_16_EPWM9A
//
// EPWM9B - GPIO Settings
//
#define GPIO_PIN_EPWM9B 162
#define DAB_PWM9_2ND_EPWMB_GPIO 162
#define DAB_PWM9_2ND_EPWMB_PIN_CONFIG GPIO_162_EPWM9B

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define CPU2_ADCD_BASE ADCD_BASE
#define CPU2_ADCD_RESULT_BASE ADCDRESULT_BASE
#define SOC0_DAB_VO ADC_SOC_NUMBER0
#define SOC0_DAB_VO_FORCE ADC_FORCE_SOC0
#define SOC0_DAB_VO_ADC_BASE ADCD_BASE
#define SOC0_DAB_VO_RESULT_BASE ADCDRESULT_BASE
#define SOC0_DAB_VO_SAMPLE_WINDOW 80
#define SOC0_DAB_VO_TRIGGER_SOURCE ADC_TRIGGER_EPWM7_SOCA
#define SOC0_DAB_VO_CHANNEL ADC_CH_ADCIN2
#define SOC1_DAB_VO_OVP ADC_SOC_NUMBER1
#define SOC1_DAB_VO_OVP_FORCE ADC_FORCE_SOC1
#define SOC1_DAB_VO_OVP_ADC_BASE ADCD_BASE
#define SOC1_DAB_VO_OVP_RESULT_BASE ADCDRESULT_BASE
#define SOC1_DAB_VO_OVP_SAMPLE_WINDOW 320
#define SOC1_DAB_VO_OVP_TRIGGER_SOURCE ADC_TRIGGER_EPWM7_SOCA
#define SOC1_DAB_VO_OVP_CHANNEL ADC_CH_ADCIN4
void CPU2_ADCD_init();


//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define SWTIRMER_BASE CPUTIMER1_BASE
void SWTIRMER_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define DAB_PWM7_PRI_AH_BASE EPWM7_BASE
#define DAB_PWM7_PRI_AH_TBPRD 0
#define DAB_PWM7_PRI_AH_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define DAB_PWM7_PRI_AH_TBPHS 0
#define DAB_PWM7_PRI_AH_CMPA 0
#define DAB_PWM7_PRI_AH_CMPB 0
#define DAB_PWM7_PRI_AH_CMPC 0
#define DAB_PWM7_PRI_AH_CMPD 0
#define DAB_PWM7_PRI_AH_DBRED 0
#define DAB_PWM7_PRI_AH_DBFED 0
#define DAB_PWM7_PRI_AH_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM7_PRI_AH_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM7_PRI_AH_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DAB_PWM8_PRI_AL_BASE EPWM8_BASE
#define DAB_PWM8_PRI_AL_TBPRD 0
#define DAB_PWM8_PRI_AL_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define DAB_PWM8_PRI_AL_TBPHS 0
#define DAB_PWM8_PRI_AL_CMPA 0
#define DAB_PWM8_PRI_AL_CMPB 0
#define DAB_PWM8_PRI_AL_CMPC 0
#define DAB_PWM8_PRI_AL_CMPD 0
#define DAB_PWM8_PRI_AL_DBRED 0
#define DAB_PWM8_PRI_AL_DBFED 0
#define DAB_PWM8_PRI_AL_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM8_PRI_AL_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM8_PRI_AL_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DAB_PWM9_2ND_BASE EPWM9_BASE
#define DAB_PWM9_2ND_TBPRD 0
#define DAB_PWM9_2ND_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define DAB_PWM9_2ND_TBPHS 0
#define DAB_PWM9_2ND_CMPA 0
#define DAB_PWM9_2ND_CMPB 0
#define DAB_PWM9_2ND_CMPC 0
#define DAB_PWM9_2ND_CMPD 0
#define DAB_PWM9_2ND_DBRED 0
#define DAB_PWM9_2ND_DBFED 0
#define DAB_PWM9_2ND_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM9_2ND_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DAB_PWM9_2ND_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// FLASH Configurations
//
//*****************************************************************************
#define FMC_CPU2_BASE FLASH0CTRL_BASE
#define FMC_CPU2_ECCBASE FLASH0ECC_BASE
#define FMC_CPU2_WAITSTATES 3
#define FMC_CPU2_ERRORTHRESHOLD 0

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_CPU2_ADCD_1
#define INT_CPU2_ADCD_1 INT_ADCD1
#define INT_CPU2_ADCD_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_CPU2_ADCD_1_ISR(void);

//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
#define IPC_SYNC IPC_FLAG31
#define IPC_SYNC IPC_FLAG31

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define CPU1_D10_GPIO31 31
#define CPU2_D9_GPIO34 34

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	CPUTIMER_init();
void	EPWM_init();
void	FLASH_init();
void	INTERRUPT_init();
void	IPC_SYSCFG_init();
void	SYNC_init();
void	SYSCTL_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
