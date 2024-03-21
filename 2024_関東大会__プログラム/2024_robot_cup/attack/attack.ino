
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

  Mota_start(ir_angle, turn_angle , mota_ok);
  Mota_start(color_angle, turn_angle , mota_ok);




  //検証用
  //Mota_start(0, 0, mota_ok);
  //Mota_serial();

}
