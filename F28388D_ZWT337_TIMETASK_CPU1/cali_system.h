/*
 * cali_system.h
 *
 *  Created on: Apr 9, 2024
 *      Author: User
 */

#ifndef CALI_SYSTEM_H_
#define CALI_SYSTEM_H_

#define CALI_LPF_K1           0.001f
#define VALID_OFFSET_RANGE    0.01f
#define VALID_POS_OFFSET      (VALID_OFFSET_RANGE)
#define VALID_NEG_OFFSET      (-VALID_OFFSET_RANGE)

#define DEFAULT_ST_CALI_SYSTEM (ST_CALI_SYSTEM) {  .fsm = _CALI_NO_ACTION, \
                                                   .sLine = DEFAULT_LINE, \
                                                   .sPoint = DEFAULT_POINT \
                                                }


static inline void runCalibration(HAL_CALI_SYSTEM v)
{
    switch(v->fsm)
    {
        CALI_DC_PARAM(sDrv.sIO.sCali, IL)
        CALI_DC_PARAM(sDrv.sIL.sCali, IO)
        CALI_DC_PARAM(sDrv.sVO.sCali, VO)
        CALI_DC_PARAM(sDrv.sVIN.sCali, VIN)

    case _EXIT_CALI:
        FG_SWTO(_CALI_NO_ACTION, v->fsm);
        break;
    case _CALI_NO_ACTION:
    default:
        break;
    }

}


#endif /* CALI_SYSTEM_H_ */
