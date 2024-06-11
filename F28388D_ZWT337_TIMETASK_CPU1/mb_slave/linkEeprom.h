/*
 *  File Name: linkEeprom.h
 *
 *  Created on: 5/13/2024
 *  Author: CODY
 */

typedef struct {
    uint16_t size;
    void *ptr;
} EE_REG;
typedef EE_REG * HAL_EEREG;

#define _BLK16_USERREGS	7
uint16_t blkUserRegs[_BLK16_USERREGS];
const EE_REG regUserRegs[4] = {
              {2, (void*)&sDrv.f32RemoteVref},
              {2, (void*)&sDrv.f32IrefLimitP},
              {2, (void*)&sDrv.f32IrefLimitN},
              {1, (void*)&blkUserRegs[6]}};
#define _TABLE_USERREGS	4

#define _BLK16_BOARDREGS	25
uint16_t blkBoardRegs[_BLK16_BOARDREGS];
const EE_REG regBoardRegs[7] = {
              {4, (void*)&sDrv.sLoopV.f32Kp},
              {4, (void*)&sDrv.sLoopV.f32Ki},
              {4, (void*)&sDrv.sLoopI.f32Kp},
              {4, (void*)&sDrv.sLoopI.f32Ki},
              {4, (void*)&sDrv.f32OpenGain},
              {4, (void*)&sDrv.f32PwmPU},
              {1, (void*)&blkBoardRegs[24]}};
#define _TABLE_BOARDREGS	7

