/*
 *  File Name: mbcmd.h
 *
 *  Created on: 5/13/2024
 *  Author: CODY
 */

#ifndef MBCMD_H_
#define MBCMD_H_



typedef enum {
	_g0_MODE = 0,
	_g1000_MODE,
	_g1030_MODE,
	_g9000_MODE,
    _END_OF_MODE
} ID_MODE;


enum {
	_muCOMmonHEAder = 0,                    // #0  T_U16                
	_muCOMmonLENgth = 1,                    // #1  T_U16                
	_muMAChineINFOrmationOFFSet = 2,        // #2  T_U16                
	_muUSERPARameterOFFSet = 3,             // #3  T_U16                
	_muADVAncePARameterOFFSet = 4,          // #4  T_U16                
	_muCOMmonCHEcksum = 5,                  // #5  T_U16                
    _end_of_0_id = 6
};

enum {
	_muCLACONtrolSTAtus = 1000,             // #1000  T_U16             
	_muCLAERROrSTAtus = 1001,               // #1001  T_U16             
	_muENABlePWM = 1002,                    // #1002  T_U16             
	_muCONtrolMODe = 1003,                  // #1003  T_U16             
	_muVOLtageREFerence = 1004,             // #1004  T_Q15             
	_muPOSitiveCURrentLIMit = 1005,         // #1005  T_Q15             
	_muNEGativeCURrentLIMit = 1006,         // #1006  T_Q15             
	_muLANuchPADPWMLOAd = 1007,             // #1007  T_U16             
	_muOVERCURrentPROtection = 1008,        // #1008  T_Q15             
	_muOVERVOLtagePROtection = 1009,        // #1009  T_Q15             
	_muDACCHAnnel = 1010,                   // #1010  T_U16             // 1->A CH ; 2->B CH ; 3->ALL CH
	_muMEAsureTEMperature = 1011,           // #1011  T_Q15             
	_muMEAsureVOLtageOUTPut = 1012,         // #1012  T_Q15             
	_muMEAsureVOLtageINPUt = 1013,          // #1013  T_Q15             
	_muMEAsureCURrentOUTPut = 1014,         // #1014  T_Q15             
	_muMEAsureINDUctorCURrent = 1015,       // #1015  T_Q15             
	_muFIRmwareBUIldDATe0 = 1016,           // #1016  T_U32             
	_muFIRmwareBUIldDATe1 = 1017,           // #1017  T_U32             
    _end_of_1000_id = 17
};

enum {
	_muVOLtageLOOpkp0 = 1030,               // #1030  T_F32             
	_muVOLtageLOOpkp1 = 1031,               // #1031  T_F32             
	_muVOLtageLOOpki0 = 1032,               // #1032  T_F32             
	_muVOLtageLOOpki1 = 1033,               // #1033  T_F32             
	_muCURrentLOOpkp0 = 1034,               // #1034  T_F32             
	_muCURrentLOOpkp1 = 1035,               // #1035  T_F32             
	_muCURrentLOOpki0 = 1036,               // #1036  T_F32             
	_muCURrentLOOpki1 = 1037,               // #1037  T_F32             
	_muOPENLOOpGAIn0 = 1038,                // #1038  T_F32             
	_muOPENLOOpGAIn1 = 1039,                // #1039  T_F32             
	_muOUTPutPWM0 = 1040,                   // #1040  T_F32             
	_muOUTPutPWM1 = 1041,                   // #1041  T_F32             
	_muHEArtbeatC280 = 1042,                // #1042  T_U32             
	_muHEArtbeatC281 = 1043,                // #1043  T_U32             
	_muHEArtbeatCLA0 = 1044,                // #1044  T_U32             
	_muHEArtbeatCLA1 = 1045,                // #1045  T_U32             
    _end_of_1030_id = 8
};

enum {
	_muCOUntryCODe = 9000,                  // #9000  T_U16             
	_muVENderid = 9001,                     // #9001  T_U16             
	_muBUIldDATe0 = 9002,                   // #9002  T_U32             
	_muBUIldDATe1 = 9003,                   // #9003  T_U32             
    _end_of_9000_id = 3
};

typedef union { 
    uint16_t u16MbusData[44];
    struct { 
		uint16_t u16COMmonHEAder;
		uint16_t u16COMmonLENgth;
		uint16_t u16MAChineINFOrmationOFFSet;
		uint16_t u16USERPARameterOFFSet;
		uint16_t u16ADVAncePARameterOFFSet;
		uint16_t u16COMmonCHEcksum;
		uint16_t u16CLACONtrolSTAtus;
		uint16_t u16CLAERROrSTAtus;
		uint16_t u16ENABlePWM;
		uint16_t u16CONtrolMODe;
		int16_t s16VOLtageREFerence;
		int16_t s16POSitiveCURrentLIMit;
		int16_t s16NEGativeCURrentLIMit;
		uint16_t u16LANuchPADPWMLOAd;
		int16_t s16OVERCURrentPROtection;
		int16_t s16OVERVOLtagePROtection;
		uint16_t u16DACCHAnnel;
		int16_t s16MEAsureTEMperature;
		int16_t s16MEAsureVOLtageOUTPut;
		int16_t s16MEAsureVOLtageINPUt;
		int16_t s16MEAsureCURrentOUTPut;
		int16_t s16MEAsureINDUctorCURrent;
		uint32_t u32FIRmwareBUIldDATe;
		float32_t f32VOLtageLOOpkp;
		float32_t f32VOLtageLOOpki;
		float32_t f32CURrentLOOpkp;
		float32_t f32CURrentLOOpki;
		float32_t f32OPENLOOpGAIn;
		float32_t f32OUTPutPWM;
		uint32_t u32HEArtbeatC28;
		uint32_t u32HEArtbeatCLA;
		uint16_t u16COUntryCODe;
		uint16_t u16VENderid;
		uint32_t u32BUIldDATe;
    }; 
} REG_MBUSDATA;
extern REG_MBUSDATA regMbusData;
extern int chkValidAddress(uint16_t addr);
extern uint16_t getModbusData(uint16_t addr);
extern uint16_t setModbusData(uint16_t addr, uint16_t data);




#endif /* MBCMD_H_ */

