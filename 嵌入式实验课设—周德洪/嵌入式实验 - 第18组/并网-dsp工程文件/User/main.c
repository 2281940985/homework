/*
 * main.c
 *
 *  Created on: 2023年5月24日
 *      Author:
 */

#include "DSP2833x_Device.h"       // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"     // DSP2833x Examples Include File
#include "adc.h"
#include "epwm.h"
#include <math.h>
#include "Solar_F.h"
#include "ABC_DQ0_POS_F.h"

//系统常量
#define pi   3.14159265358979
#define sqt  1.73205080756887                                      //sqrt3
#define Tsp  0.0001                                                //IGBT开关频率  10k
#define Ts   0.0001                                                //pi积分时间
#define udc  660                                                   //直流源电压
//#define BUFF_SIZE  7
float SampleTable[6];
//Uint16 i;

//空间矢量调制变量
int   ma,mb,mc,sector_tmp,sector;                                  //计算扇区
float u1,u2,u3;
float t0,t1,t2,t3,t4,t5,t6,ta,tb,tc;                               //计算占空比
float duty_a=0.5,duty_b=0.5,duty_c=0.5;                            //初始占空比 svpwm返回值

//pi控制参数
//#define kp1  0.25
//#define ki1  0
//#define kp2  0.45
//#define ki2  0

//pi控制变量
float ua,ub,uc,ia,ib,ic,ila,ilb,ilc,the;                            //采样值
float ud,uq,id,iq,ild,ilq;                                          //坐标转换
float ud_ref,uq_ref,ua_ref,ub_ref,uc_ref;                                  //电压参考值
float w=50,l=3e-3,c=15e-6;                                          //解耦变量
float kp1=0.001;
float ki1=0;
float kp2=0.001;
float ki2=0;
//pi控制中间变量
float error_ud=0,error_uq=0,error_id=0,error_iq=0;                  //误差e（k）
float error_ud_pre=0,error_uq_pre=0,error_id_pre=0,error_iq_pre=0;  //误差e（k-1）
float integral_ud=0,integral_uq=0,integral_id=0,integral_iq=0;      //积分值
float ud_out,uq_out,id_out,iq_out;                                  //pi控制器输出
float ild_ref,ilq_ref;                                              //外环输出 内环输入
float u_d,u_q,u_alpha,u_beta;                                       //内环输出 电压参考矢量

////锁相环 结构体
SPLL_3ph_SRF_F spll1;
ABC_DQ0_POS_F abc_dq0_pos1;

//函数声明
__interrupt void adc_isr(void);
void svpwm(float u_alpha,float u_beta);

void main(void)
{

    InitSysCtrl();                             //系统控制初始化
    InitGpio();                                //初始化GPIO
    InitEPwm1Gpio();                           //GPIO0-GPIO7设为外设功能
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();

    ABC_DQ0_POS_F_init(&abc_dq0_pos1);
    SPLL_3ph_SRF_F_init(50,0.0001,&spll1);     //锁相环初始化

    //中断配置 step1:失能中断
    DINT;                                      //失能CPU中断
    InitPieCtrl();                             //初始化PIE中断
    InitPieVectTable();                        //初始化PIE中断向量表
    IER = 0x0000;                              //CPU中断标志位清零
    IFR = 0x0000;                              //CPU中断使能位清零

    //中断配置 step2:中断地址入口
    EALLOW;
    PieVectTable.EPWM1_INT = &adc_isr;         //中断函数地址&adc_isr     采用epwm中断
//  PieVectTable.ADCINT = &adc_isr;
    EDIS;

    ADC_Init();                                //ADC初始化 分频+采样

    EPWM1_Init(7500);                          //生成PWM波  开关管频率10k
    EPwm1A_SetCompare(duty_a*7500);            //设置TBPRD  CMPA  CMPB
    EPwm1B_SetCompare(duty_a*7500);
    EPWM2_Init(7500);
    EPwm2A_SetCompare(duty_b*7500);
    EPwm2B_SetCompare(duty_b*7500);
    EPWM3_Init(7500);
    EPwm3A_SetCompare(duty_c*7500);
    EPwm3B_SetCompare(duty_c*7500);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;    //开启epwm模块时基时钟，保证同步
    EDIS;

    //中断配置 step3:使能PIE级中的ADC中断
    IER |= M_INT3;                           //开启CPU级中断线使能位
//  IER |= M_INT1;
//  PieCtrlRegs.PIEIER1.bit.INTx6 = 1;       //使能PIE中断：ADCINT是PIE第1组的第6个中断
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;       //epwm1中断，为低三组的第1个中断
    EINT;                                    //使能总中断INTM
    ERTM;                                    //使能总实时中断DBGM

    //中断配置 step4:循环等待中断到来
     for(; ;)
      {
         asm("          NOP");
      }

}

//中断函数
//中断配置 step5:中断服务程序
interrupt void adc_isr(void)
{

//变量写零
//       for(i = 0; i < BUFF_SIZE; i++)
//               {
//                  SampleTable[i] = 0;
//               }

      while(AdcRegs.ADCST.bit.INT_SEQ1 == 0) //等待ADC的中断位为1
      {

      }
       AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;   //清除排序器中断位

       //读取寄存器的值      采样值到真实值   偏置   还有一个板子的自身系数    3.0/4096 0.65
       SampleTable[0] = ((AdcRegs.ADCRESULT0>>4)*0.001127078-1)*330;     //A0 A1 ua ub uc=-ua-ub
       SampleTable[1] = ((AdcRegs.ADCRESULT1>>4)*0.001127078-1)*330;

       SampleTable[2] = ((AdcRegs.ADCRESULT2>>4)*0.001127078-0.15)*200;  //A2 A3 ia ib ic=-ia-ib
       SampleTable[3] = ((AdcRegs.ADCRESULT3>>4)*0.001127078-0.15)*200;


       SampleTable[4] = ((AdcRegs.ADCRESULT4>>4)*0.001127078-0.15)*200;  //A4 A5 ila ilb ilc=-ila-ilb
       SampleTable[5] = ((AdcRegs.ADCRESULT5>>4)*0.001127078-0.15)*200;


//     SampleTable[6] = (AdcRegs.ADCRESULT6>>4)*(3.3/4096)*4;            //A6 the
//     SampleTable[6] =((AdcRegs.ADCRESULT6>>4)*0.001127078-1)*330;      //ua_ref
//     SampleTable[7] =((AdcRegs.ADCRESULT7>>4)*0.001127078-1)*330;      //A7

       //电压电流真实值
       ua=SampleTable[0];
       ub=SampleTable[1];
       uc=-ua-ub;

       ia=SampleTable[2];
       ib=SampleTable[3];
       ic=-ia-ib;

       ila=SampleTable[4];
       ilb=SampleTable[5];
       ilc=-ila-ilb;


//       ua_ref=SampleTable[6];
//       ub_ref=SampleTable[7];
//       uc_ref=-ua_ref-ub_ref;
//       the=SampleTable[6];

       //锁相环  锁 ua,ub,uc的角度
       abc_dq0_pos1.a = ua/330;
       abc_dq0_pos1.b = ub/330;
       abc_dq0_pos1.c = uc/330;
       abc_dq0_pos1.sin = sin(spll1.theta[1]);
       abc_dq0_pos1.cos = cos(spll1.theta[1]);
       ABC_DQ0_POS_F_MACRO(abc_dq0_pos1);
       spll1.v_q[0] = (abc_dq0_pos1.q);
       SPLL_3ph_SRF_F_FUNC(&spll1);
       the=spll1.theta[0];

//     ua=311*cosf(the);
//     ub=311*cosf((the-0.6666667*pi));
//     uc=311*cosf((the+0.6666667*pi));
//     if (the>2*pi)
//       {
//           the=the-2*pi;
//       }
//           the=the+0.01*pi;

       //坐标变换  采样值：ud uq  id iq  ild ilq    利用锁相环来进行坐标转换
       ud=abc_dq0_pos1.q*330;
       uq=abc_dq0_pos1.d*330;
//     ud=(ua*cos(the)+ub*cos(the-0.6666667*pi)+uc*cos(the+0.6666667*pi))*0.6666667;
//     uq=-(ua*sin(the)+ub*sin(the-0.6666667*pi)+uc*sin(the+0.6666667*pi))*0.6666667;

       abc_dq0_pos1.a = ia/30;
       abc_dq0_pos1.b = ib/30;
       abc_dq0_pos1.c = ic/30;
       abc_dq0_pos1.sin = sin(spll1.theta[1]);
       abc_dq0_pos1.cos = cos(spll1.theta[1]);
       ABC_DQ0_POS_F_MACRO(abc_dq0_pos1);
       id=abc_dq0_pos1.q*30;
       iq=abc_dq0_pos1.d*30;

//     id=(ia*cos(the)+ib*cos(the-0.6666667*pi)+ic*cos(the+0.6666667*pi))*0.6666667;
//     iq=-(ia*sin(the)+ib*sin(the-0.6666667*pi)+ic*sin(the+0.6666667*pi))*0.6666667;

       abc_dq0_pos1.a = ila/30;
       abc_dq0_pos1.b = ilb/30;
       abc_dq0_pos1.c = ilc/30;
       abc_dq0_pos1.sin = sin(spll1.theta[1]);
       abc_dq0_pos1.cos = cos(spll1.theta[1]);
       ABC_DQ0_POS_F_MACRO(abc_dq0_pos1);
       ild=abc_dq0_pos1.q*30;
       ilq=abc_dq0_pos1.d*30;

//     ua_ref=sin(w*t*2*pi);
//     ub_ref=sin(w*t*2*pi+0.6666667*pi);
//     uc_ref=sin(w*t*2*pi+0.6666667*2*pi);
//     abc_dq0_pos1.a =ua_ref/330;
//     abc_dq0_pos1.b =ub_ref/330;
//     abc_dq0_pos1.c =uc_ref/330;
//     abc_dq0_pos1.sin = sin(spll1.theta[1]);
//     abc_dq0_pos1.cos = cos(spll1.theta[1]);
//     ud_ref=abc_dq0_pos1.q*330;
//     uq_ref=abc_dq0_pos1.d*330;
//     ild=(ila*cos(the)+ilb*cos(the-0.6666667*pi)+ilc*cos(the+0.6666667*pi))*0.6666667;
//     ilq=-(ila*sin(the)+ilb*sin(the-0.6666667*pi)+ilc*sin(the+0.6666667*pi))*0.6666667;

//      参考电压：ud_ref  uq_ref
       ud_ref=327.126983;
       uq_ref=0;

       //电压外环
       error_ud=ud_ref-ud;                                           //d轴误差电压
       integral_ud=integral_ud+ki1*Ts*(error_ud_pre+error_ud)*0.5;   //积分值
       error_ud_pre=error_ud;
       ud_out=kp1*error_ud+integral_ud;                              //控制器输出

       error_uq=uq_ref-uq;                                           //q轴误差电压
       integral_uq=integral_uq+ki1*Ts*(error_uq_pre+error_uq)*0.5;   //积分值
       error_uq_pre=error_uq;
       uq_out=kp1*error_uq+integral_uq;                              //控制器输出

//       if(ud_out>300)                                              //限幅
//       {
//           ud_out=300;
//       }
//       if(ud_out<-300)
//       {
//           ud_out=-300;
//       }
//       if(uq_out>300)
//       {
//           uq_out=300;
//       }
//       if(uq_out<-300)
//       {
//           uq_out=-300;
//       }

       ild_ref=ud_out+id-uq*w*c;                                    //电流内环的输入参考值
       ilq_ref=uq_out+iq+ud*w*c;
//     ild_ref=10;                                                  //单环验证
//     ilq_ref=0;

       //电流内环
       error_id=ild_ref-ild;                                        //d轴误差电流
       integral_id=integral_id+ki2*Ts*(error_id_pre+error_id)*0.5;  //积分值
       error_id_pre=error_id;
       id_out=kp2*error_id+integral_id;                             //控制器输出

       error_iq=ilq_ref-ilq;                                        //d轴误差电流
       integral_iq=integral_iq+ki2*Ts*(error_iq_pre+error_iq)*0.5;  //积分值
       error_iq_pre=error_iq;
       iq_out=kp2*error_iq+integral_iq;                             //控制器输出

//       if(id_out>30)                                              //限幅
//       {
//           id_out=30;
//       }
//       if(id_out<-30)
//       {
//           id_out=-30;
//       }
//
//       if(iq_out>30)
//       {
//           iq_out=30;
//       }
//       if(iq_out<-30)
//       {
//           iq_out=-30;
//       }
//
       u_d=ud_ref+id_out-ilq*w*l;                         //参考矢量电压
       u_q=uq_ref+iq_out+ild*w*l;

//     u_d=311;
//     u_q=0;
//     u_d=ud_ref;                                       //参考矢量电压
//     u_q=uq_ref;

       u_alpha=u_d*cos(the)-u_q*sin(the);                //坐标变换
       u_beta=u_d*sin(the)+u_q*cos(the);

       svpwm(u_alpha,u_beta);

//     EPWM1_Init(18749);                                //设置周期的函数中包含了初始化程序，不能放在中断函数中
       EPwm1A_SetCompare(duty_a*7500);
       EPwm1B_SetCompare(duty_a*7500);
//     EPWM2_Init(18749);
       EPwm2A_SetCompare(duty_b*7500);
       EPwm2B_SetCompare(duty_b*7500);
//     EPWM3_Init(18749);
       EPwm3A_SetCompare(duty_c*7500);
       EPwm3B_SetCompare(duty_c*7500);

       //中断配置 step6:清除中断位
//     AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
//     AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
//     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

       EPwm1Regs.ETCLR.bit.INT = 1;
       EPwm1Regs.ETCLR.bit.SOCA = 1;
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
       return;
}

//子函数  SVPWM调制得到占空比
void svpwm(float u_alpha,float u_beta)
{
    //计算扇区，选择扇区
    u1=u_beta;
    u2=0.5*sqt*u_alpha-u_beta*0.5;
    u3=-0.5*sqt*u_alpha-u_beta*0.5;
   if (u1>0)
    {
        ma=1;
    }
   else
    {
        ma=0;
    }
   if (u2>0)
    {
        mb=1;
    }
   else
    {
       mb=0;
    }
   if (u3>0)
    {
       mc=1;
    }
   else
    {
       mc=0;
    }
sector_tmp = 4*ma+2*mb+mc;
switch (sector_tmp)
{
    case 6:
        sector = 1;
        break;
    case 4:
        sector = 2;
        break;
    case 5:
        sector = 3;
        break;
    case 1:
        sector = 4;
        break;
    case 3:
        sector = 5;
        break;
    case 2:
        sector = 6;
        break;
//case 3:
//    sector = 1;
//    break;
//case 1:
//    sector = 2;
//    break;
//case 5:
//    sector = 3;
//    break;
//case 4:
//    sector = 4;
//    break;
//case 6:
//    sector = 5;
//    break;
//case 2:
//    sector = 6;
//    break;
}
  //计算开关时间
    switch (sector)
{
    case 1:
        t4 = sqt*Tsp/udc*(0.5*sqt*u_alpha-0.5*u_beta);
        t6 = sqt*Tsp/udc*u_beta;
        t0 = 0.5*(Tsp-t4-t6);
        ta = t4+t6+t0;
        tb = t6+t0;
        tc = t0;
        break;
    case 2:
        t2 = sqt*Tsp/udc*(-0.5*sqt*u_alpha+0.5*u_beta);
        t6 = sqt*Tsp/udc*( 0.5*sqt*u_alpha+0.5*u_beta);
        t0 = 0.5*(Tsp-t2-t6);
        ta = t6+t0;
        tb = t2+t6+t0;
        tc = t0;
        break;
    case 3:
        t3 = sqt*Tsp/udc*(-0.5*sqt*u_alpha-0.5*u_beta);
        t2 = sqt*Tsp/udc*u_beta;
        t0 = 0.5*(Tsp-t2-t3);
        ta = t0;
        tb = t2+t3+t0;
        tc = t3+t0;
        break;
    case 4:
        t3 = sqt*Tsp/udc*(-0.5*sqt*u_alpha+0.5*u_beta);
        t1 = -sqt*Tsp/udc*u_beta;
        t0 =0.5*(Tsp-t1-t3);
        ta = t0;
        tb = t3+t0;
        tc = t1+t3+t0;
        break;
    case 5:
        t5 = sqt*Tsp/udc*(0.5*sqt*u_alpha-0.5*u_beta);
        t1 = sqt*Tsp/udc*(-0.5*sqt*u_alpha-0.5*u_beta);
        t0 = 0.5*(Tsp-t1-t5);
        ta =t5+t0;
        tb = t0;
        tc = t1+t5+t0;
        break;
    case 6:
        t4 = sqt*Tsp/udc*(0.5*sqt*u_alpha+0.5*u_beta);
        t5 = -sqt*Tsp/udc*u_beta;
        t0 = 0.5*(Tsp-t4-t5);
        ta = t4+t5+t0;
        tb = t0;
        tc = t5+t0;
        break;
}
    duty_a=1-(ta/Tsp);
    duty_b=1-(tb/Tsp);
    duty_c=1-(tc/Tsp);

    return;
}

