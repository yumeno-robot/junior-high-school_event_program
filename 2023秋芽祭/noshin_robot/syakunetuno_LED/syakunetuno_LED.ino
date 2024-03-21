

const int a_pin_color[] = {0, 1, 2, 3};
const int a_pin_ir[] = {4, 5, 6, 7};
const int all_senswer = 2;
const int oto = 13;

void setup() {

  //Serial.begin(9600);
  Serial1.begin(19200);
  pinMode(oto, OUTPUT);
  pinMode(all_senswer, OUTPUT);
  digitalWrite(all_senswer, HIGH);



}

void loop() {

  int color_angle = get_color_angle();
  int ir_angle = get_ir_angle();


  mota(color_angle, ir_angle);



}
