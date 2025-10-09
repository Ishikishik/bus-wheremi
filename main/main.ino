
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "library.hpp"

// SoftwareSerialのインスタンス作成
SoftwareSerial gpsSerial(0, 1); 
SoftwareSerial lsiSerial(6, 5);

GPSManager gpsManager(gpsSerial);
LSI lsi(lsiSerial);

void setup() {
    lsi.begin(9600);
    gpsManager.begin(9600);
    //wifi.setupWiFi("SSID", "PASS");
}

void loop() {
    float lat = 0.0;//getgpsはtruefalseで管理しているので初期化する。
    float lng = 0.0;
    if (gpsManager.getGPS(lat, lng)) {
        String latitudeSpeech = "idoha " + lsi.convertNumberString(String(lat, 6));
        String longitudeSpeech = "keidoha " + lsi.convertNumberString(String(lng, 6));

        lsi.hatuonn(latitudeSpeech + "/" + longitudeSpeech);
    }


    delay(1000);
}
