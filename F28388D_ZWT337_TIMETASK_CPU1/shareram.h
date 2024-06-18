/*
 * shareram.h
 *
 *  Created on: Mar 4, 2024
 *      Author: cody_chen
 */

#ifndef SHARERAM_H_
#define SHARERAM_H_

#define MBUS_SHARERAM_SIZE    64


typedef volatile struct {
    uint16_t u16RxRAM[MBUS_SHARERAM_SIZE];
    uint16_t u16TxRAM[MBUS_SHARERAM_SIZE];
    uint16_t pushRcnts;
    uint16_t popRcnts;
    uint16_t pushTcnts;
    uint16_t popTcnts;

    uint32_t u32Fsm;
    uint32_t u32Stat;
    uint32_t u32Warning;
    uint32_t u32Error;

    uint16_t u16LED;
}ST_SHARERAM;

extern ST_SHARERAM sAccessCPU1;
extern ST_SHARERAM sReadCPU2;


#endif /* SHARERAM_H_ */
