

void mota(int color_angle, int ir_angle) {
  char mota[100];
  int power = 100;

  if (color_angle != 0) {
    if (color_angle == 180) {
      sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ
      tone(oto, 4000, 200) ;
      Serial1.println(mota);
      delay(500);
      return;
    } else if (color_angle == 270) {
      sprintf(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power); //左へ
      tone(oto, 4000, 200) ;
      Serial1.println(mota);
      delay(500);
      return;
    } else if (color_angle == 360) {
      sprintf(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ
      tone(oto, 4000, 200) ;
      Serial1.println(mota);
      delay(500);
      return;
    } else if (color_angle == 90) {
      sprintf(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power); //右へ
      tone(oto, 4000, 200) ;
      Serial1.println(mota);
      delay(500);
      return;
    }
    return;
  }

  if (color_angle == 0) {
    if (ir_angle == 360) {
      sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ//
    } else if (ir_angle == 90) {
      sprintf(mota, "1F%03d2F%03d3R%03d4R%03d", power, power, power, power);//左回転
    } else if (ir_angle == 180) {
      sprintf(mota, "1F%03d2F%03d3R%03d4R%03d", power, power, power, power);//左回転
    } else if (ir_angle == 270) {
      sprintf(mota, "1R%03d2R%03d3F%03d4F%03d", power, power, power, power);//右回転
    } else {
      sprintf(mota, "");//ストップ
    }
  }

  Serial1.println(mota);

}





//sprintf(mota, "1R%03d2R%03d3R%03d4R%03d" , power, power, power, power); //前へ//
//sprintf(mota, "2R%03d4R%03d", power, power);//左斜め前
//sprintf(mota, "1F%03d2R%03d3F%03d4R%03d", power, power, power, power); //左へ//
//sprintf(mota, "1F%03d3F%03d", power, power);//左斜め後ろ
//sprintf(mota, "1F%03d2F%03d3F%03d4F%03d", power, power, power, power); //後ろへ//
//sprintf(mota, "2F%03d4F%03d", power, power);//右斜め後ろ
//sprintf(mota, "1R%03d2F%03d3R%03d4F%03d", power, power, power, power); //右へ//
//sprintf(mota, "1R%03d3R%03d", power, power);//右斜め前
//sprintf(mota, "1R%03d2R%03d3R%03d4R%03d", 0, 0, 0, 0);//ストップ
//sprintf(mota, "");//ストップ
//sprintf(mota, "1R%03d2R%03d3F%03d4F%03d", power, power, power, power);//右回転
//sprintf(mota, "1F%03d2F%03d3R%03d4R%03d", power, power, power, power);//左回転
