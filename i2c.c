#include "5509.h"
#include "util.h"
extern DSPCLK dspclk;
I2C_Init()
{
    PC55XX_I2C pI2C = (PC55XX_I2C)C55XX_I2C_ADDR;

    //置I2C控制器复位
    ClearMask(pI2C -> icmdr, ICMDR_IRS);
    
    //设置预分频器生成12MHz时钟
    pI2C -> icpsc = dspclk.pllmult;
       
    //设置时钟控制寄存器(100KHz时钟输出)
    Write(pI2C -> icclkl, 10);  // For 400KHz, use 47 for 100KHz
    Write(pI2C -> icclkh, 10);
        
    //设置主和从地址
    WriteMask(pI2C -> icoar, ICOAR_OADDR, ICOAR_MASK_7);

    //将I2C控制器从复位中取出，置于主模式
    SetMask(pI2C -> icmdr, ICMDR_IRS | ICMDR_MST);
}

I2C_Disable()
{
    PC55XX_I2C pI2C = (PC55XX_I2C)C55XX_I2C_ADDR;

    //置I2C控制器复位
    ClearMask(pI2C -> icmdr, ICMDR_IRS);    
}

void I2C_Write(unsigned short int device, int count, unsigned char *bytedata)
{
    PC55XX_I2C pI2C = (PC55XX_I2C)C55XX_I2C_ADDR;  //I2C复位
    int i;
        
    //设置I2C控制器写入一个计数字节流
    Write(pI2C -> iccnt, count);      //把count写入iccnt
    WriteMask(pI2C -> icsar, device, ICSAR_MASK_7);
    WriteMask(pI2C -> icmdr,
        ICMDR_STT | ICMDR_STP | ICMDR_TRX,
        ICMDR_STT | ICMDR_STP | ICMDR_TRX);
        
    //传输数据
    for (i = 0; i < count ; i++) {
        Write(pI2C -> icdxr, bytedata[i]);   //把寄存器地址和数据读到I2C的接收寄存器中
        while(!(pI2C -> icstr & ICSTR_ICXRDY));
    }
}

void I2C_Read(unsigned short int device, int count, unsigned char *bytedata)
{
    PC55XX_I2C pI2C = (PC55XX_I2C)C55XX_I2C_ADDR;
    int i;
       
    //将I2C控制器设置为读取计数字节流
    Write(pI2C -> iccnt, count);
    WriteMask(pI2C -> icsar, device, ICSAR_MASK_7);
    WriteMask(pI2C -> icmdr,
        ICMDR_STT | ICMDR_STP,
        ICMDR_STT | ICMDR_STP | ICMDR_TRX);
    
    // 接收数据
    for (i = 0; i < count; i++)
    {
        //等待接收数据返回
        while(!(pI2C -> icstr & ICSTR_ICRRDY));

        //复制数据
        bytedata[i] = pI2C -> icdrr;
    }
}

