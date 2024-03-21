
const int a_pin_color[] = {0, 1, 2, 3};
int oto = 13;
void setup() {
  //Serial.begin(9600);
  Serial1.begin(19200);
  pinMode(oto, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

}

void loop() {

  int color_angle = get_color_angle();
  mota(color_angle);


}


void mota(int color_angle) {
  char mota[100];
  int power = 100;

  if (color_angle == 180) {
    sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ
    tone(oto, 4000, 200) ;
  } else if (color_angle == 270) {
    sprintf(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power); //左へ
    tone(oto, 4000, 200) ;
  } else if (color_angle == 360) {
    sprintf(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ
    tone(oto, 4000, 200) ;
  } else if (color_angle == 90) {
    sprintf(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power); //右へ
    tone(oto, 4000, 200) ;
  } else {
    sprintf(mota, ""); //右へ
  }

  Serial1.println(mota);


}














int get_color_angle() {

  int color_answer[3];
  int color_angle;

  color_answer[0] = analogRead(a_pin_color[0]);
  color_answer[1] = analogRead(a_pin_color[1]);
  color_answer[2] = analogRead(a_pin_color[2]);
  color_answer[3] = analogRead(a_pin_color[3]);


  if (color_answer[0] > 50) {
    color_angle = 360;
  } else if (color_answer[1] > 8) {
    color_angle = 90;
  } else if (color_answer[2] > 50) {
    color_angle = 180;
  } else if (color_answer[3] > 200) {
    color_angle = 270;
  } else {
    color_angle = 0;
  }

  Serial.print("color_1:");
  Serial.print(color_answer[0]);
  Serial.print("  color_2:");
  Serial.print(color_answer[1]);
  Serial.print("  color_3:");
  Serial.print(color_answer[2]);
  Serial.print("  color_4:");
  Serial.print(color_answer[3]);

  Serial.print("   color_answer:");
  Serial.println(color_angle);

  return color_angle;
}
