#include <Arduino.h>
#include <SoftwareSerial.h>
#include "library.hpp"

// SoftwareSerialのインスタンス作成
SoftwareSerial mySerial(0, 1); // 実際のピン番号はライブラリ外で管理
LSI lsi(mySerial);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("LSI test start");

    lsi.begin(9600);
}

void loop() {
    lsi.hatuonn("chidorinochi/yoshinonoyo/uenonou/fujisannofu/choofu");
    delay(3000);
}