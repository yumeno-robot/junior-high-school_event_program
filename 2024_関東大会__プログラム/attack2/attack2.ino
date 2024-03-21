
#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;
#define Gyro_X 173
#define Gyro_Y -30
#define Gyro_Z 10
#define Accel_Z 4871

#define mota_ok 100
#define mota_slow 70
#define mota_no 0

const int a_pin_color[] = {0, 1, 2, 3};
const int a_pin_ir[] = {4, 5, 6, 7};
const int all_senswer = 2;
const int oto = 13;



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
  int ir_angle = get_ir_angle();
  int color_angle = get_color_angle();
  int turn_angle = get_zyro();

  Serial.println(ir_angle);
  Serial.println(color_angle);
  Serial.print("gyro___");
  Serial.println(turn_angle);
   if (color_angle == 360) {
    
    Serial1.println("1R0802R0803R0804R080");
    
  } else if (color_angle == 90) {
    
    Serial1.println("1F0802R0803F0804R080");
    
  } else if (color_angle == 180) {
    
    Serial1.println("1F0802F0803F0804F080");
    
  } else if (color_angle == 270) {
    
    Serial1.println("1R0802F0803R0804F080");
  } else {
  
  if (ir_angle == 360 && 170 <= turn_angle <= 190) {
    Serial1.println("1F1002F1003F1004F100");
  }
  else if (ir_angle == 360 &&  190 < turn_angle <= 359) {
    Serial1.println("1F1002F1003F0904F090");
  }
   else if (ir_angle == 360 &&  1 < turn_angle <= 170) {
    Serial1.println("1F0902F0903F1004F100");
  }
  else if (ir_angle == 90) {
    Serial1.println("1R0902F0403R0904F040");
  }
  else if (ir_angle == 270) {
    Serial1.println("1F0402R0903F0404R090");
  }
   else if (ir_angle == 45) {
    Serial1.println("2F0904F090");
  }
  else if (ir_angle == 315) {
    Serial1.println("1F0903F090");
  }
  else  {
    Serial1.println("1R0002R0003R0004R000");
  }
  } /*} else if (ir_answer[2] >= 0) {

       }*/


  //検証用
  //Mota_start(0, 0, mota_ok);
  //Mota_serial();

}
