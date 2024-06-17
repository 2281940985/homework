/*
 * adc.c
 */

// ADC�Ĵ������ò���

#include "adc.h"

void ADC_Init(void)
{
	//step1��ADCʱ������  HSPCLK = SYSCLKOUT/(2*HISPCP)
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; //ʹ��ADC����ʱ��
	EDIS;
	EALLOW;
	SysCtrlRegs.HISPCP.all = 3;          //��Ƶ  ADCʱ����߿���Ϊ25MHz  HSPCLK=150/2*3=25MHZ
	EDIS;

	//step2�� ADC��ʼ������
	InitAdc();

	//step3��ADC������ʽ���ã�������ʽ������Ƶ�ʡ�����ͨ������
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;          // 2��Ƶ  HSPCLK/2=12.5MHZ
	AdcRegs.ADCTRL1.bit.CPS = 0;                 // ����Ƶ 12.5MHZ
	AdcRegs.ADCTRL1.bit.ACQ_PS =0xf;             // S/Hʱ������15+1=16��ADCLK
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;            // ��������ģʽ
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;            // ָ�븴λ
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;            // ����������ģʽ

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x6;      //������ͨ����Ϊ6+1=7

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;       //ADCINA0
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;       //ADCINA1

	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;       //ADCINA2
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;       //ADCINA3

	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;       //ADCINA4
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;       //ADCINA5

	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;       //ADCINA6
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;       //ADCINA7

	//step4������ADC������ʽ
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;      // ����ePWM SOCA�����ź�����SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;        // ʹ��SEQ1�ж� ����adc��CPU��������

	//����ģʽ��ֻ��Ҫ����һ���жϼ���   һ��������ĸ��һ��������ĸ���



}
