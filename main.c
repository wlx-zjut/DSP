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
double final_phase[128];
int finally_phase[100];
long finally[100];
int i;
int magn_flag=1;
int freq_min=0,value_max=90;
int freq_max;
int index,result_max;
long show_data_x,show_data_y;
double show_data_x1,show_data_y1;
int insert_flag=0,start_freq=0,insert_flag_freq_change=0;
int freq_change_flag=0,magn_change_level=3,magn_change_flag=0,flag_magn_phase_max=0,display_reset_flag=0;
int wan,qian,bai,shi,ge;
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
                show_data_x=(long)(5.3333333*(freq_min+(freq_max-freq_min)*1.0*i/100));
                show_data_y=(long)(final[show_data_x]*144/18000);
                show_data_y/=magn_change_level;
                if(show_data_y<0) show_data_y=0;
                finally[i]=show_data_y;
                //ShowPoint(8+show_data_y,16+i);
            }
            Delay(100);//延迟减缓闪屏,增强视觉体验
            if(freq_change_flag){
                update_show_num();
                freq_max=freq_min+magn_flag*5;
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
            if(insert_flag_freq_change){
                freq_min=start_freq;
                magn_flag=1;
                update_show_num();
                freq_max=freq_min+magn_flag*5;
                insert_flag_freq_change=0;
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
                /*final_phase[i]=(int)((atan(sample[2*i]/sample[2*i+1])+1.571)*16.55);*/
                final_phase[i]=(atan(sample[2*i]*1.0/sample[2*i+1]));
            }
            for(i=0;i<100;i++){
                show_data_x=(long)(1.066666666666*i);
                show_data_y1=((final_phase[show_data_x]+1.571)*16.55);
                finally_phase[i]=(int)(show_data_y1);
            }
            LCDClear();
            for(i=0;i<100;i++){
                /*ShowPoint(35+finally_phase[i],16+i);*/
                ShowPoint(9+finally_phase[i],16+i);
            }
            break;


        case  2://显示最大频率点
            if(display_reset_flag){
                LCDCLS();
                showcharacter_h(2,0,3,0);
                showcharacter_h(4,70,1,3);
                display_reset_flag=0;
            }
            index = 0;              //假设a[0]为最大值，index存储最大值下标；
            for(i = 1; i < 128; i++){
              if(final[i]>final[index]){   //如果a[i]比假设的的最大值还大，
                index = i;           //再假设a[i]是新的最大值；
              }
            }
            result_max=(int)(index*187.5);
            wan=result_max/10000;
            qian=(result_max/1000)%10;
            bai=(result_max/100)%10;
            shi=(result_max/10)%10;
            ge=result_max%10;
            ShowNum(35,5,wan);
            Delay(100);
            ShowNum(40,5,qian);
            Delay(100);
            ShowNum(45,5,bai);
            Delay(100);
            ShowNum(50,5,shi);
            Delay(100);
            ShowNum(55,5,ge);
            Delay(100);
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
