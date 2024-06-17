/*
 * epwm.h
 */

#ifndef EPWM_H_
#define EPWM_H_

#include "DSP2833x_Device.h"     // DSP2833x 头文件
#include "DSP2833x_Examples.h"   // DSP2833x 例子相关头文件


void EPWM1_Init(Uint16 tbprd);
void EPwm1A_SetCompare(Uint16 val);
void EPwm1B_SetCompare(Uint16 val);

void EPWM2_Init(Uint16 tbprd);
void EPwm2A_SetCompare(Uint16 val);
void EPwm2B_SetCompare(Uint16 val);

void EPWM3_Init(Uint16 tbprd);
void EPwm3A_SetCompare(Uint16 val);
void EPwm3B_SetCompare(Uint16 val);
#endif
