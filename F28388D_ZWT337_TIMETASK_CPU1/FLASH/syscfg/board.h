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
#define CPU1_ADCA_BASE ADCA_BASE
#define CPU1_ADCA_RESULT_BASE ADCARESULT_BASE
void CPU1_ADCA_init();

#define CPU1_ADCB_BASE ADCB_BASE
#define CPU1_ADCB_RESULT_BASE ADCBRESULT_BASE
void CPU1_ADCB_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CMPSS Configurations
//
//*****************************************************************************
#define CMP5_P_OVP_BASE CMPSS5_BASE
#define CMP5_P_OVP_HIGH_COMP_BASE CMPSS5_BASE    
#define CMP5_P_OVP_LOW_COMP_BASE CMPSS5_BASE    
void CMP5_P_OVP_init();

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define SWTIRMER_BASE CPUTIMER0_BASE
void SWTIRMER_init();

//*****************************************************************************
//
// DAC Configurations
//
//*****************************************************************************
#define myDAC0_BASE DACA_BASE
void myDAC0_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define BUCK_PWM_BASE EPWM4_BASE
#define BUCK_PWM_TBPRD 0
#define BUCK_PWM_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define BUCK_PWM_TBPHS 0
#define BUCK_PWM_CMPA 0
#define BUCK_PWM_CMPB 0
#define BUCK_PWM_CMPC 0
#define BUCK_PWM_CMPD 0
#define BUCK_PWM_DBRED 0
#define BUCK_PWM_DBFED 0
#define BUCK_PWM_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define BUCK_PWM_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define BUCK_PWM_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// FLASH Configurations
//
//*****************************************************************************
#define FMC_CPU1_COPY_COPY_BASE FLASH0CTRL_BASE
#define FMC_CPU1_COPY_COPY_ECCBASE FLASH0ECC_BASE
#define FMC_CPU1_COPY_COPY_WAITSTATES 3
#define FMC_CPU1_COPY_COPY_ERRORTHRESHOLD 0

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define CPU1_D10_GPIO31 31
void CPU1_D10_GPIO31_init();
#define CPU2_D9_GPIO34 34
void CPU2_D9_GPIO34_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_CPU1_ADCA_1
#define INT_CPU1_ADCA_1 INT_ADCA1
#define INT_CPU1_ADCA_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_CPU1_ADCA_1_ISR(void);

//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
#define IPC_SYNC IPC_FLAG31
#define BOOT_MODE_CPU2 BOOTMODE_BOOT_TO_FLASH_SECTOR0

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define DEBUG_SCI_BASE SCIA_BASE
#define DEBUG_SCI_BAUDRATE 115200
#define DEBUG_SCI_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define DEBUG_SCI_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define DEBUG_SCI_CONFIG_PAR SCI_CONFIG_PAR_EVEN
void DEBUG_SCI_init();

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
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CMPSS_init();
void	CPUTIMER_init();
void	DAC_init();
void	EPWM_init();
void	FLASH_init();
void	GPIO_init();
void	INTERRUPT_init();
void	IPC_SYSCFG_init();
void	SCI_init();
void	SYNC_init();
void	SYSCTL_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
