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
// EPWM4 -> BUCK_PWM Pinmux
//
//
// EPWM4A - GPIO Settings
//
#define GPIO_PIN_EPWM4A 6
#define BUCK_PWM_EPWMA_GPIO 6
#define BUCK_PWM_EPWMA_PIN_CONFIG GPIO_6_EPWM4A
//
// EPWM4B - GPIO Settings
//
#define GPIO_PIN_EPWM4B 7
#define BUCK_PWM_EPWMB_GPIO 7
#define BUCK_PWM_EPWMB_PIN_CONFIG GPIO_7_EPWM4B
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
#define GPIO_PIN_SCIA_RX 43
#define DEBUG_SCI_SCIRX_GPIO 43
#define DEBUG_SCI_SCIRX_PIN_CONFIG GPIO_43_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 42
#define DEBUG_SCI_SCITX_GPIO 42
#define DEBUG_SCI_SCITX_PIN_CONFIG GPIO_42_SCIA_TX

//
// EPWM3 -> DAB_PWM7_PRI_AH Pinmux
//
//
// EPWM3A - GPIO Settings
//
#define GPIO_PIN_EPWM3A 4
#define DAB_PWM7_PRI_AH_EPWMA_GPIO 4
#define DAB_PWM7_PRI_AH_EPWMA_PIN_CONFIG GPIO_4_EPWM3A
//
// EPWM3B - GPIO Settings
//
#define GPIO_PIN_EPWM3B 5
#define DAB_PWM7_PRI_AH_EPWMB_GPIO 5
#define DAB_PWM7_PRI_AH_EPWMB_PIN_CONFIG GPIO_5_EPWM3B

//
// EPWM2 -> DAB_PWM8_PRI_AL Pinmux
//
//
// EPWM2A - GPIO Settings
//
#define GPIO_PIN_EPWM2A 2
#define DAB_PWM8_PRI_AL_EPWMA_GPIO 2
#define DAB_PWM8_PRI_AL_EPWMA_PIN_CONFIG GPIO_2_EPWM2A
//
// EPWM2B - GPIO Settings
//
#define GPIO_PIN_EPWM2B 3
#define DAB_PWM8_PRI_AL_EPWMB_GPIO 3
#define DAB_PWM8_PRI_AL_EPWMB_PIN_CONFIG GPIO_3_EPWM2B

//
// EPWM1 -> DAB_PWM9_2ND Pinmux
//
//
// EPWM1A - GPIO Settings
//
#define GPIO_PIN_EPWM1A 0
#define DAB_PWM9_2ND_EPWMA_GPIO 0
#define DAB_PWM9_2ND_EPWMA_PIN_CONFIG GPIO_0_EPWM1A
//
// EPWM1B - GPIO Settings
//
#define GPIO_PIN_EPWM1B 1
#define DAB_PWM9_2ND_EPWMB_GPIO 1
#define DAB_PWM9_2ND_EPWMB_PIN_CONFIG GPIO_1_EPWM1B

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define CPU2_ADCD_BASE ADCD_BASE
#define CPU2_ADCD_RESULT_BASE ADCDRESULT_BASE
void CPU2_ADCD_init();

#define CPU2_ADCC_BASE ADCC_BASE
#define CPU2_ADCC_RESULT_BASE ADCCRESULT_BASE
void CPU2_ADCC_init();


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
#define DAB_PWM7_PRI_AH_BASE EPWM3_BASE
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
#define DAB_PWM8_PRI_AL_BASE EPWM2_BASE
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
#define DAB_PWM9_2ND_BASE EPWM1_BASE
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

//*****************************************************************************
//
// SYNC Scheme Configurations
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
void	INTERRUPT_init();
void	IPC_SYSCFG_init();
void	SYNC_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
