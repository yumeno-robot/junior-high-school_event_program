int ir_answer[4];
int ir_angle;
int get_ir_angle() {



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

  //前の処理の中に斜め前処理を書くことにした
  if ((best_id == 0) && (10 < ir_answer[0])) {//前
    if (ir_answer[0] - ir_answer[1] >= 50) {
      ir_angle = 45;
    } else if (ir_answer[0] - ir_answer[3] >= 50) {
      ir_angle = 315;
    } else {
      ir_angle = 360;
    }
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
