/*
 * adc.c
 */

// ADC寄存器配置步骤

#include "adc.h"

void ADC_Init(void)
{
	//step1：ADC时钟配置  HSPCLK = SYSCLKOUT/(2*HISPCP)
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; //使能ADC外设时钟
	EDIS;
	EALLOW;
	SysCtrlRegs.HISPCP.all = 3;          //分频  ADC时钟最高可配为25MHz  HSPCLK=150/2*3=25MHZ
	EDIS;

	//step2： ADC初始化设置
	InitAdc();

	//step3：ADC工作方式设置：采样方式、工作频率、采样通道数等
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;          // 2分频  HSPCLK/2=12.5MHZ
	AdcRegs.ADCTRL1.bit.CPS = 0;                 // 不分频 12.5MHZ
	AdcRegs.ADCTRL1.bit.ACQ_PS =0xf;             // S/H时钟脉冲15+1=16个ADCLK
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;            // 连续采样模式
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;            // 指针复位
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;            // 级联排序器模式

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x6;      //最大采样通道数为6+1=7

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;       //ADCINA0
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;       //ADCINA1

	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;       //ADCINA2
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;       //ADCINA3

	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;       //ADCINA4
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;       //ADCINA5

	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;       //ADCINA6
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;       //ADCINA7

	//step4：设置ADC触发方式
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;      // 允许ePWM SOCA触发信号启动SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;        // 使能SEQ1中断 允许adc向CPU发出申请

	//级联模式下只需要开启一个中断即可   一个是物理的概念，一个是软件的概念



}
