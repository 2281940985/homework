/*
 * epwm.c
 */

#include "epwm.h"

//一共配置三组EPWM模块   EPWM1  EPWM2  EPWM3   产生6个PWM  EPWM1A 1B  EPWM2A 2B  EPWM3A 3B 两两互补
//150mhz
//EPWM1 初始化配置
void EPWM1_Init(Uint16 tbprd)
{
    //step1:使能外设时钟，失能时基模块
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //先关闭时基时钟，后面再打开
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;          //使能EPWM1的外设时钟
	EDIS;

    //step2:开启对应GPIO时钟与初始化设置，调用库文件
	InitEPwm1Gpio();

	//step3:配置时基单元TB
	EPwm1Regs.TBCTR = 0x0000;                         //时基计数器清零 CTR=0
	EPwm1Regs.TBPRD = tbprd;                          //时基计数器周期 tbprd
	EPwm1Regs.TBPHS.half.TBPHS = 0;                   //不使用时基相位
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;       //选择同步信号输出源:CTR=0
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //禁止装载相位
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //上下计数模式
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)
	EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)

	//step4:配置比较单元CC  设置CMPA和CMPB
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //选择影子装载寄存器模式
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0装载到当前寄存器中
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPA.half.CMPA = 0;                        //设置CMRA和CMRB
	EPwm1Regs.CMPB = 0;

    //step5:配置动作模块AQ
	//epwma
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;          //向上计数时CTR=CMPA  EPWM1A 置1
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //向下计数时CTR=CMPA  EPWM1A 置0
    //epwmb
	EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;           //向上计数时CTR=CMPB  EPWM1B 置1
	EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;         //向下计数时CTR=CMPB  EPWM1B 置0

     //step6:死区模块DB（上升沿滞后于下降沿的发生，确保有效关断   死区时间  330ns）
	 EPwm1Regs.DBCTL.bit.IN_MODE=2;           //A是上升沿延时输入源 B是下降沿延时输入源
	 EPwm1Regs.DBCTL.bit.POLSEL=2;            //epwmA不翻转，epwmB翻转  形成互补
	 EPwm1Regs.DBCTL.bit.OUT_MODE=3;          //输出源选择 使能双边沿延时
	 EPwm1Regs.DBRED = 50;                    //上升沿延时 RED=DBRED*T(TBCLK) SYSCLKOUT时钟
	 EPwm1Regs.DBFED = 50;                    //下降沿延时 FED=DBRED*T(TBCLK) 150mhz 6.667ns


	 //step7:事件触发模块ET
	 EPwm1Regs.ETSEL.bit.SOCAEN = 1;     // 使能 ePWM1SOCA 信号产生
	 EPwm1Regs.ETSEL.bit.SOCASEL =1;     // 当TBCTR=0时产生 ePWM1SOCA信号
	 EPwm1Regs.ETPS.bit.SOCACNT = 1;     // 计数
	 EPwm1Regs.ETPS.bit.SOCAPRD = 1;     // 在1个事件时产生 ePWM1SOCA信号
	 EPwm1Regs.ETSEL.bit.INTEN=1;
	 EPwm1Regs.ETSEL.bit.INTSEL=1;
	 EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
	 EALLOW;
	 SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   //开启时基时钟，保证同步
	 EDIS;

}

void EPwm1A_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm1B_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPB = val;  //设置占空比
}
// EPWM2 初始化配置
void EPWM2_Init(Uint16 tbprd)
{
    //step1:使能外设时钟，失能时基模块
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //先关闭时基时钟，后面再打开
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;          //使能EPWM2的外设时钟
    EDIS;

    //step2:开启对应GPIO时钟与初始化设置，调用库文件
    InitEPwm2Gpio();

    //step3:配置时基单元TB
    EPwm2Regs.TBCTR = 0x0000;                         //时基计数器清零 CTR=0
    EPwm2Regs.TBPRD = tbprd;                          //时基计数器周期 tbprd
    EPwm2Regs.TBPHS.half.TBPHS = 0;                   //不使用时基相位
    EPwm2Regs.TBCTL.bit.SYNCOSEL =TB_SYNC_IN;         //同步输入信号为EPWM1的CTR=ZERO
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //禁止装载相位
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //上下计数模式
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)

    //step4:配置比较单元CC  设置CMPA和CMPB
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //选择影子装载寄存器模式
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0装载到当前寄存器中
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPA.half.CMPA = 0;                        //设置CMRA和CMRB
    EPwm2Regs.CMPB = 0;

    //step5:配置动作模块AQ

    //epwma
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;          //向上计数时CTR=CMPA  EPWM2A 置1
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //向下计数时CTR=CMPA  EPWM2A 置0

    //epwmb
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;         //向上计数时CTR=CMPB  EPWM2B 置0
    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;       //向下计数时CTR=CMPB  EPWM2B 置1

     //step6:死区模块DB（上升沿滞后于下降沿的发生，确保有效关断   死区时间  330ns）
     EPwm2Regs.DBCTL.bit.IN_MODE=2;        //A是上升沿延时输入源 B是下降沿延时输入源
     EPwm2Regs.DBCTL.bit.POLSEL=2;         //epwmA不翻转，epwmB翻转  形成互补
     EPwm2Regs.DBCTL.bit.OUT_MODE=3;       //输出源选择 使能双边沿延时
     EPwm2Regs.DBRED = 30;                 //上升沿延时 RED=DBRED*T(TBCLK) SYSCLKOUT时钟
     EPwm2Regs.DBFED = 30;                 //下降沿延时 FED=DBRED*T(TBCLK) 150mhz 6.667ns
     //step7:事件触发模块ET
     EPwm2Regs.ETSEL.bit.SOCAEN = 1;     // 使能 ePWM2SOCA 信号产生
     EPwm2Regs.ETSEL.bit.SOCASEL =1;    // 当TBCTR=0时产生 ePWM2SOCA信号
     EPwm2Regs.ETPS.bit.SOCAPRD = 1;     // 在第1个事件时产生 ePWM2SOCA信号


     EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // 开启时基时钟，保证同步
     EDIS;

}

void EPwm2A_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm2B_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPB = val;            //设置占空比
}
//EPWM3 初始化配置
void EPWM3_Init(Uint16 tbprd)
{
    //step1:使能外设时钟，失能时基模块
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //先关闭时基时钟，后面再打开
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;          //使能EPWM3的外设时钟
    EDIS;

    //step2:开启对应GPIO时钟与初始化设置，调用库文件
    InitEPwm3Gpio();

    //step3:配置时基单元TB
    EPwm3Regs.TBCTR = 0x0000;                         //时基计数器清零 CTR=0
    EPwm3Regs.TBPRD = tbprd;                          //时基计数器周期 tbprd
    EPwm3Regs.TBPHS.half.TBPHS = 0;                   //不使用时基相位
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;        //同步输入信号为EPWM1的CTR=ZERO
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //禁止装载相位
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //上下计数模式
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)
    EPwm3Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //不分频 TBCLK=SYSCLK/(HSPCLK*CLKDIV)

    //step4:配置比较单元CC  设置CMPA和CMPB
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //选择影子装载寄存器模式
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0装载到当前寄存器中
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPA.half.CMPA = 0;                        //设置CMRA和CMRB
    EPwm3Regs.CMPB = 0;

    //step5:配置动作模块AQ

    //epwma
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;          //向上计数时CTR=CMPA  EPWM3A 置1
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //向下计数时CTR=CMPA  EPWM3A 置0

    //epwmb
    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;          //向上计数时CTR=CMPB  EPWM3B 置0
    EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;         //向下计数时CTR=CMPB  EPWM3B 置1

     //step6:死区模块DB（上升沿滞后于下降沿的发生，确保有效关断   死区时间  260ns）
     EPwm3Regs.DBCTL.bit.IN_MODE=2;        //A是上升沿延时输入源 B是下降沿延时输入源
     EPwm3Regs.DBCTL.bit.POLSEL=2;         //epwmA不翻转，epwmB翻转  形成互补
     EPwm3Regs.DBCTL.bit.OUT_MODE=3;       //输出源选择 使能双边沿延时
     EPwm3Regs.DBRED = 50;                 //上升沿延时 RED=DBRED*T(TBCLK) SYSCLKOUT时钟
     EPwm3Regs.DBFED = 50;                 //下降沿延时 FED=DBRED*T(TBCLK) 150mhz 6.667ns

     //step7:事件触发模块ET
      EPwm3Regs.ETSEL.bit.SOCAEN = 1;     // 使能 ePWM3SOCA 信号产生
      EPwm3Regs.ETSEL.bit.SOCASEL =1;     // 当TBCTR=0时产生 ePWM3SOCA信号
      EPwm3Regs.ETPS.bit.SOCAPRD = 1;     // 在第1个事件时产生 ePWM3SOCA信号

     EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // 开启时基时钟，保证同步
     EDIS;

}

void EPwm3A_SetCompare(Uint16 val)
{
    EPwm3Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm3B_SetCompare(Uint16 val)
{
    EPwm3Regs.CMPB = val;  //设置占空比
}


