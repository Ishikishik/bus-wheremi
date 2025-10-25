
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "library.hpp"
#include "secret.hpp"

// SoftwareSerialのインスタンス作成
SoftwareSerial gpsSerial(3, 2); 
SoftwareSerial lsiSerial(6, 5);

GPSManager gpsManager(gpsSerial);
LSI lsi(lsiSerial);

NetClient net; 

void setup() {
    lsi.lsibegin(9600);
    gpsManager.begin(9600);
    net.begin(SSID, PASS);
}

void loop() {
    
    float lat = 0.0;//getgpsはtruefalseで管理しているので初期化する。
    float lng = 0.0;
    String mode = "roma";
    if (gpsManager.getGPS(lat, lng)) {
        String response = net.queryAPI(lat, lng, AUTH, mode);

        // LSIで発音
        lsi.hatuonn(response);
        delay(5000);
    }

}

