#include "ICETEK-VC5509-EDU.h"     //ICETEK-VC5509A-S60实验箱扩展接口和控制模块

ioport unsigned int *SPCR21=(unsigned int *)0x2c04;
ioport unsigned int *PCR_1=(unsigned int *)0x2c12;

unsigned char ledbuf[8],ledx[8];

unsigned char dbClearKey;

unsigned char ledkey[10][8]=
{
    {0x00,0x00,0x7C,0x82,0x82,0x82,0x7C,0x00},  //0
    {0x00,0x00,0x00,0x84,0xFE,0x80,0x00,0x00},  //1
    {0x00,0x00,0x84,0xC2,0xA2,0x92,0x8C,0x00},  //2
    {0x00,0x00,0x44,0x92,0x92,0x92,0x6C,0x00},
    {0x00,0x00,0x30,0x28,0x24,0xFE,0x20,0x00},
    {0x00,0x00,0x4E,0x92,0x92,0x92,0x62,0x00},
    {0x00,0x00,0x7C,0x92,0x92,0x92,0x64,0x00},
    {0x00,0x00,0x02,0xC2,0x32,0x0A,0x06,0x00},
    {0x00,0x00,0x6C,0x92,0x92,0x92,0x6C,0x00},
    {0x00,0x00,0x4C,0x92,0x92,0x92,0x7C,0x00}
};
#define nMusicNumber 52
unsigned int music[nMusicNumber][2]=
{
    {101,1920},{121,1440},{114,480},{101,1920},{151,1920},
    {151,480},{135,480},{121,480},{101,480},{114,960},{121,960},{135,3840},
    {121,480},{114,480},{101,480},{91,480},{101,960},{101,960},
    {76,1920},{101,1920},{114,960},{121,960},{135,1440},{151,480},{151,1920},{0,1920},
    {101,1920},{121,1440},{114,480},{101,1920},{151,1920},
    {151,480},{135,480},{121,480},{101,480},{114,960},{121,960},{135,3840},
    {121,480},{114,480},{101,480},{91,480},{101,960},{101,960},
    {76,1920},{101,1920},{114,960},{121,960},{135,1440},{151,480},{151,1920},{0,1920}
};
unsigned int pwm[8]={ 0x86,0x87,0x83,0x8b,0x89,0x8d,0x8c,0x8e };

void CloseCTR()
{
    CTRGR=0;
    CTRLR=0; CTRLR=0x40;
    CTRLR=0x0c0;
    LCDCMD(LCDCMDTURNOFF);
    dbClearKey=CTRCLKEY;
    LBDS=0;
}

void LCDCMD(unsigned char dbCommand)
{
    CTRLCDCMDR=dbCommand;
    CTRLCDCR=0;
}
unsigned char GetKey(){
    unsigned char dbReturn;

    dbReturn=CTRKEY;
    Delay(200);
    if(CTRKEY!=0)
    {
        dbReturn=CTRKEY;
        dbClearKey=CTRCLKEY;   //��һ�¾�����
        return dbReturn;
    }
    else return 0;
}

char ConvertScanToChar(unsigned char cScanCode)
{
    char cReturn;

    cReturn=0;
    switch ( cScanCode )
    {
        case SCANCODE_1: cReturn='1'; break;
        case SCANCODE_2: cReturn='2'; break;
        case SCANCODE_3: cReturn='3'; break;
        case SCANCODE_4: cReturn='4'; break;
        case SCANCODE_5: cReturn='5'; break;
        case SCANCODE_6: cReturn='6'; break;
        case SCANCODE_7: cReturn='7'; break;
        case SCANCODE_8: cReturn='8'; break;
        case SCANCODE_9: cReturn='9'; break;
    }
    return cReturn;
}

void InitCTR()
{
    CTRGR=0; CTRGR=0x80; CTRGR=0;
    CTRLR=0; CTRLR=0x40;
    CTRLR=0x0c0;
    LCDCMD(LCDCMDTURNOFF);
    dbClearKey=CTRCLKEY;
    LBDS=0;
    CTRLR=0xc8;
    ncode=CTRCLKEY;
}

void Delay(unsigned int nDelay)
{
    int ii,jj,kk=0;
    for ( ii=0;ii<nDelay;ii++ )
    {
        for ( jj=0;jj<1024;jj++ )
        {
            kk++;
        }
    }
}

void Delay1(unsigned int nDelay)
{
    int ii,jj,kk=0;
    for ( ii=0;ii<nDelay;ii++ )
    {
        for ( jj=0;jj<64;jj++ )
        {
            RefreshLEDArray();
            kk++;
        }
    }
}

void RefreshLEDArray()
{
    int i;
    for ( i=0;i<8;i++ )
    {
        CTRGR=ledx[i];
        CTRLA=ledbuf[i];
    }
}

void SetLEDArray(int nNumber)
{
    int i;
    for ( i=0;i<8;i++ )
        ledbuf[i]=~ledkey[nNumber][7-i];
}

void LCDWriteLeft(unsigned char dbData)
{
    CTRLCDLCR=dbData;
    CTRLCDCR=0;
}

void LCDWriteRight(unsigned char dbData)
{
    CTRLCDRCR=dbData;
    CTRLCDCR=0;
}

void TurnOnLCD()
{
    LCDCMD(LCDCMDTURNON);
}

void LCDCLS()
{
    int i,j;
    LCDCMD(LCDCMDSTARTLINE);
    for ( i=0;i<8;i++ )
    {
        LCDCMD(LCDCMDPAGE+i);
        LCDCMD(LCDCMDVERADDRESS);
        for ( j=0;j<64;j++ )
            LCDWriteLeft(0);
        LCDCMD(LCDCMDPAGE+i);
        LCDCMD(LCDCMDVERADDRESS);
        for ( j=0;j<64;j++ )
            LCDWriteRight(0);
    }
}
