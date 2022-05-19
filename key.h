#ifndef __KEY__H
#define __KEY__H


//#include "ICETEK-VC5509-EDU.h"     //ICETEK-VC5509A-S60实验箱扩展接口和控制模块
//#include "5509.h"
//#include "c5509mmr.h"

unsigned char GetKey();                   //获取按键
void interrupt XINT2(void);	      //声明中断服务子程序ISR
void Keyshift();                  	      //移位键实现相应功能
void INTR_init( void );
extern int scanKey;
void InitCTR();

#endif

