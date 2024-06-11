/*
 * cali_param.h
 *
 *  Created on: Apr 9, 2024
 *      Author: User
 */

#ifndef CALI_PARAM_H_
#define CALI_PARAM_H_

#define _CALI_AC_STEP_NAME(name)    _RUN_## name ##_CALIBRATION, \
                                    _INIT_## name ##_PARAMETERS, \
                                    _GET_## name ##_ADC_OFFSET, \
                                    _RECORD_## name ##_ADC_OFFSET, \
                                    _GET_## name ##_ADC_GAIN, \
                                    _RECORD_## name ##_ADC_GAIN, \
                                    _WAIT_FOR_## name ##_SET_ZERO

#define _CALI_DC_STEP_NAME(name)    _RUN_## name ##_CALIBRATION, \
                                    _INIT_## name ##_PARAMETERS, \
                                    _GET_## name ##_POINT1, \
                                    _RECORD_## name ##_POINT1, \
                                    _GET_## name ##_POINT2, \
                                    _RECORD_## name ##_POINT2, \
                                    _WAIT_FOR_## name ##_SET_ZERO

typedef volatile enum {
    _CALI_NO_ACTION = 0x00000000,
    _CALI_DC_STEP_NAME(IO),
    _CALI_DC_STEP_NAME(IL),
    _CALI_DC_STEP_NAME(VO),
    _CALI_DC_STEP_NAME(VIN),
    _EXIT_CALI = 0x40000000,
    _MARK_CALI_ERROR = 0x80000000
}FSM_CALI;

typedef volatile FSM_CALI * HAL_FSM_CALI;

typedef volatile struct {
    FSM_CALI fsm;
    ST_LINE sLine;
    ST_POINT sPoint;
    float32_t f32Temp;
} ST_CALI_SYSTEM;

typedef ST_CALI_SYSTEM * HAL_CALI_SYSTEM;

#define CALI_AC_PARAM(p, name)  \
    case _RUN_## name ##_CALIBRATION: \
    case _INIT_## name ##_PARAMETERS: \
        s.f32Gain = 1.0f; \
        s.f32Offset = 1.0f; \
        v->sPoint = DEFAULT_POINT; \
        FG_SWTO(_GET_## name ##_ADC_OFFSET, v->fsm); \
    case _GET_## name ##_ADC_OFFSET: \
        v->f32Temp = (s.f32Input - s.f32Offset); \
        s.f32Offset += CALI_LPF_K1 * v->f32Temp; \
        break; \
    case _RECORD_## name ##_ADC_OFFSET: \
        if((VALID_POS_OFFSET < s.f32Offset)||(VALID_NEG_OFFSET > s.f32Offset)) { \
            FG_SET(_MARK_CALI_ERROR, v->fsm); \
        } \
        else { \
            FG_SWTO(_GET_## name ##_ADC_GAIN, v->fsm); \
        } \
    case _GET_## name ##_ADC_GAIN: \
        v->sPoint.x += CALI_LPF_K1 * (s.f32Out - v->sPoint.x); \
        break; \
    case _RECORD_## name ##_ADC_GAIN: \
        s.f32Gain = (v->sPoint.y / s.f32Base) / v->sPoint.x; \
        FG_SWTO(_WAIT_FOR_## name ##_SET_ZERO, v->fsm); \
        break; \
    case _WAIT_FOR_## name ##_SET_ZERO: \
        break;

#define CALI_DC_PARAM(s, name)  \
    case _RUN_## name ##_CALIBRATION: \
    case _INIT_## name ##_PARAMETERS: \
        s.f32Gain = 1.0f; \
        s.f32Offset = 0.0f; \
        v->sLine = DEFAULT_LINE; \
        FG_SWTO(_GET_## name ##_POINT1, v->fsm); \
    case _GET_## name ##_POINT1: \
        v->f32Temp = (s.f32Input - v->sLine.p1.x); \
        v->sLine.p1.x += CALI_LPF_K1 * v->f32Temp; \
        break; \
    case _RECORD_## name ##_POINT1: \
        FG_SWTO(_GET_## name ##_POINT2, v->fsm); \
    case _GET_## name ##_POINT2: \
        v->f32Temp = (s.f32Input - v->sLine.p2.x); \
        v->sLine.p2.x += CALI_LPF_K1 * v->f32Temp; \
        break; \
    case _RECORD_## name ##_POINT2: \
        s.f32Gain = (v->sLine.p2.y-v->sLine.p1.y)/s.f32Base/(v->sLine.p2.x-v->sLine.p1.x); \
        s.f32Offset = v->sLine.p2.y/s.f32Base - s.f32Gain*v->sLine.p2.x; \
        FG_SWTO(_WAIT_FOR_## name ##_SET_ZERO, v->fsm); \
        break; \
    case _WAIT_FOR_## name ##_SET_ZERO: \
        break;


#endif /* CALI_PARAM_H_ */
