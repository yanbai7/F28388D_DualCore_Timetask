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

#define BUCK_PWM_KHZ                     100UL    // (kHz)

#define T_BUCK_PWM_DEADBAND_NSEC         200UL   // (nsec)

#define VIN_SCALE                        13.3000f   // [Vpeak]
#define IO_SCALE                         7.51666f   // [Apeak]
#define IL_SCALE                         7.51666f   // [Apeak]
#define VOUT_SCALE                       6.70000f   // [Vpeak]

#define V2I_SCALE                        (VOUT_SCALE/IL_SCALE)
#define VIN2VOUT_SCALE                   (VIN_SCALE/VOUT_SCALE)

#define VREF_TARGET_AT_IMAX              5.0f     // [V]
#define VREF_TARGET_AT_IMAX_PU           (VREF_TARGET_AT_IMAX/VOUT_SCALE)

#define VREF_LPF_K1                      CAL_LPF_K1(3500, ((float)BUCK_PWM_KHZ * 1000.0f))
#define DEFAULT_VREF_LPF                 (ST_LPF){.f32K1 = VREF_LPF_K1, .f32Out = 0.0f}

#define RATED_POWER                      20.0f   // [W]
#define MAX_POWER_TIMES                  1.2      // [Ratio]
#define RATED_IOUT_PU                    (RATED_POWER*MAX_POWER_TIMES/VREF_TARGET_AT_IMAX/IO_SCALE)
#define RATED_IOUT_P_PU                  RATED_IOUT_PU
#define RATED_IOUT_N_PU                  -RATED_IOUT_PU

#define VIN_BROWN_IN                     8.0f    // [Vrms]
#define VIN_BROWN_OUT                    6.0f    // [Vrms]
#define VIN_BROWN_IN_PU                 (VIN_BROWN_IN/VIN_SCALE)
#define VIN_BROWN_OUT_PU                (VIN_BROWN_OUT/VIN_SCALE)

#define VIN_OVP                          11.0000f    // [V]
#define VIN_OVP_PU                      (VIN_OVP/VIN_SCALE)

#define OVP_TARGET                       6.00000f    // [V]
#define OVP_PU                          (OVP_TARGET/VOUT_SCALE)


#define OCP_TARGET                       5.0f    // [A]
#define OCP_PU                          (OCP_TARGET/IO_SCALE)

#define VIN_LPF_K1                       DEFAULT_VREF_LPF
#define VO_LPF_K1                        DEFAULT_VREF_LPF
#define IO_LPF_K1                        CAL_LPF_K1(10000.0f, ((float)BUCK_PWM_KHZ * 1000.0f))
#define DEFAULT_IO_LPF                   (ST_LPF){.f32K1 = IO_LPF_K1, .f32Out = 0.0f}
#define IL_LPF_K1                        CAL_LPF_K1(10000.0f, ((float)BUCK_PWM_KHZ * 1000.0f))
#define DEFAULT_IL_LPF                   (ST_LPF){.f32K1 = IL_LPF_K1, .f32Out = 0.0f}


// @ ADC_RESULT_Xy(X, y)
// X:= ADCA/B/C, y:= SOC0-15
#define ADC_12BITS_RESULT_Xy(X, y)       (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0002442f)
#define ADC_16BITS_SPU_Xy(X, y)          (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0000305f-1.0f)
#define ADC_16BITS_UPU_Xy(X, y)          (((float)HWREGH(ADC ## X ##RESULT_BASE + y))*0.0000152f)
#define ADC_RESULT_Xy(X,y)               ADC_12BITS_RESULT_Xy(X, y)

#define A14P_A15N_SOC0_IL_SENSE          ADC_16BITS_SPU_Xy(A, 0)
#define A2P_A3N_SOC1_VIN_SENSE           ADC_16BITS_UPU_Xy(A, 1)
#define A4P_A4N_SOC2_VO_SENSE            ADC_16BITS_UPU_Xy(A, 1)

#define B2P_B2N_SOC0_IO_SENSE            ADC_16BITS_SPU_Xy(B, 0)
#define B2P_B2N_SOC1_IO_SENSE            ADC_16BITS_SPU_Xy(B, 1)
#define B2P_B2N_SOC2_IO_SENSE            ADC_16BITS_SPU_Xy(B, 2)


#define IL_SENSE                         ((A14P_A15N_SOC0_IL_SENSE)*1.00000f)
#define IO_SENSE                         ((B2P_B2N_SOC0_IO_SENSE+B2P_B2N_SOC1_IO_SENSE+B2P_B2N_SOC2_IO_SENSE)*0.333333f)
#define VO_SENSE                         ((A4P_A4N_SOC2_VO_SENSE)*1.00000f)
#define VIN_SENSE                        ((A2P_A3N_SOC1_VIN_SENSE)*1.00000f)

#define _V_LOOP_KP                       (1.0f)
#define _V_LOOP_KI                       (0.0001f)

#define _I_LOOP_KP                       (1.0f)
#define _I_LOOP_KI                       (0.001f)

#define ENABLE_DEBUG_DAC                 1
#define ENABLE_CYCLE_PROTECTION          1
#define ENABLE_ELOAD                     0

#define CMP_DACMAX                       4095.0f
#define CMP_STATUS(cmp, base)            (CMPSS_STS_## cmp ##_FILTOUT & CMPSS_getStatus(base))
#define OVP_STATUS()                     CMP_STATUS(HI, CMP5_P_OVP_BASE)
#define OCP_STATUS()                     CMP_STATUS(HI, CMP2_P_OCP_BASE)

#define CMPSS_HI_DAC(data, base)         CMPSS_setDACValueHigh(base, (uint16_t)data)
#define CMPSS_LO_DAC(data, base)         CMPSS_setDACValueLow(base, (uint16_t)data)
#define SET_CMPH_DAC(out, in, cal, cmp)  out = (in - cal.f32Offset)/cal.f32Gain * CMP_DACMAX; \
                                         CMPSS_HI_DAC(out, cmp);
#define SET_CMPL_DAC(out, in, cal, cmp)  out = (in - cal.f32Offset)/cal.f32Gain * CMP_DACMAX; \
                                         CMPSS_LO_DAC(out, cmp);

#define OVP_CMPDAC(out, in)              SET_CMPH_DAC(out, in, sDrv.sVO.sCali, CMP5_P_OVP_BASE)
#define OCP_CMPDAC(out, in)              SET_CMPH_DAC(out, in, sDrv.sIL.sCali, CMP2_P_OCP_BASE)

#define OPEN_LOOP                        1
#define CLOSE_LOOP                       2
#define LOOP_MODE                        (CLOSE_LOOP)

#define ENABLE_FORCE_PWMOUT              0
#define TEST_S_CMD                       1

#endif /* HWCONFIG_H_ */
