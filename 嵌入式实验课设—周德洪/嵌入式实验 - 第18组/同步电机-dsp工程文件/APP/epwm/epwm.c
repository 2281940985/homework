/*
 * epwm.c
 */

#include "epwm.h"

//һ����������EPWMģ��   EPWM1  EPWM2  EPWM3   ����6��PWM  EPWM1A 1B  EPWM2A 2B  EPWM3A 3B ��������
//150mhz
//EPWM1 ��ʼ������
void EPWM1_Init(Uint16 tbprd)
{
    //step1:ʹ������ʱ�ӣ�ʧ��ʱ��ģ��
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //�ȹر�ʱ��ʱ�ӣ������ٴ�
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;          //ʹ��EPWM1������ʱ��
	EDIS;

    //step2:������ӦGPIOʱ�����ʼ�����ã����ÿ��ļ�
	InitEPwm1Gpio();

	//step3:����ʱ����ԪTB
	EPwm1Regs.TBCTR = 0x0000;                         //ʱ������������ CTR=0
	EPwm1Regs.TBPRD = tbprd;                          //ʱ������������ tbprd
	EPwm1Regs.TBPHS.half.TBPHS = 0;                   //��ʹ��ʱ����λ
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;       //ѡ��ͬ���ź����Դ:CTR=0
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //��ֹװ����λ
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //���¼���ģʽ
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)
	EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)

	//step4:���ñȽϵ�ԪCC  ����CMPA��CMPB
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //ѡ��Ӱ��װ�ؼĴ���ģʽ
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0װ�ص���ǰ�Ĵ�����
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPA.half.CMPA = 0;                        //����CMRA��CMRB
	EPwm1Regs.CMPB = 0;

    //step5:���ö���ģ��AQ
	//epwma
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;          //���ϼ���ʱCTR=CMPA  EPWM1A ��1
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //���¼���ʱCTR=CMPA  EPWM1A ��0
    //epwmb
	EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;           //���ϼ���ʱCTR=CMPB  EPWM1B ��1
	EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;         //���¼���ʱCTR=CMPB  EPWM1B ��0

     //step6:����ģ��DB���������ͺ����½��صķ�����ȷ����Ч�ض�   ����ʱ��  330ns��
	 EPwm1Regs.DBCTL.bit.IN_MODE=2;           //A����������ʱ����Դ B���½�����ʱ����Դ
	 EPwm1Regs.DBCTL.bit.POLSEL=2;            //epwmA����ת��epwmB��ת  �γɻ���
	 EPwm1Regs.DBCTL.bit.OUT_MODE=3;          //���Դѡ�� ʹ��˫������ʱ
	 EPwm1Regs.DBRED = 50;                    //��������ʱ RED=DBRED*T(TBCLK) SYSCLKOUTʱ��
	 EPwm1Regs.DBFED = 50;                    //�½�����ʱ FED=DBRED*T(TBCLK) 150mhz 6.667ns


	 //step7:�¼�����ģ��ET
	 EPwm1Regs.ETSEL.bit.SOCAEN = 1;     // ʹ�� ePWM1SOCA �źŲ���
	 EPwm1Regs.ETSEL.bit.SOCASEL =1;     // ��TBCTR=0ʱ���� ePWM1SOCA�ź�
	 EPwm1Regs.ETPS.bit.SOCACNT = 1;     // ����
	 EPwm1Regs.ETPS.bit.SOCAPRD = 1;     // ��1���¼�ʱ���� ePWM1SOCA�ź�
	 EPwm1Regs.ETSEL.bit.INTEN=1;
	 EPwm1Regs.ETSEL.bit.INTSEL=1;
	 EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
	 EALLOW;
	 SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   //����ʱ��ʱ�ӣ���֤ͬ��
	 EDIS;

}

void EPwm1A_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPA.half.CMPA = val;  //����ռ�ձ�
}
void EPwm1B_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPB = val;  //����ռ�ձ�
}
// EPWM2 ��ʼ������
void EPWM2_Init(Uint16 tbprd)
{
    //step1:ʹ������ʱ�ӣ�ʧ��ʱ��ģ��
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //�ȹر�ʱ��ʱ�ӣ������ٴ�
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;          //ʹ��EPWM2������ʱ��
    EDIS;

    //step2:������ӦGPIOʱ�����ʼ�����ã����ÿ��ļ�
    InitEPwm2Gpio();

    //step3:����ʱ����ԪTB
    EPwm2Regs.TBCTR = 0x0000;                         //ʱ������������ CTR=0
    EPwm2Regs.TBPRD = tbprd;                          //ʱ������������ tbprd
    EPwm2Regs.TBPHS.half.TBPHS = 0;                   //��ʹ��ʱ����λ
    EPwm2Regs.TBCTL.bit.SYNCOSEL =TB_SYNC_IN;         //ͬ�������ź�ΪEPWM1��CTR=ZERO
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //��ֹװ����λ
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //���¼���ģʽ
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)

    //step4:���ñȽϵ�ԪCC  ����CMPA��CMPB
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //ѡ��Ӱ��װ�ؼĴ���ģʽ
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0װ�ص���ǰ�Ĵ�����
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPA.half.CMPA = 0;                        //����CMRA��CMRB
    EPwm2Regs.CMPB = 0;

    //step5:���ö���ģ��AQ

    //epwma
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;          //���ϼ���ʱCTR=CMPA  EPWM2A ��1
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //���¼���ʱCTR=CMPA  EPWM2A ��0

    //epwmb
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;         //���ϼ���ʱCTR=CMPB  EPWM2B ��0
    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;       //���¼���ʱCTR=CMPB  EPWM2B ��1

     //step6:����ģ��DB���������ͺ����½��صķ�����ȷ����Ч�ض�   ����ʱ��  330ns��
     EPwm2Regs.DBCTL.bit.IN_MODE=2;        //A����������ʱ����Դ B���½�����ʱ����Դ
     EPwm2Regs.DBCTL.bit.POLSEL=2;         //epwmA����ת��epwmB��ת  �γɻ���
     EPwm2Regs.DBCTL.bit.OUT_MODE=3;       //���Դѡ�� ʹ��˫������ʱ
     EPwm2Regs.DBRED = 30;                 //��������ʱ RED=DBRED*T(TBCLK) SYSCLKOUTʱ��
     EPwm2Regs.DBFED = 30;                 //�½�����ʱ FED=DBRED*T(TBCLK) 150mhz 6.667ns
     //step7:�¼�����ģ��ET
     EPwm2Regs.ETSEL.bit.SOCAEN = 1;     // ʹ�� ePWM2SOCA �źŲ���
     EPwm2Regs.ETSEL.bit.SOCASEL =1;    // ��TBCTR=0ʱ���� ePWM2SOCA�ź�
     EPwm2Regs.ETPS.bit.SOCAPRD = 1;     // �ڵ�1���¼�ʱ���� ePWM2SOCA�ź�


     EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // ����ʱ��ʱ�ӣ���֤ͬ��
     EDIS;

}

void EPwm2A_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPA.half.CMPA = val;  //����ռ�ձ�
}
void EPwm2B_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPB = val;            //����ռ�ձ�
}
//EPWM3 ��ʼ������
void EPWM3_Init(Uint16 tbprd)
{
    //step1:ʹ������ʱ�ӣ�ʧ��ʱ��ģ��
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;           //�ȹر�ʱ��ʱ�ӣ������ٴ�
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;          //ʹ��EPWM3������ʱ��
    EDIS;

    //step2:������ӦGPIOʱ�����ʼ�����ã����ÿ��ļ�
    InitEPwm3Gpio();

    //step3:����ʱ����ԪTB
    EPwm3Regs.TBCTR = 0x0000;                         //ʱ������������ CTR=0
    EPwm3Regs.TBPRD = tbprd;                          //ʱ������������ tbprd
    EPwm3Regs.TBPHS.half.TBPHS = 0;                   //��ʹ��ʱ����λ
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;        //ͬ�������ź�ΪEPWM1��CTR=ZERO
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;           //��ֹװ����λ
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    //���¼���ģʽ
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;            //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)
    EPwm3Regs.TBCTL.bit.CLKDIV=TB_DIV1;               //����Ƶ TBCLK=SYSCLK/(HSPCLK*CLKDIV)

    //step4:���ñȽϵ�ԪCC  ����CMPA��CMPB
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;          //ѡ��Ӱ��װ�ؼĴ���ģʽ
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;        //CTR=0װ�ص���ǰ�Ĵ�����
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPA.half.CMPA = 0;                        //����CMRA��CMRB
    EPwm3Regs.CMPB = 0;

    //step5:���ö���ģ��AQ

    //epwma
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;          //���ϼ���ʱCTR=CMPA  EPWM3A ��1
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;        //���¼���ʱCTR=CMPA  EPWM3A ��0

    //epwmb
    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;          //���ϼ���ʱCTR=CMPB  EPWM3B ��0
    EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;         //���¼���ʱCTR=CMPB  EPWM3B ��1

     //step6:����ģ��DB���������ͺ����½��صķ�����ȷ����Ч�ض�   ����ʱ��  260ns��
     EPwm3Regs.DBCTL.bit.IN_MODE=2;        //A����������ʱ����Դ B���½�����ʱ����Դ
     EPwm3Regs.DBCTL.bit.POLSEL=2;         //epwmA����ת��epwmB��ת  �γɻ���
     EPwm3Regs.DBCTL.bit.OUT_MODE=3;       //���Դѡ�� ʹ��˫������ʱ
     EPwm3Regs.DBRED = 50;                 //��������ʱ RED=DBRED*T(TBCLK) SYSCLKOUTʱ��
     EPwm3Regs.DBFED = 50;                 //�½�����ʱ FED=DBRED*T(TBCLK) 150mhz 6.667ns

     //step7:�¼�����ģ��ET
      EPwm3Regs.ETSEL.bit.SOCAEN = 1;     // ʹ�� ePWM3SOCA �źŲ���
      EPwm3Regs.ETSEL.bit.SOCASEL =1;     // ��TBCTR=0ʱ���� ePWM3SOCA�ź�
      EPwm3Regs.ETPS.bit.SOCAPRD = 1;     // �ڵ�1���¼�ʱ���� ePWM3SOCA�ź�

     EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // ����ʱ��ʱ�ӣ���֤ͬ��
     EDIS;

}

void EPwm3A_SetCompare(Uint16 val)
{
    EPwm3Regs.CMPA.half.CMPA = val;  //����ռ�ձ�
}
void EPwm3B_SetCompare(Uint16 val)
{
    EPwm3Regs.CMPB = val;  //����ռ�ձ�
}


