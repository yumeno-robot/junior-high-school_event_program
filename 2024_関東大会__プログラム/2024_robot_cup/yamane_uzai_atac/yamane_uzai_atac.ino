  
#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;
#define Gyro_X 173
#define Gyro_Y -30
#define Gyro_Z 10
#define Accel_Z 4871

const int a_pin_color[] = {0, 1, 2, 3};
const int a_pin_ir[] = {4, 5, 6, 7};
const int all_senswer = 2;
const int oto = 13;
int color_answer[4];
int ir_answer[4];
int gyro_answer;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(19200);
  start_gyro();
  pinMode(oto, OUTPUT);
  pinMode(all_senswer, OUTPUT);
  digitalWrite(all_senswer, HIGH);

  tone(oto, 4000, 200) ;
}

void loop() {
  //センサーインプット達
  gyro_answer = get_zyro();
  color_answer[0] = analogRead(a_pin_color[0]);
  color_answer[1] = analogRead(a_pin_color[1]);
  color_answer[2] = analogRead(a_pin_color[2]);
  color_answer[3] = analogRead(a_pin_color[3]);
  ir_answer[0] = analogRead(a_pin_ir[0]);
  ir_answer[1] = analogRead(a_pin_ir[1]);
  ir_answer[2] = analogRead(a_pin_ir[2]);
  ir_answer[3] = analogRead(a_pin_ir[3]);
  Serial.print("  C_1:");
  Serial.print(color_answer[0]);
  Serial.print("  C_2:");
  Serial.print(color_answer[1]);
  Serial.print("  C_3:");
  Serial.print(color_answer[2]);
  Serial.print("  C_4:");
  Serial.print(color_answer[3]);
  Serial.print("                   ");
  Serial.print("  A_1:");
  Serial.print(ir_answer[0]);
  Serial.print("  A_2:");
  Serial.print(ir_answer[1]);
  Serial.print("  A_3:");
  Serial.print(ir_answer[2]);
  Serial.print("  A_4:");
  Serial.print(ir_answer[3]);
  Serial.print("________gyro:");
  Serial.print(gyro_answer);


  //if文処理
  if ((gyro_answer >= 210) && (gyro_answer <= 360)) {
    //左周り
  } else if ((gyro_answer >= 1) && (gyro_answer <= 150)) {
    //右回り処理
  } else {
    //カラーセンサー処理
    if (color_answer[0] < 50) {

    } else if (color_answer[1] < 50) {

    } else if (color_answer[2] < 50) {

    } else if (color_answer[3] < 50) {

    }


    if (ir_answer[0] < 50) {



    } else if (ir_answer[1] < 50) {

    } else if (ir_answer[2] < 50) {

    } else if (ir_answer[3] < 50) {

    }















  }
