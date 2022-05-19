#ifndef __VC5509_H
#define __VC5509_H

#include "scancode.h"

// emif  --------------------------------------------------------
/*
#define EMIF_GCTL       0x01800000
#define EMIF_CE1        0x01800004
#define EMIF_CE0        0x01800008
#define EMIF_CE2        0x01800010
#define EMIF_CE3        0x01800014
#define EMIF_SDRAMCTL   0x01800018
#define EMIF_SDRAMTIM   0x0180001C
#define EMIF_SDRAMEXT   0x01800020
#define EMIF_CCFG       0x01840000;
*/
// interrupt  --------------------------------------------------
/*
#define IMH (*(unsigned int *)0x19c0000)
#define IML (*(unsigned int *)0x19c0004)
*/
// timer  -------------------------------------------------------
/*
#define TIMER1CTL (*(unsigned int *)0x01980000)
#define TIMER1PRD (*(unsigned int *)0x01980004)
*/
// McBSP0  ------------------------------------------------------
#define SPCR0 (*(unsigned int *)0x018c0008)
#define PCR0 (*(unsigned int *)0x018c0024)
#define SPCR01 (*(unsigned int *)0x01900008)
#define SPCR02 (*(unsigned int *)0x0)
// McBSP1  ------------------------------------------------------

#define SPCR2_1 (*SPCR21)
#define PCR1 (*PCR_1)

// ICETEK-VC5509-A -----------------------------------------------
#define LBDS (*((unsigned int *)0x400001))
#define DIPS (*(unsigned int *)0x400002)
// ICETEK-CTR  --------------------------------------------------
#define CTRGR (*(unsigned int *)0x600800)		//ȫ�ֿ��ƼĴ���
#define CTRKEY (*(unsigned int *)0x602800)		//�������ݻض��Ĵ���
#define CTRCLKEY (*(unsigned int *)0x600801)	//������̼Ĵ���
#define CTRLA (*(unsigned int *)0x602802)		//��������ܿ��ƼĴ���
#define CTRLR (*(unsigned int *)0x602803)		//�������ƼĴ���
#define CTRLCDCMDR (*(unsigned int *)0x602800)	//Һ����Ļָ��Ĵ���
#define CTRLCDCR (*(unsigned int *)0x600801)	//Һ����Ļ�����Ĵ���
#define CTRLCDLCR (*(unsigned int *)0x602801)	//�����Ļ����д�Ĵ���
#define CTRLCDRCR (*(unsigned int *)0x600802)	//�Ұ���Ļ����д�Ĵ���
// Special values -----------------------------------------------
#define LCDCMDTURNON 0x3f
#define LCDCMDTURNOFF 0x3e
#define LCDCMDSTARTLINE 0xc0
#define LCDCMDPAGE 0xb8
#define LCDCMDVERADDRESS 0x40
// C6713DSP Registers  ------------------------------------------
//cregister unsigned int IER,IFR,CSR,ICR,ISTP;

// Variables


// Functions
void InitInterrupt(void);			// ��ʼ���ж�
void InitCTR();						// ��ʼ��ICETEK-CTR
void CloseCTR();					// �ر�ICETEK-CTR�ϸ��豸
void Delay(unsigned int nTime);		// ��ʱ�ӳ���
void Delay1(unsigned int nTime);	// ��ʱ�ӳ���(��LED��ʾˢ��)
unsigned char GetKey();				// ��ȡ��������
void RefreshLEDArray();				// ˢ�·��������������ʾ
void SetLEDArray(int nNumber);		// �޸ķ��������������ʾ����
char ConvertScanToChar(unsigned char cScanCode);	// ������ɨ����ת�����ַ�
void LCDCMD(unsigned char dbCommand);	// ��Һ����ʾ����������
void LCDWriteLeft(unsigned char dbData);	// дҺ����ʾ�������
void LCDWriteRight(unsigned char dbData);
void LCDCLS();							// ���Һ����ʾ����ʾ
void TurnOnLCD();						// ��Һ����ʾ��
extern unsigned int ncode;





#endif






