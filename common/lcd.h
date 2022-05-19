/*
 * lcd.h
 *
 *  Created on: 2017-3-30
 *      Author: Administrator
 */

#ifndef LCD_H_
#define LCD_H_
#include "ICETEK-VC5509-EDU.h"
#include "include.h"

#define LCDDELAY 1

// ICETEK-CTR  --------------------------------------------------
#define CTRGR (*(unsigned int *)0x600800)
#define CTRKEY (*(unsigned int *)0x602800)
#define CTRCLKEY (*(unsigned int *)0x600801)
#define CTRLA (*(unsigned int *)0x602802)
#define CTRLR (*(unsigned int *)0x602803)
#define CTRLCDCMDR (*(unsigned int *)0x602800)
#define CTRLCDCR (*(unsigned int *)0x600801)
#define CTRLCDLCR (*(unsigned int *)0x602801)
#define CTRLCDRCR (*(unsigned int *)0x600802)
// Special values -----------------------------------------------
#define LCDCMDTURNON 0x3f
#define LCDCMDTURNOFF 0x3e
#define LCDCMDSTARTLINE 0xc0
#define LCDCMDPAGE 0xb8
#define LCDCMDVERADDRESS 0x40
// C6713DSP Registers  ------------------------------------------
//cregister unsigned int IER,IFR,CSR,ICR,ISTP;


#define nMusicNumber 52



// Functions
//void InitInterrupt(void);			// 初始化中断
void Lcd_Show();
void Lcd_Test();
void Lcd_Paint(const uint8 data[]);
void InitCTR();						// 初始化ICETEK-CTR
void CloseCTR();					// 关闭ICETEK-CTR上各设备
void Delay(unsigned int nTime);		// 延时子程序
void Delay1(unsigned int nTime);	// 延时子程序(带LED显示刷新)
unsigned char GetKey();				// 读取键盘输入
void RefreshLEDArray();				// 刷新发光二极管阵列显示
void SetLEDArray(int nNumber);		// 修改发光二极管阵列显示内容
char ConvertScanToChar(unsigned char cScanCode);	// 将键盘扫描码转换成字符
void LCDCMD(unsigned char dbCommand);	// 向液晶显示器发送命令
void LCDWriteLeft(unsigned char dbData);	// 写液晶显示器左半屏
void LCDWriteRight(unsigned char dbData);   // 写液晶屏右半屏
void LCDCLS();							// 清除液晶显示器显示
void TurnOnLCD();						// 打开液晶显示器
void Lcd_Wave();
void Lcd_SimpleWave(int *p,int N);
void Lcd_PrintChar(int x,int y,int c);

void Lcd_Draw_Line(int x, int y) ;
void Lcd_Draw_Line2(int x, int y) ;
void Lcd_Draw_Axes();
void yzhou1();//0-56
void yzhou2();//0-42
void yzhou3();//0-28
void yzhou4();//0-14
void Writee(int wpage,int m);

void Lcd_Tune();
void Lcd_Print(int,int,int,int,int);
void Lcd_PrintF();

void showhz(int flag);
void showvalue(int x, int y ,int n);

#endif /* LCD_H_ */
