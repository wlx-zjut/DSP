#include "ICETEK-VC5509-EDU.h"
#include "WordLibrary.h"//字符库
#include "lcddisplay.h"
#define LCDDELAY 1
void lcdInit()//初始化LCD屏幕
{
    //TurnOnLCD();                // 打开显示
    LCDCLS();               // 清除显示内存
    CTRLCDCMDR=LCDCMDSTARTLINE;     // 设置显示起始行
    Delay(LCDDELAY);
    CTRLCDCR=0;
    Delay(LCDDELAY);
}

void setpage(int page)                  // 设置操作页
{
    CTRLCDCMDR=LCDCMDPAGE+7-page;
    Delay(1);
    CTRLCDCR=0;
    Delay(1);
}
void setcolumn(int column)              //设置列
{
    CTRLCDCMDR=LCDCMDVERADDRESS+column;
    CTRLCDCR=0;
}
void printleft(unsigned char data)      //画左半屏
{
    CTRLCDLCR=data;                     //将显示数组送入左半屏数据控制接口
    CTRLCDCR=0;
}
void printright(unsigned char data)     //画右半屏
{
    CTRLCDRCR=data;                     //将显示数组送入右左半屏数据控制接口
    CTRLCDCR=0;
}
void ShowSpace(int x,int y)
{
        int j,Left_or_Right;
        unsigned char space[5] = {0x00,0x00,0x00,0x00,0x00};
        Left_or_Right=x;//变量Left_or_Right用来判断处于左右半屏的哪一块，统一屏幕显示代码
        CTRLCDCMDR=LCDCMDPAGE+y;  //选页
        Delay(1);
        CTRLCDCR=0;
        if(Left_or_Right<64)
                CTRLCDCMDR=LCDCMDVERADDRESS+x;  // 起始列
        else
                CTRLCDCMDR=LCDCMDVERADDRESS+x-64;   //右半屏额外-64
        Delay(1);
        CTRLCDCR=0;
        Delay(1);
        for(j=0;j<5;j++)
        {
                if(Left_or_Right<64)
                    CTRLCDLCR =  space[j];//左半屏数据写入
                else
                    CTRLCDRCR =  space[j];//右半屏数据写入
                Delay(1);
                CTRLCDCR=0;
                Delay(1);
        }
}
unsigned char ledpoint[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//ledpoint[8]为由下到上依次点亮一个像素点数组
unsigned char ledpoint2[8]={0x80,0xC0,0xA0,0x90,0x88,0x84,0x82,0x81};//ledpoint[8]为由下到上依次点亮一个像素点数组
void ShowPoint(int i,int j)             //画单点函数
    {
        setpage(i/8);
        if(i/8 == 1)
        {
            if(j<64)                        //判断点所在列在左半屏
                    {
                        setcolumn(j);
                        printleft(ledpoint2[i%8]);
                    }
                    else                            //判断点所在列在右半屏
                    {
                        setcolumn(j-64);
                        printright(ledpoint2[i%8]);
                    }
        }
        else{
            if(j<64)                        //判断点所在列在左半屏
            {
                setcolumn(j);
                printleft(ledpoint[i%8]);
            }
            else                            //判断点所在列在右半屏
            {
                setcolumn(j-64);
                printright(ledpoint[i%8]);
            }
        }
    }

void full(int page,int column)          //填充1页1列
{
    setpage(page);
    if(column<64)
    {
        setcolumn(column);
        printleft(0x0FF);
    }
    else
    {
        setcolumn(column-64);
        printright(0x0FF);
    }
}
unsigned char number[10][5] = {
                               {0x00,0x3E,0x41,0x41,0x3E},/*"0",0*/

                               {0x00,0x42,0x7F,0x40,0x00},/*"1",1*/

                               {0x00,0x62,0x51,0x49,0x46},/*"2",2*/

                               {0x00,0x22,0x49,0x49,0x36},/*"3",3*/

                               {0x00,0x38,0x26,0x7F,0x20},/*"4",4*/

                               {0x00,0x4F,0x49,0x49,0x31},/*"5",5*/

                               {0x00,0x3E,0x49,0x49,0x32},/*"6",6*/

                               {0x00,0x03,0x71,0x09,0x07},/*"7",7*/

                               {0x00,0x36,0x49,0x49,0x36},/*"8",8*/

                               {0x00,0x26,0x49,0x49,0x3E},/*"9",9*/
};
void ShowNum(int x,int y,int num)
{
    int i,j,Left_or_Right;
    num=num-0;//得到与'0'的ASC码差值
    Left_or_Right=x;//变量Left_or_Right用来判断处于左右半屏的哪一块，统一屏幕显示代码
    for(i=0;i<1;i++)
    {
        CTRLCDCMDR=LCDCMDPAGE+y;  //选页
        Delay(1);
        CTRLCDCR=0;
        if(Left_or_Right<64)
            CTRLCDCMDR=LCDCMDVERADDRESS+x;  // 起始列
        else
            CTRLCDCMDR=LCDCMDVERADDRESS+x-64;   //右半屏额外-64
        Delay(1);
        CTRLCDCR=0;
        Delay(1);
        for(j=0;j<5;j++)
        {
            if(Left_or_Right<64)
                CTRLCDLCR =  number[num][j];//左半屏数据写入
            else
                CTRLCDRCR=number[num][j];//右半屏数据写入
            Delay(1);
            CTRLCDCR=0;
            Delay(1);
        }
    }
}
void Show_123(){
    ShowNum(0,1,3);
    ShowNum(5,1,0);
    ShowNum(0,3,2);
    ShowNum(5,3,0);
    ShowNum(0,5,1);
    ShowNum(5,5,0);
    ShowNum(5,7,0);
}
void Show_246(){
    ShowNum(0,1,6);
    ShowNum(5,1,0);
    ShowNum(0,3,4);
    ShowNum(5,3,0);
    ShowNum(0,5,2);
    ShowNum(5,5,0);
    ShowNum(5,7,0);
}

void Show_369(){
    ShowNum(0,1,9);
    ShowNum(5,1,0);
    ShowNum(0,3,6);
    ShowNum(5,3,0);
    ShowNum(0,5,3);
    ShowNum(5,5,0);
    ShowNum(5,7,0);
}

