#include "key.h"
#include "ICETEK-VC5509-EDU.h"     //ICETEK-VC5509A-S60实验箱扩展接口和控制模块
#include "c5509mmr.h"
//#include "5509.h"
int scanKey=0;
unsigned int ncode;
void interrupt XINT2()
{
	scanKey=GetKey(); //Getkey函数获得键盘值并放入该变量中，以做消抖处理
	scanKey&=0x0ff; //获取键盘值
	Keyshift();
}

void INTR_init( void )
{
	IVPD=0x80;			//DSP中断向量指针设置到80H
	IVPH=0x80;			//主机中断向量指针设置到80H

	IER0=0x08;			//中断使能寄存器IER0第3位置1，开放IV3，即外部中断2（XINT2）
	DBIER0=0x08;			//调试中断寄存器

	IFR0=0xffff;		//中断标志寄存器IFR0清零
	asm(" BCLR INTM");	//开放所有可屏蔽中断

}

void Keyshift()
{  //该实现1-9，10（A）和11（B）
	if(scanKey==1)
	{	LBDS=1;Delay(1500);
		while(1)
		{	scanKey=GetKey();
			if(scanKey==2)
			{
				LBDS=10;Delay(1500);
				break;
			}
			if(scanKey==3)
			{
				LBDS=11;Delay(1500);
				break;
			}
			break;
		}
	}
	else
	{
		LBDS=scanKey; Delay(1500);
	}
}
