/*
 *  File Name: linkVariables.c
 *
 *  Created on: 5/13/2024
 *  Author: CODY
 */

#include "ModbusCommon.h"
#include "ModbusSlave.h"


void initRegN(void *v){ 

	SCI_MODBUS *p = (SCI_MODBUS *) v;
	p->pReg->u16COMmonHEAder = 2423; 
	p->pReg->u16COMmonLENgth = 4; 
	p->pReg->u16MAChineINFOrmationOFFSet = 9000; 
	p->pReg->u16USERPARameterOFFSet = 1000; 
	p->pReg->u16ADVAncePARameterOFFSet = 1020; 
	p->pReg->u16COMmonCHEcksum = 13447; 
	sDrv.f32RemoteVref = 0; 
	sDrv.regLoad.u16Remote = 0; 
	p->pReg->u16DACCHAnnel = 0; 
	p->pReg->u32FIRmwareBUIldDATe = 2024051310; 
	p->pReg->u16COUntryCODe = 886; 
	p->pReg->u16VENderid = 2423; 
	p->pReg->u32BUIldDATe = 2024051310; 
}

void readRegN(void *v){ 

	SCI_MODBUS *p = (SCI_MODBUS *) v;
	p->pReg->u16CLACONtrolSTAtus = sDrv.fgStatus; 
	p->pReg->u16CLAERROrSTAtus = sDrv.fgError; 
	p->pReg->u16ENABlePWM = sDrv.regPwm.u16Remote; 
	p->pReg->s16VOLtageREFerence = MB_SFtoQ15(sDrv.f32RemoteVref); 
	p->pReg->s16POSitiveCURrentLIMit = MB_SFtoQ15(sDrv.f32IrefLimitP); 
	p->pReg->s16NEGativeCURrentLIMit = MB_SFtoQ15(sDrv.f32IrefLimitN); 
	p->pReg->u16LANuchPADPWMLOAd = sDrv.regLoad.u16Remote; 
	p->pReg->s16OVERCURrentPROtection = MB_SFtoQ15(sDrv.f32RemoteHwOcp); 
	p->pReg->s16OVERVOLtagePROtection = MB_SFtoQ15(sDrv.f32RemoteHwOvp); 
	p->pReg->s16MEAsureVOLtageOUTPut = MB_SFtoQ15(sDrv.sVO.sLPF.f32Out); 
	p->pReg->s16MEAsureVOLtageINPUt = MB_SFtoQ15(sDrv.sVIN.sLPF.f32Out); 
	p->pReg->s16MEAsureCURrentOUTPut = MB_SFtoQ15(sDrv.sIO.sLPF.f32Out); 
	p->pReg->s16MEAsureINDUctorCURrent = MB_SFtoQ15(sDrv.sIL.sLPF.f32Out); 
	p->pReg->f32VOLtageLOOpkp = sDrv.sLoopV.f32Kp; 
	p->pReg->f32VOLtageLOOpki = sDrv.sLoopV.f32Ki; 
	p->pReg->f32CURrentLOOpkp = sDrv.sLoopI.f32Kp; 
	p->pReg->f32CURrentLOOpki = sDrv.sLoopI.f32Ki; 
	p->pReg->f32OPENLOOpGAIn = sDrv.f32OpenGain; 
	p->pReg->f32OUTPutPWM = sDrv.f32PwmPU; 
	p->pReg->u32HEArtbeatC28 = sDrv.u32HeartBeat; 
	p->pReg->u32HEArtbeatCLA = sCLA.u32HeartBeat; 
}

void writeReg(void *v){ 

	SCI_MODBUS *p = (SCI_MODBUS *) v;
	switch(p->info.rwfrom) {
	case _muCLACONtrolSTAtus :   sDrv.fgStatus = p->pReg->u16CLACONtrolSTAtus; break;
	case _muCLAERROrSTAtus :   sDrv.fgError = p->pReg->u16CLAERROrSTAtus; break;
	case _muENABlePWM :   sDrv.regPwm.u16Remote = p->pReg->u16ENABlePWM; break;
	case _muVOLtageREFerence :   sDrv.f32RemoteVref = MB_Q15toSF(p->pReg->s16VOLtageREFerence); break;
	case _muPOSitiveCURrentLIMit :   sDrv.f32IrefLimitP = MB_Q15toSF(p->pReg->s16POSitiveCURrentLIMit); break;
	case _muNEGativeCURrentLIMit :   sDrv.f32IrefLimitN = MB_Q15toSF(p->pReg->s16NEGativeCURrentLIMit); break;
	case _muLANuchPADPWMLOAd :   sDrv.regLoad.u16Remote = p->pReg->u16LANuchPADPWMLOAd; break;
	case _muOVERCURrentPROtection :   sDrv.f32RemoteHwOcp = MB_Q15toSF(p->pReg->s16OVERCURrentPROtection); break;
	case _muOVERVOLtagePROtection :   sDrv.f32RemoteHwOvp = MB_Q15toSF(p->pReg->s16OVERVOLtagePROtection); break;
	case _muMEAsureVOLtageOUTPut :   sDrv.sVO.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureVOLtageOUTPut); break;
	case _muMEAsureVOLtageINPUt :   sDrv.sVIN.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureVOLtageINPUt); break;
	case _muMEAsureCURrentOUTPut :   sDrv.sIO.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureCURrentOUTPut); break;
	case _muMEAsureINDUctorCURrent :   sDrv.sIL.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureINDUctorCURrent); break;
	case _muVOLtageLOOpkp0 :   sDrv.sLoopV.f32Kp = p->pReg->f32VOLtageLOOpkp; break;
	case _muVOLtageLOOpki0 :   sDrv.sLoopV.f32Ki = p->pReg->f32VOLtageLOOpki; break;
	case _muCURrentLOOpkp0 :   sDrv.sLoopI.f32Kp = p->pReg->f32CURrentLOOpkp; break;
	case _muCURrentLOOpki0 :   sDrv.sLoopI.f32Ki = p->pReg->f32CURrentLOOpki; break;
	case _muOPENLOOpGAIn0 :   sDrv.f32OpenGain = p->pReg->f32OPENLOOpGAIn; break;
	case _muOUTPutPWM0 :   sDrv.f32PwmPU = p->pReg->f32OUTPutPWM; break;
	case _muHEArtbeatC280 :   sDrv.u32HeartBeat = p->pReg->u32HEArtbeatC28; break;
	case _muHEArtbeatCLA0 :   sCLA.u32HeartBeat = p->pReg->u32HEArtbeatCLA; break;
	default:
	    break;
	}
}

void writeRegN(void *v){ 

	SCI_MODBUS *p = (SCI_MODBUS *) v;
	sDrv.fgStatus = p->pReg->u16CLACONtrolSTAtus; 
	sDrv.fgError = p->pReg->u16CLAERROrSTAtus; 
	sDrv.regPwm.u16Remote = p->pReg->u16ENABlePWM; 
	sDrv.f32RemoteVref = MB_Q15toSF(p->pReg->s16VOLtageREFerence); 
	sDrv.f32IrefLimitP = MB_Q15toSF(p->pReg->s16POSitiveCURrentLIMit); 
	sDrv.f32IrefLimitN = MB_Q15toSF(p->pReg->s16NEGativeCURrentLIMit); 
	sDrv.regLoad.u16Remote = p->pReg->u16LANuchPADPWMLOAd; 
	sDrv.f32RemoteHwOcp = MB_Q15toSF(p->pReg->s16OVERCURrentPROtection); 
	sDrv.f32RemoteHwOvp = MB_Q15toSF(p->pReg->s16OVERVOLtagePROtection); 
	sDrv.sVO.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureVOLtageOUTPut); 
	sDrv.sVIN.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureVOLtageINPUt); 
	sDrv.sIO.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureCURrentOUTPut); 
	sDrv.sIL.sLPF.f32Out = MB_Q15toSF(p->pReg->s16MEAsureINDUctorCURrent); 
	sDrv.sLoopV.f32Kp = p->pReg->f32VOLtageLOOpkp; 
	sDrv.sLoopV.f32Ki = p->pReg->f32VOLtageLOOpki; 
	sDrv.sLoopI.f32Kp = p->pReg->f32CURrentLOOpkp; 
	sDrv.sLoopI.f32Ki = p->pReg->f32CURrentLOOpki; 
	sDrv.f32OpenGain = p->pReg->f32OPENLOOpGAIn; 
	sDrv.f32PwmPU = p->pReg->f32OUTPutPWM; 
	sDrv.u32HeartBeat = p->pReg->u32HEArtbeatC28; 
	sCLA.u32HeartBeat = p->pReg->u32HEArtbeatCLA; 
}

