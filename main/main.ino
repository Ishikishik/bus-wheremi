#include <Arduino.h>
#include <SoftwareSerial.h>
#include "library.hpp"

// SoftwareSerialのインスタンス作成
SoftwareSerial mySerial(5, 6); // 実際のピン番号はライブラリ外で管理
LSI lsi(mySerial);
WiFiManager wifi; 

void setup() {
    lsi.begin(9600);
    wifi.setupWiFi("SSID", "PASS");
}

void loop() {
    lsi.hatuonn("chidorinochi/yoshinonoyo/uenonou/fujisannofu/choofu");
    delay(3000);
}