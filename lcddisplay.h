void lcdInit();
void LCDCLS();
void showChar(int x,int y,int num);//列，页，显示字符  16行x8列
//void showString(int x,int y,char*p);//页，列，字符串  16行x8列
void showcharacter_h(int x,int y,int length,int start);
void showcharacter_v(int x,int y,int length);//       16行x16列
void ShowPoint(int i,int j);  //画单点函数


void setpage(int page);                  // 设置操作页
void setcolumn(int column);              //设置列
void printleft(unsigned char data);      //画左半屏
void printright(unsigned char data);     //画右半屏
void ShowNum(int x,int y,int num);       //显示数字
void ShowSpace(int x,int y);
void full(int page,int column);
void Show_123();
void Show_246();
void Show_369();
void Init_gra();
void Show0_20k();
void Show0_10k();
void Show2_12k();
void Show4_14k();
void Show6_16k();
void Show8_18k();
void LCDClear();
void LCDFull_all();
void ShowPoint_magn(int i,int j);
void update_value_level();
void Init_phase();
