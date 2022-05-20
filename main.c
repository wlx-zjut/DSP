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
int final_phase[128];
int finally_phase[100];
long finally[100];
int i;
int magn_flag=1;
int freq_min=0,value_max=90;
int freq_max;
long show_data_x,show_data_y;
double show_data_x1,show_data_y1;
int freq_change_flag=0,magn_change_level=3,magn_change_flag=0,flag_magn_phase_max=0,display_reset_flag=0;
double show_data_y1;
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
    update_value_level();
    update_show_num();
    while(1){
        AIC23_Mixer();
        AIC23_Mixer();
        rfft(sample,256,SCALE);
        final[0]=sample[0];
        for(i=1;i<128;i++){
           final[i]=sqrt((long)sample[2*i]*(long)sample[2*i]+(long)sample[2*i+1]*(long)sample[2*i+1]);
        }
        switch(flag_magn_phase_max){
        case  0://显示幅度谱
            if(display_reset_flag){
                Init_gra();
                update_value_level();
                update_show_num();
                display_reset_flag=0;
            }
            for(i=0;i<100;i++){
                show_data_x=(long)(0.053333333*(freq_min+(freq_max-freq_min)*i));
                show_data_y=(long)(final[show_data_x]*144/18000);
                show_data_y/=magn_change_level;
                if(show_data_y<0) show_data_y=0;
                finally[i]=show_data_y;
                //ShowPoint(8+show_data_y,16+i);
            }
            Delay(100);//延迟减缓闪屏,增强视觉体验
            if(freq_change_flag){
                update_show_num();
                freq_change_flag=0;
            }
            if(magn_change_flag){
                update_value_level();
                magn_change_flag=0;
            }
            LCDClear();
            for(i=0;i<100;i++){
                ShowPoint_magn(16+i,8+finally[i]);
            }
               break;
        case  1://显示相位谱
            if(display_reset_flag){
                Init_phase();
                Show0_20k();
                display_reset_flag=0;
            }
            final_phase[0]=0;
            for(i=1;i<128;i++){
                final_phase[i]=(int)((atan(sample[2*i]/sample[2*i+1])+1.571)*16.55);
            }
            for(i=0;i<100;i++){
                show_data_x=(long)(1.066666666666*i);
                show_data_y1=(final_phase[show_data_x]);
                finally_phase[i]=(int)show_data_y1;
            }
            LCDClear();
            for(i=0;i<100;i++){
                /*ShowPoint(35+finally_phase[i],16+i);*/
                ShowPoint(9+finally_phase[i],16+i);
            }

            break;
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
