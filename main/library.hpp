#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFi.h>

class LSI {
public:
    // コンストラクタでSoftwareSerialインスタンスを渡す
    LSI(SoftwareSerial& serial);

    // 初期化
    void begin(long baudrate = 9600);

    // 発声させる
    void hatuonn(String msg);

private:
    SoftwareSerial& mySerial;

    void sendToLSI(String s);
};

class WiFiManager {
public:
    void setupWiFi(const char* ssid, const char* pass);
};

#endif
