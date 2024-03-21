
//Wireファイルのインクルード
#include<Wire.h>

//9軸センサ　IICアドレス
#define BNO055 0x28

//コンパスセンサー　変数設定
volatile int RET_MSG;
volatile int DIR;
volatile int GYRO;
volatile int PITCH;
volatile int ROLL;

//for文の変数
int i;
int ii;
int iii;

void setup() {//___________________________________________________________________________________________

  //Wire初期設定
  Wire.begin();

  //IR カラー　シリアル　初期設定
  Serial.begin(9600);

  //6ch　シリアル 初期設定
  Serial1.begin(19200);

  //コンパスセンサー　初期設定
  Wire.begin();                         //I2C通信開始
  Wire.beginTransmission(BNO055);
  Wire.write(0x3B); //register設定
  Wire.write(0x00);
  RET_MSG = Wire.endTransmission();     // データの送信と終了処理
  if (RET_MSG == 0) {
  } else {
    Serial.print("ERROR NO.=");           //通信出来ない
    Serial.println(RET_MSG);
  }
  Wire.beginTransmission(BNO055);
  Wire.write(0x41);                    //register設定
  Wire.write(0x21);
  Wire.write(0x04);
  RET_MSG = Wire.endTransmission();    // データの送信と終了処理
  if (RET_MSG == 0) {
  } else {
    Serial.print("ERROR NO.=");          //通信出来ない
    Serial.println(RET_MSG);
  }
  Wire.beginTransmission(BNO055);
  Wire.write(0x3D); //register設定
  Wire.write(0x0C);
  RET_MSG = Wire.endTransmission();    // データの送信と終了処理
  if (RET_MSG == 0) {
  }  else {
    Serial.print("ERROR NO.=");          //通信出来ない
    Serial.println(RET_MSG);
  }

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

}//セットアップ終了_______________________________________________________________________________________________________


//割り込み測定　開始_________________________________________________________________
int color_1 = 0;
int color_2 = 0;
int color_3 = 0;
int color_4 = 0;

int color_h_1 = 0;
int color_h_2 = 0;
int color_h_3 = 0;
int color_h_4 = 0;

int color_kekka_1() {
  for (ii = 0; ii < 3; ii++) {
    color_1 = color_1 + analogRead(0);
  }
  color_1 = color_1 / 3;
  return (color_1);
}
int color_kekka_2() {
  for (ii = 0; ii < 3; ii++) {
    color_2 = color_2 + analogRead(1);
  }
  color_2 = color_2 / 3;
  return (color_2);
}
int color_kekka_3() {
  for (ii = 0; ii < 3; ii++) {
    color_3 = color_3 + analogRead(2);
  }
  color_3 = color_3 / 3;
  return (color_3);
}
int color_kekka_4() {
  for (ii = 0; ii < 3; ii++) {
    color_4 = color_4 + analogRead(3);
  }
  color_4 = color_4 / 3;
  return (color_4);
}


float ir_1 = 0;
float ir_2 = 0;
float ir_3 = 0;
float ir_4 = 0;

float ir_h_1 = 0;
float ir_h_2 = 0;
float ir_h_3 = 0;
float ir_h_4 = 0;

float ir_kekka_1() {
  for (i = 0; i < 5; i++) {
    ir_1 = ir_1 + analogRead(4);// * 0.81722128514056225
  }
  ir_1 = ir_1 / 5;
  return (ir_1);
}
float ir_kekka_2() {
  for (i = 0; i < 5; i++) {
    ir_2 = ir_2 + analogRead(5);// * 0.83532128514056225
  }
  ir_2 = ir_2 / 5;
  return (ir_2);
}
float ir_kekka_3() {
  for (i = 0; i < 5; i++) {
    ir_3 = ir_3 + analogRead(6);// *  0.84932128514056225
  }
  ir_3 = ir_3 / 5;

  return (ir_3);
}
float ir_kekka_4() {

  for (i = 0; i < 5; i++) {
    ir_4 = ir_4 + analogRead(7);// * 1.023590163934426
  }
  ir_4 = ir_4 / 5;
  return (ir_4);
}

long ultrasonic_1 = 0;
long ultrasonic_h_1 = 0;

long ultrasonic_kekka_1() {
  long d;
  long in;
  long ultrasonic_1;
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(5);
  digitalWrite(5, LOW);
  pinMode(5, INPUT);
  d = pulseIn(7, HIGH);
  ultrasonic_1 = d / 59;
  return (ultrasonic_1);
}
//割り込み測定　終了_________________________________________________________________


//ループ開始_______________________________________________________________________________________________
void loop() {

  color_h_1 = color_kekka_1();
  color_h_2 = color_kekka_2();
  color_h_3 = color_kekka_3();
  color_h_4 = color_kekka_4();

  ir_h_1 = ir_kekka_1();
  ir_h_2 = ir_kekka_2();
  ir_h_3 = ir_kekka_3();
  ir_h_4 = ir_kekka_4();

  ultrasonic_h_1 = ultrasonic_kekka_1();

  //斜め処理をする変数
  float ir_h_1_and_ir_h_2 = ir_h_1 + ir_h_2;
  float ir_h_2_and_ir_h_3 = ir_h_2 + ir_h_3;
  float ir_h_3_and_ir_h_4 = ir_h_3 + ir_h_4;
  float ir_h_4_and_ir_h_1 = ir_h_4 + ir_h_1;
  //  ir_h_1  983      1000/983= 1.017293997965412
  //  ir_h_1  962      1000/963= 1.038421599169263
  //  ir_h_1  976      1000/976= 1.024590163934426
  //  ir_h_1  954      1000/954= 1.048218029350105



  //IRセンサー変数を出力
  Serial.print("   IR_1 =");
  Serial.print(ir_h_1);
  Serial.print("   IR_2 =");
  Serial.print(ir_h_2);
  Serial.print("   IR_3 =");
  Serial.print(ir_h_3);
  Serial.print("   IR_4 =");
  Serial.println(ir_h_4);
  delay(10);
  //カラーセンサーセンサー変数を出力
  Serial.print("   color_1 =");
  Serial.print(color_h_1);
  Serial.print("   color_2 =");
  Serial.print(color_h_2);
  Serial.print("   color_3 =");
  Serial.print(color_h_3);
  Serial.print("   color_4 =");
  Serial.println(color_h_4);
  delay(10);
  //コンパスセンサー変数を出力
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
  delay(10);

  //超音波センサー　　測定開始
  Serial.print(ultrasonic_h_1);
  Serial.println();
  delay(10);




  //条件分岐　スタート　メイン
  if ((DIR >= 20) || (DIR <= -20)) {/////////////////////////////////////////////////////////////コンパスセンサー
    if (DIR >= 20) { /////////////////////////////////////////////////x軸が20以上の場合
      Serial.println("x軸が20以上の場合");
      for (iii = 0; iii < 4; iii++) {
        Serial1.println("1R1002R1003F1004F100");
        delay(10);
        //Serial1.println("");
      }
      Serial1.println("");
      return;
    } else if (DIR <= -20) {////////////////////////////////////////////x軸が-20以上の場合
      Serial.println("x軸が-20以下の場合");
      for (iii = 0; iii < 4; iii++) {
        Serial1.println("1F1002F1003R1004R100");
        delay(10);
        //Serial1.println("");
      }
      Serial1.println("");
      return;
    }
  } else if ((color_h_1 >= 240) || (color_h_2 >= 850) || (color_h_3 >= 115) || (color_h_4 >= 325)) {//////////////カラーセンサー
    if (color_h_1 >= 240) { ///////////////////////////////////////////////////1が白色の場合
      Serial.println("1　白ならば");
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (color_h_2 >= 850) {///////////////////////////////////////////////２が白色の場合
      Serial.println("2 白ならば");
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1F1002R1003F1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (color_h_3 >= 115) { //////////////////////////////////////////３が白色の場合
      Serial.println("3 白ならば");
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1F1002F1003F1004F100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (color_h_4 >= 325) { /////////////////////////////////////////４が白色の場合
      Serial.println("4 白ならば");
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1R1002F1003R1004F100");
        delay(10);
      }
      Serial1.println("");
      return;
    }
  } else if ((ir_h_1_and_ir_h_2 >= 2380) || (ir_h_4_and_ir_h_1 >= 2380) || (ir_h_2_and_ir_h_3 >= 2485) || (ir_h_3_and_ir_h_4 >= 2485)) {//////IRセンサー斜め　　　　　　　　　　
    if ((ir_h_1_and_ir_h_2) >= 2380) { /////////////////////////////////////////左斜め前
      Serial.println("左斜め前");
      //後ろ
      for (iii = 0; iii < 30; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      //横
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1F1002F1003F1004F100");
        delay(20);
        Serial1.println("");
        delay(1);
        Serial1.println("2F1004F100");
        delay(40);
      }
      Serial1.println("");
      return;
    } else if ((ir_h_4_and_ir_h_1) >= 2380) {//////////////////////////////////////右斜め前
      Serial.println("右斜め前");
      //後ろ
      for (iii = 0; iii < 30; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      //横
      for (iii = 0; iii < 10; iii++) {
        Serial1.println("1F1002F1003F1004F100");
        delay(20);
        Serial1.println("");
        delay(1);
        Serial1.println("1F1003F100");
        delay(40);
      }
      Serial1.println("");
      return;
    } else if ((ir_h_2_and_ir_h_3) >= 2485) { //////////////////////////////////////左斜め後ろ
      Serial.println("左斜め後ろ");
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if ((ir_h_3_and_ir_h_4) >= 2485) { ////////////////////////////////////////右斜め後ろ
      Serial.println("右斜め後ろ");
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    }
  } else if ((1200 <= ir_h_1) || (1180 <= ir_h_2) || (1215 <= ir_h_3) || (1200 <= ir_h_4)) {//////////////////////////IRセンサー直線
    if (1200 <= ir_h_1) { //////////////////////////////////////////////////////////////前
      Serial.println("前");
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("1F1002F1003F1004F100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (1180 <= ir_h_2) { ////////////////////////////////////////////////////////左
      Serial.println("左");
      //後ろ
      for (iii = 0; iii < 30; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      //左
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("2F1004F100");
        delay(10);
        Serial1.println("");
        delay(1);
        Serial1.println("1R1003R100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (1215 <= ir_h_3) { ///////////////////////////////////////////////////////////後ろ
      Serial.println("後ろ");
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("1R1002R1003R1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    } else if (1200 <= ir_h_4) { //////////////////////////////////////////////////////////////右
      Serial.println("右");
      //後ろ
      for (iii = 0; iii < 30; iii++) {
        Serial1.println("1F1002R1003F1004R100");
        delay(10);
      }
      //右
      for (iii = 0; iii < 20; iii++) {
        Serial1.println("1F1003F100");
        delay(10);
        Serial1.println("");
        delay(1);
        Serial1.println("2R1004R100");
        delay(10);
      }
      Serial1.println("");
      return;
    }
  }/*else if ((cm) <= 5)
    } else if ((cm) <= 5) {/////////////////////////////////////////////////////////////////////////５CM以内にものがある時
              for (iii = 0; iii < 10; iii++) {
          Serial1.println("1F1003F100");
          delay(1000);
          Serial1.println("2F1004F100");
          delay(1000);
          }
          Serial1.println("");
           return;
  }*/ else {////////////////////////////////////////////////////////////////////////////////////////////////それ以外
    Serial.println("それ以外");
    //Serial1.println("2F1004F100");
    //    delayMicroseconds(100);
    //Serial1.println("1F1003F100");
    //    delayMicroseconds(100);
    //Serial1.println("1R1003R100");
    //    delayMicroseconds(100);
    //Serial1.println("2R1004R100");
    //    delayMicroseconds(100);
    Serial1.println("");
    //return;
  }

}//loop終了_______________________________________________________________________________________________________________





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




/*







  //IRセンサー 測定設定
  float ir_h_1 = 0;                  //IRセンサー変数設定
  float ir_h_2 = 0;
  float ir_h_3 = 0;
  float ir_h_4 = 0;
  int i;
  //IRセンサー　測定開始
  for (i = 0; i < 5; i++) {
    ir_h_1 = ir_h_1 + analogRead(4) * 1.017293997965412;
  }
  ir_h_1 = ir_h_1 / 5;

  for (i = 0; i < 5; i++) {
    ir_h_2 = ir_h_2 + analogRead(5) * 1.038421599169263;
  }
  ir_h_2 = ir_h_2 / 5;

  for (i = 0; i < 5; i++) {
    ir_h_3 = ir_h_3 + analogRead(6) * 1.024590163934426;
  }
  ir_h_3 = ir_h_3 / 5;

  for (i = 0; i < 5; i++) {
    ir_h_4 = ir_h_4 + analogRead(7) * 1.048218029350105;
  }
  ir_h_4 = ir_h_4 / 5;
  //  ir_h_1  983      1000/983= 1.017293997965412
  //  ir_h_1  962      1000/963= 1.038421599169263
  //  ir_h_1  976      1000/976= 1.024590163934426
  //  ir_h_1  954      1000/954= 1.048218029350105
  //斜め処理をする変数
  float ir_h_1_and_ir_h_2 = ir_h_1 + ir_h_2;
  float ir_h_2_and_ir_h_3 = ir_h_2 + ir_h_3;
  float ir_h_3_and_ir_h_4 = ir_h_3 + ir_h_4;
  float ir_h_4_and_ir_h_1 = ir_h_4 + ir_h_1;

  //変数を出力
  Serial.print("   IR_1 =");
  Serial.print(ir_h_1);
  Serial.print("   IR_2 =");
  Serial.print(ir_h_2);
  Serial.print("   IR_3 =");
  Serial.print(ir_h_3);
  Serial.print("   IR_4 =");
  Serial.println(ir_h_4);
  delay(10);


  //カラーセンサー　測定設定
  int color_h_1 = 0;
  int color_h_2 = 0;
  int color_h_3 = 0;
  int color_h_4 = 0;
  int ii;

  for (ii = 0; ii < 3; ii++) {
    color_h_1 = color_h_1 + analogRead(0);
  }
  color_h_1 = color_h_1 / 3;    // 平均

  for (ii = 0; ii < 3; ii++) {
    color_h_2 = color_h_2 + analogRead(1);
  }
  color_h_2 = color_h_2 / 3;

  for (ii = 0; ii < 3; ii++) {
    color_h_3 = color_h_3 + analogRead(2);
  }
  color_h_3 = color_h_3 / 3;

  for (ii = 0; ii < 3; ii++) {
    color_h_4 = color_h_4 + analogRead(3);
  }
  color_h_4 = color_h_4 / 3;

  Serial.print("   color_1 =");
  Serial.print(color_h_1);
  Serial.print("   color_2 =");
  Serial.print(color_h_2);
  Serial.print("   color_3 =");
  Serial.print(color_h_3);
  Serial.print("   color_4 =");
  Serial.println(color_h_4);
  delay(10);



  //コンパスセンサー　測定開始
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
  delay(10);

  //超音波センサー　　測定開始
  long d;
  long in;
  long cm;
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(5);
  digitalWrite(5, LOW);
  pinMode(5, INPUT);
  d = pulseIn(7, HIGH);
  cm = d / 59;

  Serial.print(cm);
  Serial.println();
  delay(10);

*/
