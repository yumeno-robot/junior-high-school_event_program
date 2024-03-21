
const int MOTOR_DEG[] = {45, 135, 225, 315}; // モーター配置角度
int out_speed[4];


void Mota_serial() {
  Serial.print("  0:");
  Serial.print(out_speed[0]);
  Serial.print(" 1:");
  Serial.print(out_speed[1]);
  Serial.print(" 2:");
  Serial.print(out_speed[2]);
  Serial.print(" 3:");
  Serial.println(out_speed[3]);
}



void Mota_start(int LINEIR, int GYRO, int SPEED) {
  /*
     LINEIR 進行角度(0:無動作,1-360:進む)
     GYRO   目標傾き角度(1-360)
     SPEED  加減速(0-254) 進行角度に係る
     Mota_start(LINEIR, GYRO, SPEED);
  */

  //SPEED = map(SPEED, 0, 100, 0, 100);

  int gyro_speed = F_MD_gyro(GYRO, SPEED);
  int lineIr_speed[4];

  if (LINEIR != 0) {
    float sine_power[4];
    float big_power = 0;

    for (int i = 0; i < 4; i++) {
      int sine_thita = MOTOR_DEG[i] - LINEIR;
      sine_power[i] = (sin(sine_thita * PI / 180));
      big_power = max(big_power, abs(sine_power[i]));
    }
    float  aaa = 1 / big_power;
    for (int i = 0; i < 4; i++) {
      lineIr_speed[i] = ((sine_power[i] * aaa)) * SPEED;
    }
  } else {
    for (int i = 0; i < 4; i++) {
      lineIr_speed[i] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    out_speed[i] = gyro_speed * 0.6 + lineIr_speed[i] * 1;
  }

  for (int i = 0; i < 4; i++) {
    if (out_speed[i] == 0) {
      out_speed[i] = 0;
    } else if (out_speed[i] > 0) {
      out_speed[i] = constrain(out_speed[i], 40, 99);
    } else if (out_speed[i] < 0) {
      out_speed[i] = constrain(out_speed[i], -99, -40);
    }
  }










  String m1;
  String m2;
  String m3;
  String m4;

  //正
  //負
  //１０以下
  if (out_speed[0] > 0) {
    if (out_speed[0] >= 10) {
      m1.concat("1F0");
      m1.concat(abs(out_speed[0]));
    } else if (out_speed[0] < 10) {
      m1.concat("1F00");
      m1.concat(abs(out_speed[0]));
    }
  } else if (out_speed[0] < 0) {
    if (abs(out_speed[0]) >= 10) {
      m1.concat("1R0");
      m1.concat(abs(out_speed[0]));
    } else if (abs(out_speed[0]) < 10) {
      m1.concat("1R00");
      m1.concat(abs(out_speed[0]));
    }
  }

  if (out_speed[1] > 0) {
    if (out_speed[1] >= 10) {
      m2.concat("2F0");
      m2.concat(abs(out_speed[1]));
    } else if (out_speed[1] < 10) {
      m2.concat("2F00");
      m2.concat(abs(out_speed[1]));
    }
  } else if (out_speed[1] < 0) {
    if (abs(out_speed[1]) >= 10) {
      m2.concat("2R0");
      m2.concat(abs(out_speed[1]));
    } else if (abs(out_speed[1]) < 10) {
      m2.concat("2R00");
      m2.concat(abs(out_speed[1]));
    }
  }

  if (out_speed[2] > 0) {
    if (out_speed[2] >= 10) {
      m3.concat("3F0");
      m3.concat(abs(out_speed[2]));
    } else if (out_speed[2] < 10) {
      m3.concat("3F00");
      m3.concat(abs(out_speed[2]));
    }
  } else if (out_speed[2] < 0) {
    if (abs(out_speed[2]) >= 10) {
      m3.concat("3R0");
      m3.concat(abs(out_speed[2]));
    } else if (abs(out_speed[2]) < 10) {
      m3.concat("3R00");
      m3.concat(abs(out_speed[2]));
    }
  }

  if (out_speed[3] > 0) {
    if (out_speed[3] >= 10) {
      m4.concat("4F0");
      m4.concat(abs(out_speed[3]));
    } else if (out_speed[3] < 10) {
      m4.concat("4F00");
      m4.concat(abs(out_speed[3]));
    }
  } else if (out_speed[3] < 0) {
    if (abs(out_speed[3]) >= 10) {
      m4.concat("4R0");
      m4.concat(abs(out_speed[3]));
    } else if (abs(out_speed[3]) < 10) {
      m4.concat("4R00");
      m4.concat(abs(out_speed[3]));
    }
  }



  String final_go_mota = m1 + m2 + m3 + m4;
  Serial.println(final_go_mota);
  Serial1.println(final_go_mota);


}







int F_MD_gyro(int gyro_deg, int myspeed) {
  /*
    返り値：80-250
    それぞれのモーターごとに計算してね！！
  */
  int pwm_val = 0;
  myspeed = 255;
  if (gyro_deg != 0) {
    if (4 <= gyro_deg && gyro_deg <= 180) {
      //左回り
      pwm_val = map(gyro_deg, 4, 180, 40, myspeed);
    } else if (180 <= gyro_deg && gyro_deg <= 356) {
      //右回り
      pwm_val = map(gyro_deg, 356, 180, -40, -myspeed);
    } else {
      //回らない
      pwm_val = 0;
    }
  } else {
    pwm_val = 0;
  }
  return pwm_val;
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
