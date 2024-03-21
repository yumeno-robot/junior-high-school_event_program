


int get_color_angle() {

  int color_answer[4];
  int color_angle;

  color_answer[0] = analogRead(a_pin_color[0]);
  color_answer[1] = analogRead(a_pin_color[1]);
  color_answer[2] = analogRead(a_pin_color[2]);
  color_answer[3] = analogRead(a_pin_color[3]);


  /*if (color_answer[0] > 30) {
    color_angle = 360;
    tone(oto, 4000, 200) ;
  } else if (color_answer[1] > 30) {
    color_angle = 90;
    tone(oto, 4000, 200) ;
  } else if (color_answer[2] > 30) {
    color_angle = 180;
    tone(oto, 4000, 200) ;
  } else if (color_answer[3] > 50) {
    color_angle = 270;
    tone(oto, 4000, 200) ;
  } else {
    color_angle = 0;
  }
*/
  Serial.print("color_1:");
  Serial.print(color_answer[0]);
  Serial.print("  color_2:");
  Serial.print(color_answer[1]);
  Serial.print("  color_3:");
  Serial.print(color_answer[2]);
  Serial.print("  color_4:");
  Serial.print(color_answer[3]);
  Serial.print("                 ");
  Serial.print("   color_answer:");
  Serial.println(color_angle);

  return color_angle;
}
