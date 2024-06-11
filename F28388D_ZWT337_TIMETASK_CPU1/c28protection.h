/*
 * c28protection.h
 *
 *  Created on: May 8, 2024
 *      Author: User
 */

#ifndef C28PROTECTION_H_
#define C28PROTECTION_H_

static inline void scanProtection(void)
{
    if(OVP_STATUS()){
        SET_ERR(_ERR_VO_OVP, sDrv);
    }
}

static inline void scanWarning(void)
{
    if(sDrv.f32Ovp < sDrv.sVO.sCali.f32Out) {
        SET_ERR(_WARNING_VO, sDrv);
    }

    if(sDrv.f32VinOvp < sDrv.sVIN.sCali.f32Out) {
        SET_ERR(_WARNING_VIN, sDrv);
    }

    if(sDrv.f32Ocp < sDrv.sIO.sCali.f32Out || -sDrv.f32Ocp > sDrv.sIO.sCali.f32Out) {
        SET_ERR(_WARNING_IO, sDrv);
    }
}

static inline void rstError(void)
{
    RST_ERR((_ALL_ERROR|_ALL_WARNING), sDrv);
}


#endif /* C28PROTECTION_H_ */
