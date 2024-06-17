/*
 * tlv5620.c
 *
 *  Created on: 2018-3-1
 *      Author: Administrator
 */

#include "tlv5620.h"


void TLV5620_Init(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
	EDIS;

	/*��ʼ��GPIO;*/
	InitSpiaGpio();

	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0; // ����GPIOΪGPIO��
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;      // ����GPIO�������
	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;      // ��ֹ���� GPIO����
	EDIS;

	SpiaRegs.SPICCR.all =0x0a;///�����ʼ״̬��������������������Բ��ֹ��11λ����ģʽ
	SpiaRegs.SPICTL.all =0x0006; // ʹ������ģʽ��������λ��ʹ���������ͣ���ֹ����
		                            //����жϣ���ֹSPI�жϣ�
	SpiaRegs.SPIBRR =0x0031;	//SPI������=37.5M/50	=0.75MHZ��
	SpiaRegs.SPICCR.all =0x8a; //�˳���ʼ״̬��
	SpiaRegs.SPIPRI.bit.FREE = 1;  // ��������

	SET_LOAD;
}


///���Ҫ֪������������ĸ��������ĺ���,channel��4��ͨ���ĵ�ַ��00��01��10��11��
///                                     rng�������Χ�ı�����������0��1��
///                                     dat��0~256����
void DAC_SetChannelData(unsigned char channel,unsigned char rng,unsigned char dat)
{
	Uint16 dacvalue=0;

	//ע���������Ч������11λ��SPI��ʼ����Ҳ�����˶���
	dacvalue = ((channel<<14) | (rng<<13) | (dat<<5));

	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG ==1);//�ж�SPI�ķ��ͻ������Ƿ��ǿյ�,����0��д����
	SpiaRegs.SPITXBUF = dacvalue;	//�ѷ��͵�����д��SPI���ͻ�����
	while( SpiaRegs.SPISTS.bit.BUFFULL_FLAG==1);		//�����ͻ�������������־λʱ,��ʼ��������

	ClEAR_LOAD;//�½��ش�
	DELAY_US(2);

	SET_LOAD;
	DELAY_US(10);

}


