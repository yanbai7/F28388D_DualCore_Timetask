/*
 * HwConfig.h
 *
 *  Created on: Mar 18, 2024
 *      Author: cody_chen
 */

#ifndef HWCONFIG_H_
#define HWCONFIG_H_


//! For 28377S
//! The equation for the output clock is:
//!   TBCLK = EPWMCLK/(highSpeedPrescaler * pre-scaler)
//! \b Note: EPWMCLK is a scaled version of SYSCLK. At reset EPWMCLK is half
//!          SYSCLK.
//! UP/DOWM MODE:= TPWM= (TBPRD + 1) x TBCLK
//! UPDOWM MODE := TPWM= 2 x TBPRD x TBCLK

#define OSCSRC_FREQ                      20000000   //DEVICE_OSCSRC_FREQ

#define CPUCLK_FREQUENCY                 200       /* 200 MHz System frequency */

#define EPWMCLK_FREQ                     100000000  //((OSCSRC_FREQ * 20 * 1) / 2 / 2)

#define DAB_PWM_KHZ                      100UL      // (kHz)

#define T_DAB_PWM_DEADBAND_NSEC          500UL      // (nsec)

#define VIN_SCALE                        80.0f      // [Vpeak]
#define IO_SCALE                         25.0f      // [Apeak]
#define VOUT_OVP_SCALE                   60.0f      // [Apeak]
#define VOUT_SCALE                       60.0f      // [Vpeak]

#define VREF_TARGET_AT_IMAX              6.0f       // [V]
#define VREF_TARGET_AT_IMAX_PU           (VREF_TARGET_AT_IMAX/VOUT_SCALE)

#define VOUT_LPF_K1                      CAL_LPF_K1(3500, ((float)DAB_PWM_KHZ * 1000.0f))
#define DEFAULT_VOUT_LPF                 (ST_LPF){.f32K1 = VOUT_LPF_K1, .f32Out = 0.0f}
#define DEFAULT_OVP_LPF                  DEFAULT_VOUT_LPF
#define DEFAULT_VIN_LPF                  DEFAULT_VOUT_LPF

#define IOUT_LPF_K1                      CAL_LPF_K1(10000, ((float)DAB_PWM_KHZ * 1000.0f))
#define DEFAULT_IO_LPF                   (ST_LPF){.f32K1 = IOUT_LPF_K1, .f32Out = 0.0f}



#define RATED_POWER                      200.0f     // [W]
#define MAX_POWER_TIMES                  1.2        // [Ratio]
#define RATED_IOUT_PU                    (RATED_POWER*MAX_POWER_TIMES/VREF_TARGET_AT_IMAX_PU/IO_SCALE)
#define RATED_IOUT_P_PU                  RATED_IOUT_PU
#define RATED_IOUT_N_PU                  -RATED_IOUT_PU

#define VIN_BROWN_IN                     65.0f      // [Vrms]
#define VIN_BROWN_OUT                    55.0f      // [Vrms]
#define VIN_BROWN_IN_PU                 (VIN_BROWN_IN/VIN_SCALE)
#define VIN_BROWN_OUT_PU                (VIN_BROWN_OUT/VIN_SCALE)

#define VIN_OVP                          76.0f      // [V]
#define VIN_OVP_PU                      (VIN_OVP/VIN_SCALE)

#define VOUT_OVP_TARGET                  30.0f      // [V]
#define VOUT_OVP_PU                     (VOUT_OVP_TARGET/VOUT_OVP_SCALE)

#define OCP_TARGET                       10.0f      // [A]
#define OCP_PU                          (OCP_TARGET/IO_SCALE)

// @ ADC_RESULT_Xy(X, y)
// X:= ADCA/B/C, y:= SOC0-15
#define ADC_12BITS_RESULT_Xy(X, y)       (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0002442f)
#define ADC_16BITS_SPU_Xy(X, y)          (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0000305f-1.0f)
#define ADC_16BITS_UPU_Xy(X, y)          (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0000152f)
#define ADC_RESULT_Xy(X,y)               ADC_12BITS_RESULT_Xy(X, y)


#define D0_VO_SENSE                      ADC_12BITS_RESULT_Xy(D, 0)
#define D1_VO_OVP_SENSE                  ADC_12BITS_RESULT_Xy(D, 1)

#define VO_SENSE                         ((D0_VO_SENSE)*1.000000f)
#define VO_OVP_SENSE                     ((D1_VO_OVP_SENSE)*1.000000f)

#define ENABLE_CYCLE_PROTECTION          1

#define OPEN_LOOP                        1
#define CLOSE_LOOP                       2
#define LOOP_MODE                        (OPEN_LOOP)


#endif /* HWCONFIG_H_ */
