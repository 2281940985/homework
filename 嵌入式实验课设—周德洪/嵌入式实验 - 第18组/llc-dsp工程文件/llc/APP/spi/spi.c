/*
 * spi.c
 *
 *  Created on: 2018-2-3
 *      Author: Administrator
 */


#include "spi.h"


void SPIA_Init(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
	EDIS;

	InitSpiaGpio();

	// Initialize SPI FIFO registers
	SpiaRegs.SPIFFTX.all=0xE040;//清除发送中断
	SpiaRegs.SPIFFRX.all=0x204f;//接受16位
	SpiaRegs.SPIFFCT.all=0x0;//清除计数器


	SpiaRegs.SPICCR.all =0x000F;	             // 复位, rising edge, 16-bit char bits
	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
	                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x007F;
	SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset自测模式并从复位状态解放
	SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission

}

Uint16 SPIA_SendReciveData(Uint16 dat)
{
	// Transmit data
	SpiaRegs.SPITXBUF=dat;

	// Wait until data is received
	while(SpiaRegs.SPIFFRX.bit.RXFFST !=1);//等于1时检测到有数据然后跳出才输出

	return SpiaRegs.SPIRXBUF;
}
