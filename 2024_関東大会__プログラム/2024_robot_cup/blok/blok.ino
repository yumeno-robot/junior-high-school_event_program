
#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;
#define Gyro_X 180
#define Gyro_Y -18
#define Gyro_Z -58
#define Accel_Z 721

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

  get_ir_angle();
  get_color_angle();
  Serial.print("gyro_____");
  Serial.println( get_zyro());


  if (color_answer[0] > 50) {
    
  }
  ir_answer[];
  color_answer[];


  //検証用
  Mota_start(0, 0, mota_ok);
  Mota_serial();

}
