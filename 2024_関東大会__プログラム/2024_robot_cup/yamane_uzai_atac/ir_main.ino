
const int a_pin_ir[] = {4, 5, 6, 7};

void setup() {

  Serial.begin(9600);
  Serial1.begin(19200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

}

void loop() {

  int ir_angle = get_ir_angle();

}

int get_ir_angle() {

  int ir_answer[4];
  int ir_angle;


  ir_answer[0] = analogRead(a_pin_ir[0]);
  ir_answer[1] = analogRead(a_pin_ir[1]);
  ir_answer[2] = analogRead(a_pin_ir[2]);
  ir_answer[3] = analogRead(a_pin_ir[3]);



  if (ir_answer[0] > 80) {
    ir_angle = 360;
  } else if (ir_answer[1] > 80) {
    ir_angle = 90;
  } else if (ir_answer[2] > 80) {
    ir_angle = 180;
  } else if (ir_answer[3] > 80) {
    ir_angle = 270;
  } else {
    ir_angle = 0;
  }

  Serial.print("ir_1:");
  Serial.print(ir_answer[0]);
  Serial.print("  ir_2:");
  Serial.print(ir_answer[1]);
  Serial.print("  ir_3:");
  Serial.print(ir_answer[2]);
  Serial.print("  ir_4:");
  Serial.print(ir_answer[3]);

  Serial.print("   ir_answer:");
  Serial.println(ir_angle);

  return ir_angle;
}
