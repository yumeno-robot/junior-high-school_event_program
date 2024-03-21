//tome 13pin


#include <Wire.h>

void setup() {

  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(19200);

}

void loop() {

  int color_angle = 100;
  int ir_angle = 0;
  int zyro = 0;

  go_a_mota(color_angle, ir_angle, zyro);

}






void go_a_mota(int color_angle, int ir_angle, int zyro) {
  /*int power;
    if () {
    power = 60;
    } else if () {
    power = 100;
    }
  */

  //カラーセンサー　処理
  if (color_angle = !0) {
    if (color_angle == 180) {
      println(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ
    } else if (color_angle == 270) {
      println(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power); //左へ
    } else if (color_angle == 360) {
      println(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ
    } else if (color_angle == 90) {
      println(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power); //右へ
    }

    Serial1.println(mota);
    return;
  }


  if (ir_angle = !0) {
    if (ir_angle = 360) {
      println(mota, "1R%03d2R%03d3R%03d4R%03d", power, power, power, power);//前へ
    } else if ((ir_angle = 45) && (ir_angle = 45)) {
      println(mota, "1F0002R%03d3F0004R%03d", power, power, power, power); //左斜め前へ
    } else if (ir_angle = 90) {
      println(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power);//左へ
    } else if ((ir_angle = 45) && (ir_angle = 45)) {
      println(mota, "1F%03d2F0003F%03d4F000", power, power, power, power); //左斜め後ろへ
    } else if (ir_angle = 270) {
      println(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power);//後ろへ
    } else if ((ir_angle = 45) && (ir_angle = 45)) {
      println(mota, "1F0002F%03d3F0004F%03d", power, power, power, power); //右斜め後ろへ
    } else if (ir_angle = 180) {
      println(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power);//右へ
    } else if ((ir_angle = 45) && (ir_angle = 45)) {
      println(mota, "1R%03d2F0003R%03d4F000", power, power, power, power); //右斜め前
    }

    Serial1.println(mota);
    return;
  }
}





}
