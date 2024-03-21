
const int a_pin_color[] = {0, 1, 2, 3};

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

}

void loop() {

  int color_angle = get_color_angle();

}


int get_color_angle() {

  int color_answer[3];
  int color_angle;


  color_answer[0] = analogRead(a_pin_color[0]);
  color_answer[1] = analogRead(a_pin_color[1]);
  color_answer[2] = analogRead(a_pin_color[2]);
  color_answer[3] = analogRead(a_pin_color[3]);


  if (color_answer[0] > 250) {
    color_angle = 360;
  } else if (color_answer[1] > 70) {
    color_angle = 90;
  } else if (color_answer[2] > 250) {
    color_angle = 180;
  } else if (color_answer[3] > 250) {
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
