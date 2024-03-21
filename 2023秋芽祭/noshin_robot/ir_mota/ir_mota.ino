
const int a_pin_ir[] = {4, 5, 6, 7};

void setup() {

  //Serial.begin(9600);
  Serial1.begin(19200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

}

void loop() {

  int ir_angle = get_ir_angle();
  mota(ir_angle);

}


void mota(int ir_angle) {
  char mota[100];
  int power = 100;

  if ((ir_angle == 45) || (ir_angle == 315)) {
    power = 80;
  } else {
    power = 100;
  }

  if (ir_angle == 360) {
    sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ//
  } else if (ir_angle == 45) {
    sprintf(mota, "2R%03d4R%03d", power, power);//左斜め前
  } else if (ir_angle == 90) {
    sprintf(mota, "1F%03d3F%03d", power, power);//左斜め後ろ
  } else if (ir_angle == 135) {
    sprintf(mota, "1F%03d3F%03d", power, power);//左斜め後ろ
  } else if (ir_angle == 180) {
    sprintf(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ//
  } else if (ir_angle == 225) {
    sprintf(mota, "2F%03d4F%03d", power, power);//右斜め後ろ
  } else if (ir_angle == 270) {
    sprintf(mota, "2F%03d4F%03d", power, power);//右斜め後ろ
  } else if (ir_angle == 315) {
    sprintf(mota, "1R%03d3R%03d", power, power);//右斜め前
  } else {
    sprintf(mota, "");//ストップ
    //sprintf(mota, "");//ストップ
  }

  Serial1.println(mota);

  //sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ//
  //sprintf(mota, "2R%03d4R%03d", power, power);//左斜め前
  //sprintf(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power); //左へ//
  //sprintf(mota, "1F%03d3F%03d", power, power);//左斜め後ろ
  //sprintf(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ//
  //sprintf(mota, "2F%03d4F%03d", power, power);//右斜め後ろ
  //sprintf(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power); //右へ//
  //sprintf(mota, "1R%03d3R%03d", power, power);//右斜め前
  //sprintf(mota, "1R%03d2R%03d3R%03d4R%03d", 0, 0, 0, 0);//ストップ
  //sprintf(mota, "1R%03d2R%03d3F%03d4F%03d", power, power, power, power);//右回転
  //sprintf(mota, "1F%03d2F%03d3R%03d4R%03d", power, power, power, power);//左回転
}








int get_ir_angle() {

  int ir_answer[4];
  int ir_angle;

  ir_answer[0] = analogRead(a_pin_ir[0]);
  ir_answer[1] = analogRead(a_pin_ir[1]);
  ir_answer[2] = analogRead(a_pin_ir[2]);
  ir_answer[3] = analogRead(a_pin_ir[3]);


//最大値と最大IDの取得
  int max_answer;
  int best_id;
  max_answer = max(max_answer, ir_answer[0]);
  max_answer = max(max_answer, ir_answer[1]);
  max_answer = max(max_answer, ir_answer[2]);
  max_answer = max(max_answer, ir_answer[3]);
  if (max_answer == ir_answer[0]) {
    best_id = 0;
  } else if (max_answer == ir_answer[1]) {
    best_id = 1;
  } else if (max_answer == ir_answer[2]) {
    best_id = 2;
  } else if (max_answer == ir_answer[3]) {
    best_id = 3;
  }


  if ((best_id == 0) && (10 < ir_answer[0])) {//前
    ir_angle = 360;
  } else if ((best_id == 1) && (10 < ir_answer[1])) {//左
    ir_angle = 90;
  } else if ((best_id == 2) && (10 < ir_answer[2])) {//後ろ
    ir_angle = 180;
  } else if ((best_id == 3) && (10 < ir_answer[3])) {//右
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
