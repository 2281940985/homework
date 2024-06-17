/*
 * adc.c
 *
 *  Created on: 2018-1-29
 *      Author: Administrator
 */

#include "adc.h"




void ADC_Init(void)
{
	// Specific clock setting for this example:
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
	EDIS;

	// Specific clock setting for this example:
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/(2*ADC_MODCLK)设置工作时钟
	EDIS;

	InitAdc();  // For this example, init the ADC

	// Specific ADC setup for this example:
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;//采样保持的频率
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;//不分频
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x1;

	// Start SEQ1
	//设置触发方式
	 AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// 允许ePWM的触发信号启动SEQ1
	 AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // 使能SEQ1中断
}

