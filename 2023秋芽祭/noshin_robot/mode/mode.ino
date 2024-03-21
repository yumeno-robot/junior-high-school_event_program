//get_mode   1=アタッカー::2=ブロッカー


void setup() {

  Serial.begin(19200);

}

void loop() {

  Serial.println("なし");

  int get_mode = 0;
  if (Serial.available() > 0) {
    get_mode = (int)Serial.read();
    if (get_mode == 1) {

      Serial.println("アタッカー");

    } else if (get_mode == 2) {

      Serial.println("ブロッカー");

    }
  }
}
