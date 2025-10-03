#include <SoftwareSerial.h>

// RX=10, TX=11 のソフトウェアUART
SoftwareSerial mySerial(0, 1);

void setup() {
  // ESP32本体のデバッグ用シリアル
  Serial.begin(115200);
  delay(1000);
  Serial.println("SoftwareSerial test start");

  // 音声合成LSIとの通信
  mySerial.begin(9600);
}

void loop() {
  // 3秒ごとに発声テスト
  hatuonn("chidorinochi/yoshinonoyo/uenonou/fujisannofu/choofu");
  delay(3000);
}

// -----------------------------
// 文字列を渡すと音声合成LSIで発声する関数
// 区切り「/」ごとに分割して送信
// -----------------------------
void hatuonn(String msg) {
  String segment = "";
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i];
    if (c == '/') {
      sendToLSI(segment);
      segment = "";
    } else {
      segment += c;
    }
  }
  if (segment.length() > 0) sendToLSI(segment);
}

// -----------------------------
// LSIに文字列を送信して「>」応答を待つ
// -----------------------------
void sendToLSI(String s) {
  mySerial.print(s);
  mySerial.print("\r"); // 改行で送信完了

  // 発声準備完了を待つ
  while (true) {
    if (mySerial.available() > 0) {
      char c = mySerial.read();
      if (c == '>') {
        Serial.println("LSI ready >");
        break;
      }
    }
    delay(5);
  }
}
