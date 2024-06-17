/*
 * main.c
 *
 *  Created on: 2023��5��24��
 *      Author:
 */

#include "DSP2833x_Device.h"       // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"     // DSP2833x Examples Include File
#include "adc.h"
#include "epwm.h"
#include <math.h>
#include "Solar_F.h"
#include "ABC_DQ0_POS_F.h"

//ϵͳ����
#define pi   3.14159265358979
#define sqt  1.73205080756887                                      //sqrt3
#define Tsp  0.0001                                                //IGBT����Ƶ��  10k
#define Ts   0.0001                                                //pi����ʱ��
#define udc  660                                                   //ֱ��Դ��ѹ
//#define BUFF_SIZE  7
float SampleTable[6];
//Uint16 i;

//�ռ�ʸ�����Ʊ���
int   ma,mb,mc,sector_tmp,sector;                                  //��������
float u1,u2,u3;
float t0,t1,t2,t3,t4,t5,t6,ta,tb,tc;                               //����ռ�ձ�
float duty_a=0.5,duty_b=0.5,duty_c=0.5;                            //��ʼռ�ձ� svpwm����ֵ

//pi���Ʋ���
//#define kp1  0.25
//#define ki1  0
//#define kp2  0.45
//#define ki2  0

//pi���Ʊ���
float ua,ub,uc,ia,ib,ic,ila,ilb,ilc,the;                            //����ֵ
float ud,uq,id,iq,ild,ilq;                                          //����ת��
float ud_ref,uq_ref,ua_ref,ub_ref,uc_ref;                                  //��ѹ�ο�ֵ
float w=50,l=3e-3,c=15e-6;                                          //�������
float kp1=0.001;
float ki1=0;
float kp2=0.001;
float ki2=0;
//pi�����м����
float error_ud=0,error_uq=0,error_id=0,error_iq=0;                  //���e��k��
float error_ud_pre=0,error_uq_pre=0,error_id_pre=0,error_iq_pre=0;  //���e��k-1��
float integral_ud=0,integral_uq=0,integral_id=0,integral_iq=0;      //����ֵ
float ud_out,uq_out,id_out,iq_out;                                  //pi���������
float ild_ref,ilq_ref;                                              //�⻷��� �ڻ�����
float u_d,u_q,u_alpha,u_beta;                                       //�ڻ���� ��ѹ�ο�ʸ��

////���໷ �ṹ��
SPLL_3ph_SRF_F spll1;
ABC_DQ0_POS_F abc_dq0_pos1;

//��������
__interrupt void adc_isr(void);
void svpwm(float u_alpha,float u_beta);

void main(void)
{

    InitSysCtrl();                             //ϵͳ���Ƴ�ʼ��
    InitGpio();                                //��ʼ��GPIO
    InitEPwm1Gpio();                           //GPIO0-GPIO7��Ϊ���蹦��
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();

    ABC_DQ0_POS_F_init(&abc_dq0_pos1);
    SPLL_3ph_SRF_F_init(50,0.0001,&spll1);     //���໷��ʼ��

    //�ж����� step1:ʧ���ж�
    DINT;                                      //ʧ��CPU�ж�
    InitPieCtrl();                             //��ʼ��PIE�ж�
    InitPieVectTable();                        //��ʼ��PIE�ж�������
    IER = 0x0000;                              //CPU�жϱ�־λ����
    IFR = 0x0000;                              //CPU�ж�ʹ��λ����

    //�ж����� step2:�жϵ�ַ���
    EALLOW;
    PieVectTable.EPWM1_INT = &adc_isr;         //�жϺ�����ַ&adc_isr     ����epwm�ж�
//  PieVectTable.ADCINT = &adc_isr;
    EDIS;

    ADC_Init();                                //ADC��ʼ�� ��Ƶ+����

    EPWM1_Init(7500);                          //����PWM��  ���ع�Ƶ��10k
    EPwm1A_SetCompare(duty_a*7500);            //����TBPRD  CMPA  CMPB
    EPwm1B_SetCompare(duty_a*7500);
    EPWM2_Init(7500);
    EPwm2A_SetCompare(duty_b*7500);
    EPwm2B_SetCompare(duty_b*7500);
    EPWM3_Init(7500);
    EPwm3A_SetCompare(duty_c*7500);
    EPwm3B_SetCompare(duty_c*7500);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;    //����epwmģ��ʱ��ʱ�ӣ���֤ͬ��
    EDIS;

    //�ж����� step3:ʹ��PIE���е�ADC�ж�
    IER |= M_INT3;                           //����CPU���ж���ʹ��λ
//  IER |= M_INT1;
//  PieCtrlRegs.PIEIER1.bit.INTx6 = 1;       //ʹ��PIE�жϣ�ADCINT��PIE��1��ĵ�6���ж�
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;       //epwm1�жϣ�Ϊ������ĵ�1���ж�
    EINT;                                    //ʹ�����ж�INTM
    ERTM;                                    //ʹ����ʵʱ�ж�DBGM

    //�ж����� step4:ѭ���ȴ��жϵ���
     for(; ;)
      {
         asm("          NOP");
      }

}

//�жϺ���
//�ж����� step5:�жϷ������
interrupt void adc_isr(void)
{

//����д��
//       for(i = 0; i < BUFF_SIZE; i++)
//               {
//                  SampleTable[i] = 0;
//               }

      while(AdcRegs.ADCST.bit.INT_SEQ1 == 0) //�ȴ�ADC���ж�λΪ1
      {

      }
       AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;   //����������ж�λ

       //��ȡ�Ĵ�����ֵ      ����ֵ����ʵֵ   ƫ��   ����һ�����ӵ�����ϵ��    3.0/4096 0.65
       SampleTable[0] = ((AdcRegs.ADCRESULT0>>4)*0.001127078-1)*330;     //A0 A1 ua ub uc=-ua-ub
       SampleTable[1] = ((AdcRegs.ADCRESULT1>>4)*0.001127078-1)*330;

       SampleTable[2] = ((AdcRegs.ADCRESULT2>>4)*0.001127078-0.15)*200;  //A2 A3 ia ib ic=-ia-ib
       SampleTable[3] = ((AdcRegs.ADCRESULT3>>4)*0.001127078-0.15)*200;


       SampleTable[4] = ((AdcRegs.ADCRESULT4>>4)*0.001127078-0.15)*200;  //A4 A5 ila ilb ilc=-ila-ilb
       SampleTable[5] = ((AdcRegs.ADCRESULT5>>4)*0.001127078-0.15)*200;


//     SampleTable[6] = (AdcRegs.ADCRESULT6>>4)*(3.3/4096)*4;            //A6 the
//     SampleTable[6] =((AdcRegs.ADCRESULT6>>4)*0.001127078-1)*330;      //ua_ref
//     SampleTable[7] =((AdcRegs.ADCRESULT7>>4)*0.001127078-1)*330;      //A7

       //��ѹ������ʵֵ
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

       //���໷  �� ua,ub,uc�ĽǶ�
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

       //����任  ����ֵ��ud uq  id iq  ild ilq    �������໷����������ת��
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

//      �ο���ѹ��ud_ref  uq_ref
       ud_ref=327.126983;
       uq_ref=0;

       //��ѹ�⻷
       error_ud=ud_ref-ud;                                           //d������ѹ
       integral_ud=integral_ud+ki1*Ts*(error_ud_pre+error_ud)*0.5;   //����ֵ
       error_ud_pre=error_ud;
       ud_out=kp1*error_ud+integral_ud;                              //���������

       error_uq=uq_ref-uq;                                           //q������ѹ
       integral_uq=integral_uq+ki1*Ts*(error_uq_pre+error_uq)*0.5;   //����ֵ
       error_uq_pre=error_uq;
       uq_out=kp1*error_uq+integral_uq;                              //���������

//       if(ud_out>300)                                              //�޷�
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

       ild_ref=ud_out+id-uq*w*c;                                    //�����ڻ�������ο�ֵ
       ilq_ref=uq_out+iq+ud*w*c;
//     ild_ref=10;                                                  //������֤
//     ilq_ref=0;

       //�����ڻ�
       error_id=ild_ref-ild;                                        //d��������
       integral_id=integral_id+ki2*Ts*(error_id_pre+error_id)*0.5;  //����ֵ
       error_id_pre=error_id;
       id_out=kp2*error_id+integral_id;                             //���������

       error_iq=ilq_ref-ilq;                                        //d��������
       integral_iq=integral_iq+ki2*Ts*(error_iq_pre+error_iq)*0.5;  //����ֵ
       error_iq_pre=error_iq;
       iq_out=kp2*error_iq+integral_iq;                             //���������

//       if(id_out>30)                                              //�޷�
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
       u_d=ud_ref+id_out-ilq*w*l;                         //�ο�ʸ����ѹ
       u_q=uq_ref+iq_out+ild*w*l;

//     u_d=311;
//     u_q=0;
//     u_d=ud_ref;                                       //�ο�ʸ����ѹ
//     u_q=uq_ref;

       u_alpha=u_d*cos(the)-u_q*sin(the);                //����任
       u_beta=u_d*sin(the)+u_q*cos(the);

       svpwm(u_alpha,u_beta);

//     EPWM1_Init(18749);                                //�������ڵĺ����а����˳�ʼ�����򣬲��ܷ����жϺ�����
       EPwm1A_SetCompare(duty_a*7500);
       EPwm1B_SetCompare(duty_a*7500);
//     EPWM2_Init(18749);
       EPwm2A_SetCompare(duty_b*7500);
       EPwm2B_SetCompare(duty_b*7500);
//     EPWM3_Init(18749);
       EPwm3A_SetCompare(duty_c*7500);
       EPwm3B_SetCompare(duty_c*7500);

       //�ж����� step6:����ж�λ
//     AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
//     AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
//     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

       EPwm1Regs.ETCLR.bit.INT = 1;
       EPwm1Regs.ETCLR.bit.SOCA = 1;
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
       return;
}

//�Ӻ���  SVPWM���Ƶõ�ռ�ձ�
void svpwm(float u_alpha,float u_beta)
{
    //����������ѡ������
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
  //���㿪��ʱ��
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

