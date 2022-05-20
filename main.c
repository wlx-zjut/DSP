#include "c5509.h"
#include "util.h"
#include "func.h"
#include <dsplib.h>
#include <TMS320.H>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <lcddisplay.h>
#include "ICETEK-VC5509-EDU.h"     //ICETEK-VC5509A-S60实验箱扩展接口和控制模块
#include <key.h>
void wait( unsigned int cycles );
void EnableAPLL( );
extern short sample[256];
long final[128];
long finally[100];
int i;
int magn_flag=1;
int freq_min=0,value_max=90;
int freq_max;
long show_data_x,show_data_y;
int freq_change_flag=0;
void main()
{
    PLL_Init(24);
    SDRAM_init();
    freq_max=freq_min+magn_flag*5;
    INTR_init();
    InitCTR();
    AIC23_Init();
    AIC23_Mixer_Init();
    lcdInit();
    Init_gra();
    Show_369();
    update_show_num();
/*    ShowPoint(40,16+);
    while(1);*/
    while(1){
        AIC23_Mixer();
        AIC23_Mixer();
        rfft(sample,256,SCALE);
        for(i=0;i<128;i++){
           final[i]=sqrt((long)sample[2*i]*(long)sample[2*i]+(long)sample[2*i+1]*(long)sample[2*i+1]);
        }
        for(i=0;i<100;i++){
            show_data_x=(long)(0.053333333*(freq_min+(freq_max-freq_min)*i));
            show_data_y=(long)(final[show_data_x]*value_max/18000);
            finally[i]=show_data_y;
            //ShowPoint(8+show_data_y,16+i);
        }
        Delay(100);//延迟减缓闪屏,增强视觉体验
        if(freq_change_flag){
            update_show_num();
            freq_change_flag=0;
        }
        LCDClear();


        for(i=0;i<100;i++){
            //ShowPoint(8+finally[i],16+i);
            ShowPoint_magn(16+i,8+finally[i]);
        }

    }
}
void wait( unsigned int cycles )
{
    int i;
    for ( i = 0 ; i < cycles ; i++ ){ }
}

void EnableAPLL( )
{
    /* Enusre DPLL is running */
    *( ioport volatile unsigned short* )0x1f00 = 4;

    wait( 25 );

    *( ioport volatile unsigned short* )0x1f00 = 0;

    // MULITPLY
    *( ioport volatile unsigned short* )0x1f00 = 0x3000;

    // COUNT
    *( ioport volatile unsigned short* )0x1f00 |= 0x4F8;

    wait( 25 );

    //*( ioport volatile unsigned short* )0x1f00 |= 0x800

    // MODE
    *( ioport volatile unsigned short* )0x1f00 |= 2;

    wait( 30000 );

    // APLL Select
    *( ioport volatile unsigned short* )0x1e80 = 1;

    // DELAY
    wait( 60000 );
}
