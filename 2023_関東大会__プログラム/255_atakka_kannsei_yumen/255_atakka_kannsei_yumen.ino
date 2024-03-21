
#include <Wire.h>

#define BNO055 0x28

volatile int RET_MSG;
volatile int DIR;
volatile int GYRO;
volatile int PITCH;
volatile int ROLL;

void setup() {

  Serial.begin(9600);
  Serial1.begin(19200);

  //カラーセンサー　PIN 　設定
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  //超音波センサー　PIN 　設定
  //pinMode(5, OUTPUT);
  //pinMode(5, INPUT);

  //IRセンサー　PIN 　設定
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  //コンパス
  Wire.begin();                         //I2C通信開始
  Wire.beginTransmission(BNO055);
  Wire.write(0x3B); //register設定
  Wire.write(0x00);
  RET_MSG = Wire.endTransmission();     // データの送信と終了処理
  if (RET_MSG == 0) {
  }
  else {
    Serial.print("ERROR NO.=");           //通信出来ない
    Serial.println(RET_MSG);
  }

  Wire.beginTransmission(BNO055);
  Wire.write(0x41);                    //register設定
  Wire.write(0x21);
  Wire.write(0x04);
  RET_MSG = Wire.endTransmission();    // データの送信と終了処理
  if (RET_MSG == 0) {
  }
  else {
    Serial.print("ERROR NO.=");          //通信出来ない
    Serial.println(RET_MSG);
  }

  Wire.beginTransmission(BNO055);
  Wire.write(0x3D); //register設定
  Wire.write(0x0C);
  RET_MSG = Wire.endTransmission();    // データの送信と終了処理
  if (RET_MSG == 0) {
  }
  else {
    Serial.print("ERROR NO.=");          //通信出来ない
    Serial.println(RET_MSG);
  }
  if (DIR >= 20) {
    Serial.println("x軸が20以上の場合");
    Serial1.println("1R1002R1003F1004F100");
    delay(40);
    Serial1.println("");
    return;
  }
  else if (DIR <= -20) {
    Serial.println("x軸が-20以上の場合");
    Serial1.println("1F1002F1003R1004R100");
    delay(40);
    Serial1.println("");
    return;
  }
}


void loop() {
  Serial.print("   color_1 =");
  Serial.print(analogRead(0));
  Serial.print("   color_2 =");
  Serial.print(analogRead(1));
  Serial.print("   color_3 =");
  Serial.print(analogRead(2));
  Serial.print("   color_4 =");
  Serial.println(analogRead(3));
  Serial.print("      IR_1 =");
  Serial.print(analogRead(4));
  Serial.print("      IR_2 =");
  Serial.print(analogRead(5));
  Serial.print("      IR_3 =");
  Serial.print(analogRead(6));
  Serial.print("      IR_4 =");
  Serial.println(analogRead(7));
  DIR = getDIR(0);
  Serial.print("　X軸");
  Serial.print(DIR);
  GYRO = getGYRO(0);
  Serial.print("　加速度");
  Serial.print(GYRO);
  PITCH = getPITCH(0);
  Serial.print("　Ý軸");
  Serial.print(PITCH);
  ROLL = getROLL(0);
  Serial.print("　Z軸");
  Serial.println(ROLL);




  if (DIR >= 20) {
    Serial.println("x軸が20以上の場合");
    Serial1.println("1R1002R1003F1004F100");
    delay(40);
    Serial1.println("");
    return;
  }
  else if (DIR <= -20) {
    Serial.println("x軸が-20以上の場合");
    Serial1.println("1F1002F1003R1004R100");
    delay(40);
    Serial1.println("");
    return;
  }

  if ((analogRead(0) >= 100)) {// || (analogRead(0) <= 10)
    Serial.println("1　白or黒ならば");
    Serial1.println("1R1002R1003R1004R100");
    delay(100);
    Serial1.println("");
    return;
  }
  else if ((analogRead(1) >= 100)) {// || (analogRead(1) <= 10)
    Serial.println("2 白or黒ならば");
    Serial1.println("1F1002R1003F1004R100");
    delay(100);
    Serial1.println("");
    return;
  }
  else if ((analogRead(2) >= 200)) {// || (analogRead(2) <= 0)
    Serial.println("3 白or黒ならば");
    Serial1.println("1F1002F1003F1004F100");
    delay(100);
    Serial1.println("");
    return;
  }
  else if ((analogRead(3) >= 100)) {// || (analogRead(3) <= 1)
    Serial.println("4 白or黒ならば");
    Serial1.println("1R1002F1003R1004F100");
    delay(100);
    Serial1.println("");
    return;
  }

  if (analogRead(4) >= 970 && analogRead(5) >= 950) {
    Serial.println("左斜め前");
    Serial1.println("1R1002R1003R1004R100");
    delay(400);
    Serial1.println("1R1002F1003R1004F100");
    delay(400);
    Serial1.println("");
  }
  else if (analogRead(7) >= 960 && analogRead(4) >= 972) {
    Serial.println("右斜め前");
    Serial1.println("1R1002R1003R1004R100");
    delay(400);
    Serial1.println("1F1002R1003F1004R100");
    delay(400);
    Serial1.println("");
  }
  else if (analogRead(4) >= 970) {
    Serial.println("前");
    Serial1.println("1F1002F1003F1004F100");
    delay(150);
    Serial1.println("");
  }
  else if (analogRead(5) >= 945) {
    Serial.println("左");
    Serial1.println("1R1002R1003R1004R100");
    delay(400);
    Serial1.println("1R1002F1003R1004F100");
    delay(700);
    Serial1.println("");
  }
  else if (analogRead(6) >= 970) {
    Serial.println("後ろ");
    Serial1.println("1R1002R1003R1004R100");
    delay(100);
    Serial1.println("");
  }
  else if (analogRead(7) >= 960) {
    Serial.println("右");
    Serial1.println("1R1002R1003R1004R100");
    delay(400);
    Serial1.println("1F1002R1003F1004R100");
    delay(700);
    Serial1.println("");
  }
  else if (analogRead(5) >= 1000 && analogRead(6) >= 1000) {
    Serial.println("左斜め後ろ");
    Serial1.println("1R1002R1003R1004R100");
    delay(100);
    Serial1.println("");
  }
  else if (analogRead(6) >= 1000 && analogRead(7) >= 1000) {
    Serial.println("右斜め後ろ");
    Serial1.println("1R1002R1003R1004R100");
    delay(100);
    Serial1.println("");
  }
  else {
    Serial.println("IRボール　発見できない");
    Serial1.println("1R1002R1003R1004R100");
    delay(100);
    Serial1.println("");
  }


}

//IRセンサー 4 IR1,5 IR2,6 IR3,7 IR4*/
unsigned int getGYRO(unsigned char)  //ジャイロ角速度を読み込み。
{
  typedef union {                      //受信データ用共用体
    unsigned int W;
    struct {
      unsigned char L;
      unsigned char H;
    };
  } U_UINT;
  U_UINT data;                        // 受信データ
  int reg;                            //レジスターアドレス
  reg = 0x18;                         // Register 0x1E:GYRO_DATA_Z (LSB-MSB)
  Wire.beginTransmission(BNO055);     //通信開始
  Wire.write(reg);                    //register
  Wire.endTransmission();             //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read();               //１バイト分のデータの読み込み
    data.H = Wire.read();               //次の１バイト分のデータを読み込み
  }
  return (data.W);
}

unsigned int getDIR(unsigned char) //ヘッドアップ角度を読み込み。
{
  typedef union {                    //受信データ用共用体
    unsigned int W;
    struct {
      unsigned char L;
      unsigned char H;
    };
  } U_UINT;
  U_UINT data;                      // 受信データ
  int reg; //レジスターアドレス
  reg = 0x1A;                       // Register 0x1A:dir(EUL_DATA_X LSB-MSB)
  Wire.beginTransmission(BNO055);   //通信開始
  Wire.write(reg);                  //register
  Wire.endTransmission();           //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read();             //１バイト分のデータの読み込み
    data.H = Wire.read();             //次の１バイト分のデータを読み込み
  }
  data.W = data.W / 16;

  if (data.W == 181) {
    data.W = -179;
  } else if (data.W == 182) {
    data.W = -178;
  } else if (data.W == 183) {
    data.W = -177;
  } else if (data.W == 184) {
    data.W = -176;
  } else if (data.W == 185) {
    data.W = -175;
  } else if (data.W == 186) {
    data.W = -174;
  } else if (data.W == 187) {
    data.W = -173;
  } else if (data.W == 188) {
    data.W = -172;
  } else if (data.W == 189) {
    data.W = -171;
  } else if (data.W == 190) {
    data.W = -170;
  } else if (data.W == 191) {
    data.W = -169;
  } else if (data.W == 192) {
    data.W = -168;
  } else if (data.W == 193) {
    data.W = -167;
  } else if (data.W == 194) {
    data.W = -166;
  } else if (data.W == 195) {
    data.W = -165;
  } else if (data.W == 196) {
    data.W = -164;
  } else if (data.W == 197) {
    data.W = -163;
  } else if (data.W == 198) {
    data.W = -162;
  } else if (data.W == 199) {
    data.W = -161;
  } else if (data.W == 200) {
    data.W = -160;
  } else if (data.W == 201) {
    data.W = -159;
  } else if (data.W == 202) {
    data.W = -158;
  } else if (data.W == 203) {
    data.W = -157;
  } else if (data.W == 204) {
    data.W = -156;
  } else if (data.W == 205) {
    data.W = -155;
  } else if (data.W == 206) {
    data.W = -154;
  } else if (data.W == 207) {
    data.W = -153;
  } else if (data.W == 208) {
    data.W = -152;
  } else if (data.W == 209) {
    data.W = -151;
  } else if (data.W == 210) {
    data.W = -150;
  } else if (data.W == 211) {
    data.W = -149;
  } else if (data.W == 212) {
    data.W = -148;
  } else if (data.W == 213) {
    data.W = -147;
  } else if (data.W == 214) {
    data.W = -146;
  } else if (data.W == 215) {
    data.W = -145;
  } else if (data.W == 216) {
    data.W = -144;
  } else if (data.W == 217) {
    data.W = -143;
  } else if (data.W == 218) {
    data.W = -142;
  } else if (data.W == 219) {
    data.W = -141;
  } else if (data.W == 220) {
    data.W = -140;
  } else if (data.W == 221) {
    data.W = -139;
  } else if (data.W == 222) {
    data.W = -138;
  } else if (data.W == 223) {
    data.W = -137;
  } else if (data.W == 224) {
    data.W = -136;
  } else if (data.W == 225) {
    data.W = -135;
  } else if (data.W == 226) {
    data.W = -134;
  } else if (data.W == 227) {
    data.W = -133;
  } else if (data.W == 228) {
    data.W = -132;
  } else if (data.W == 229) {
    data.W = -131;
  } else if (data.W == 230) {
    data.W = -130;
  } else if (data.W == 231) {
    data.W = -129;
  } else if (data.W == 232) {
    data.W = -128;
  } else if (data.W == 233) {
    data.W = -127;
  } else if (data.W == 234) {
    data.W = -126;
  } else if (data.W == 235) {
    data.W = -125;
  } else if (data.W == 236) {
    data.W = -124;
  } else if (data.W == 237) {
    data.W = -123;
  } else if (data.W == 238) {
    data.W = -122;
  } else if (data.W == 239) {
    data.W = -121;
  } else if (data.W == 240) {
    data.W = -120;
  } else if (data.W == 241) {
    data.W = -119;
  } else if (data.W == 242) {
    data.W = -118;
  } else if (data.W == 243) {
    data.W = -117;
  } else if (data.W == 244) {
    data.W = -116;
  } else if (data.W == 245) {
    data.W = -115;
  } else if (data.W == 246) {
    data.W = -114;
  } else if (data.W == 247) {
    data.W = -113;
  } else if (data.W == 248) {
    data.W = -112;
  } else if (data.W == 249) {
    data.W = -111;
  } else if (data.W == 250) {
    data.W = -110;
  } else if (data.W == 251) {
    data.W = -109;
  } else if (data.W == 252) {
    data.W = -108;
  } else if (data.W == 253) {
    data.W = -107;
  } else if (data.W == 654) {
    data.W = -106;
  } else if (data.W == 255) {
    data.W = -105;
  } else if (data.W == 256) {
    data.W = -104;
  } else if (data.W == 257) {
    data.W = -103;
  } else if (data.W == 258) {
    data.W = -102;
  } else if (data.W == 259) {
    data.W = -101;
  } else if (data.W == 260) {
    data.W = -100;
  } else if (data.W == 261) {
    data.W = -99;
  } else if (data.W == 262) {
    data.W = -98;
  } else if (data.W == 263) {
    data.W = -97;
  } else if (data.W == 264) {
    data.W = -96;
  } else if (data.W == 265) {
    data.W = -95;
  } else if (data.W == 266) {
    data.W = -94;
  } else if (data.W == 267) {
    data.W = -93;
  } else if (data.W == 268) {
    data.W = -92;
  } else if (data.W == 269) {
    data.W = -91;
  } else if (data.W == 270) {
    data.W = -90;
  } else if (data.W == 271) {
    data.W = -89;
  } else if (data.W == 272) {
    data.W = -88;
  } else if (data.W == 273) {
    data.W = -87;
  } else if (data.W == 274) {
    data.W = -86;
  } else if (data.W == 275) {
    data.W = -85;
  } else if (data.W == 276) {
    data.W = -84;
  } else if (data.W == 277) {
    data.W = -83;
  } else if (data.W == 278) {
    data.W = -82;
  } else if (data.W == 279) {
    data.W = -81;
  } else if (data.W == 280) {
    data.W = -80;
  } else if (data.W == 281) {
    data.W = -79;
  } else if (data.W == 282) {
    data.W = -78;
  } else if (data.W == 283) {
    data.W = -77;
  } else if (data.W == 284) {
    data.W = -76;
  } else if (data.W == 285) {
    data.W = -75;
  } else if (data.W == 286) {
    data.W = -74;
  } else if (data.W == 287) {
    data.W = -73;
  } else if (data.W == 288) {
    data.W = -72;
  } else if (data.W == 289) {
    data.W = -71;
  } else if (data.W == 290) {
    data.W = -70;
  } else if (data.W == 291) {
    data.W = -69;
  } else if (data.W == 292) {
    data.W = -68;
  } else if (data.W == 293) {
    data.W = -67;
  } else if (data.W == 294) {
    data.W = -66;
  } else if (data.W == 295) {
    data.W = -65;
  } else if (data.W == 296) {
    data.W = -64;
  } else if (data.W == 297) {
    data.W = -63;
  } else if (data.W == 298) {
    data.W = -62;
  } else if (data.W == 299) {
    data.W = -61;
  } else if (data.W == 300) {
    data.W = -60;
  } else if (data.W == 301) {
    data.W = -59;
  } else if (data.W == 302) {
    data.W = -58;
  } else if (data.W == 303) {
    data.W = -57;
  } else if (data.W == 304) {
    data.W = -56;
  } else if (data.W == 305) {
    data.W = -55;
  } else if (data.W == 306) {
    data.W = -54;
  } else if (data.W == 307) {
    data.W = -53;
  } else if (data.W == 308) {
    data.W = -52;
  } else if (data.W == 309) {
    data.W = -51;
  } else if (data.W == 310) {
    data.W = -50;
  } else if (data.W == 311) {
    data.W = -49;
  } else if (data.W == 312) {
    data.W = -48;
  } else if (data.W == 313) {
    data.W = -47;
  } else if (data.W == 314) {
    data.W = -46;
  } else if (data.W == 315) {
    data.W = -45;
  } else if (data.W == 316) {
    data.W = -44;
  } else if (data.W == 317) {
    data.W = -43;
  } else if (data.W == 318) {
    data.W = -42;
  } else if (data.W == 319) {
    data.W = -41;
  } else if (data.W == 320) {
    data.W = -40;
  } else if (data.W == 321) {
    data.W = -39;
  } else if (data.W == 322) {
    data.W = -38;
  } else if (data.W == 323) {
    data.W = -37;
  } else if (data.W == 324) {
    data.W = -36;
  } else if (data.W == 325) {
    data.W = -35;
  } else if (data.W == 326) {
    data.W = -34;
  } else if (data.W == 327) {
    data.W = -33;
  } else if (data.W == 328) {
    data.W = -32;
  } else if (data.W == 329) {
    data.W = -31;
  } else if (data.W == 330) {
    data.W = -30;
  } else if (data.W == 331) {
    data.W = -29;
  } else if (data.W == 332) {
    data.W = -28;
  } else if (data.W == 333) {
    data.W = -27;
  } else if (data.W == 334) {
    data.W = -26;
  } else if (data.W == 335) {
    data.W = -25;
  } else if (data.W == 336) {
    data.W = -24;
  } else if (data.W == 337) {
    data.W = -23;
  } else if (data.W == 338) {
    data.W = -22;
  } else if (data.W == 339) {
    data.W = -21;
  } else if (data.W == 340) {
    data.W = -20;
  } else if (data.W == 341) {
    data.W = -19;
  } else if (data.W == 342) {
    data.W = -18;
  } else if (data.W == 343) {
    data.W = -17;
  } else if (data.W == 344) {
    data.W = -16;
  } else if (data.W == 345) {
    data.W = -15;
  } else if (data.W == 346) {
    data.W = -14;
  } else if (data.W == 347) {
    data.W = -13;
  } else if (data.W == 348) {
    data.W = -12;
  } else if (data.W == 349) {
    data.W = -11;
  } else if (data.W == 350) {
    data.W = -10;
  } else if (data.W == 351) {
    data.W = -9;
  } else if (data.W == 352) {
    data.W = -8;
  } else if (data.W == 353) {
    data.W = -7;
  } else if (data.W == 354) {
    data.W = -6;
  } else if (data.W == 355) {
    data.W = -5;
  } else if (data.W == 356) {
    data.W = -4;
  } else if (data.W == 357) {
    data.W = -3;
  } else if (data.W == 358) {
    data.W = -2;
  } else if (data.W == 359) {
    data.W = -1;
  }
  return (data.W);
}

unsigned int getROLL(unsigned char)//ロール角度を読み込み。
{
  typedef union {                    //受信データ用共用体
    unsigned int W;
    struct {
      unsigned char L;
      unsigned char H;
    };
  } U_UINT;
  U_UINT data;                      // 受信データ
  int reg;                          //レジスターアドレス
  reg = 0x1C;                       // Register 0x1C:ROLL(EUL_DATA_Y LSB-MSB)
  Wire.beginTransmission(BNO055);  //通信開始
  Wire.write(reg); //register
  Wire.endTransmission();          //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read();            //１バイト分のデータの読み込み
    data.H = Wire.read();            //次の１バイト分のデータを読み込み
  }
  return (data.W);
}

unsigned int getPITCH(unsigned char) //ピッチ角度を読み込み。
{
  typedef union {                 //受信データ用共用体
    unsigned int W;
    struct {
      unsigned char L;
      unsigned char H;
    };
  } U_UINT;
  U_UINT data;                   // 受信データ
  int reg;                       //レジスターアドレス
  reg = 0x1E;                    // Register 0x1E:PITCH(LSB-MSB)
  Wire.beginTransmission(BNO055); //通信開始
  Wire.write(reg);               //register
  Wire.endTransmission();        //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read();          //１バイト分のデータの読み込み
    data.H = Wire.read();          //次の１バイト分のデータを読み込み
  }
  return (data.W);
}
