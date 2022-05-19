#include "5509.h"
#include "util.h"
#include "extaddr.h"
#include "math.h"

// AIC23控制寄存器地址  地址为左对齐，取前7位。
#define AIC23_LT_LINE_CTL         0x00  // 0 左线性输入声道音量控制
#define AIC23_RT_LINE_CTL         0x02  // 1 右线性输入声道音量控制
#define AIC23_LT_HP_CTL           0x04  // 2 左耳机输出声道音量控制
#define AIC23_RT_HP_CTL           0x06  // 3 右耳机输出声道音量控制
#define AIC23_ANALOG_AUDIO_CTL    0x08  // 4 模拟音频通道控制
#define AIC23_DIGITAL_AUDIO_CTL   0x0A  // 5 数字音频通道控制
#define AIC23_POWER_DOWN_CTL      0x0C  // 6 电源控制
#define AIC23_DIGITAL_IF_FORMAT   0x0E  // 7 数字音频接口格式
#define AIC23_SAMPLE_RATE_CTL     0x10  // 8 采样率控制
#define AIC23_DIG_IF_ACTIVATE     0x12  // 9 数字接口激活
#define AIC23_RESET_REG           0x1E  // F 复位寄存器

#define DIGIF_FMT_MS              0x40
#define DIGIF_FMT_LRSWAP          0x20
#define DIGIF_FMT_LRP             0x10
#define DIGIF_FMT_IWL             0x0c
#define DIGIF_FMT_FOR             0x03

#define DIGIF_FMT_IWL_16          0x00
#define DIGIF_FMT_IWL_20          0x04
#define DIGIF_FMT_IWL_24          0x08
#define DIGIF_FMT_IWL_32          0xc0

#define DIGIF_FMT_FOR_MSBRIGHT    0x00
#define DIGIF_FMT_FOR_MSLEFT      0x01
#define DIGIF_FMT_FOR_I2S         0x02
#define DIGIF_FMT_FOR_DSP         0x03

#define POWER_DEV                 0x80
#define POWER_CLK                 0x40
#define POWER_OSC                 0x20
#define POWER_OUT                 0x10
#define POWER_DAC                 0x08
#define POWER_ADC                 0x04
#define POWER_MIC                 0x02
#define POWER_LINE                0x01

#define SRC_CLKOUT                0x80
#define SRC_CLKIN                 0x40
#define SRC_SR                    0x3c
#define SRC_BOSR                  0x02
#define SRC_MO                    0x01

#define SRC_SR_44                 0x20
#define SRC_SR_32                 0x18

#define ANAPCTL_STA               0xc0
#define ANAPCTL_STE               0x20
#define ANAPCTL_DAC               0x10
#define ANAPCTL_BYP               0x08
#define ANAPCTL_INSEL             0x04
#define ANAPCTL_MICM              0x02
#define ANAPCTL_MICB              0x01    

#define DIGPCTL_DACM              0x08
#define DIGPCTL_DEEMP             0x06
#define DIGPCTL_ADCHP             0x01
#define DIGPCTL_DEEMP_DIS         0x00
#define DIGPCTL_DEEMP_32          0x02
#define DIGPCTL_DEEMP_44          0x04
#define DIGPCRL_DEEMP_48          0x06

#define DIGIFACT_ACT              0x01

void AIC23_Write(unsigned short regaddr, unsigned short data)
{
    unsigned char buf[2];  //缓存区数组
    buf[0] = regaddr;      //存放寄存器地址
    buf[1] = data;         //存放数据
    I2C_Write(I2C_AIC23, 2, buf);
}

void McBSP0_InitSlave()
{
    PC55XX_MCSP pMCBSP0 = (PC55XX_MCSP)C55XX_MSP0_ADDR;
    
    //McBSP0复位
    Write(pMCBSP0 -> spcr1, 0);
    Write(pMCBSP0 -> spcr2, 0);
       
    // 配置帧参数(32位，单相，无延迟)
    Write(pMCBSP0 -> xcr1, XWDLEN1_32);
    Write(pMCBSP0 -> xcr2, XPHASE_SINGLE | XDATDLY_0);
    Write(pMCBSP0 -> rcr1, RWDLEN1_32);
    Write(pMCBSP0 -> rcr2, RPHASE_SINGLE | RDATDLY_0);

    // Disable int frame generation and enable slave w/ext frame signals on FSX
    // Frame sync is active high, data clocked on rising edge of clkx
    Write(pMCBSP0 -> pcr, PCR_CLKXP);

    //发送器摆脱复位  接收器使能
    SetMask(pMCBSP0 -> spcr2, SPCR2_XRST);
    SetMask(pMCBSP0 -> spcr1, SPCR1_RRST);    
}

void AIC23_Init()
{
    I2C_Init();
    AIC23_Write(AIC23_RESET_REG, 0);     //复位寄存器
    AIC23_Write(AIC23_POWER_DOWN_CTL,0);//所有电源都打开
    AIC23_Write(AIC23_ANALOG_AUDIO_CTL, ANAPCTL_DAC | ANAPCTL_INSEL); //打开DAC 选择传声器
    AIC23_Write(AIC23_DIGITAL_AUDIO_CTL, 0);//数字音频通道控制   禁止去加重
    
    // 打开线入声道音量
    AIC23_Write(AIC23_LT_LINE_CTL,0x01f);//左声道输入衰减正常，最小为-34.5dB
    AIC23_Write(AIC23_RT_LINE_CTL,0x01f);//右声道输入衰减正常，最小为-34.5dB  禁止左右声道同时更新

    // 数字音频接口主模式    输入长度16位     DSP初始化
    // 采样率控制 48KHz 比较常用   SRC_BOSR为272fs  USB clock
    AIC23_Write(AIC23_DIGITAL_IF_FORMAT, DIGIF_FMT_MS | DIGIF_FMT_IWL_16 | DIGIF_FMT_FOR_DSP);
    AIC23_Write(AIC23_SAMPLE_RATE_CTL, 0x01);

    // 打开耳机声道音量和数字接口激活
    AIC23_Write(AIC23_LT_HP_CTL, 0x1ff);  //激活 衰减+6dB 零点检测  开启
    AIC23_Write(AIC23_RT_HP_CTL, 0x1ff);
    AIC23_Write(AIC23_DIG_IF_ACTIVATE, DIGIFACT_ACT);

    // 设置McBSP0为发送从设备
    McBSP0_InitSlave();
}

void AIC23_Disable()
{
    PC55XX_MCSP pMCBSP0 = (PC55XX_MCSP)C55XX_MSP0_ADDR;
    //I2C_Disable();
    
    //把McBSP复位
    Write(pMCBSP0 -> spcr1, 0);
    Write(pMCBSP0 -> spcr2, 0);
}

#define AUDIOBUFFER 0x200000
FARPTR lpAudio;

PC55XX_MCSP pMCBSP0 = (PC55XX_MCSP)C55XX_MSP0_ADDR;
int nWork;
FARPTR lpWork;
long int luWork,luWork1;
short sample[256];
void AIC23_Mixer_Init(){
    lpWork=lpAudio=AUDIOBUFFER; luWork=0;      //音频缓冲区
      for ( luWork1=0;luWork1<512;luWork1++ )
          far_poke(lpWork++,0);
      lpWork=lpAudio;
}

void AIC23_Mixer()
{
    while (!ReadMask(pMCBSP0 -> spcr2, SPCR2_XRDY));
    lpWork=lpAudio;
    for(luWork=0;luWork<256;luWork++){
        while(!ReadMask(pMCBSP0 -> spcr2, SPCR2_XRDY)); // 等待McBSP0准备好
        nWork=Read(pMCBSP0->drr2);  // 读取左右声道的数据到nWork
        nWork=Read(pMCBSP0->drr1);  // 这里假设两个声道相同，所以都输入到nWork，其中一个声道是被覆盖的。
                                    // 如果左右声道不同，则要分别输入到两个数组，比如nWork_L和nWork_R
        far_poke(lpWork++,nWork);   // 读取的左右声道数据保存到缓冲区lpWork
        Write(pMCBSP0->dxr2,nWork); // 送数据到McBSP0，声音输出由AIC23完成
        Write(pMCBSP0->dxr1,nWork); // 这里两个声道相同，都从nWork输出。
        sample[luWork]=nWork;

    }
}
