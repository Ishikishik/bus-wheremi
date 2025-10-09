#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h>


class WiFiManager {
public:
    void setupWiFi(const char* ssid, const char* pass);
};


class LSI {
public:
    // コンストラクタでSoftwareSerialインスタンスを渡す
    LSI(SoftwareSerial& serial);
    // 初期化
    void begin(long baudrate = 9600);
    // 発声させる
    void hatuonn(String msg);
    //数字をローマ字に変換する
    String convertNumberString(String numStr);

private:
    SoftwareSerial& lsiSerial;
    void sendToLSI(String s);
    String numToEnglish(char c);
};

class GPSManager {
    public:
    GPSManager(SoftwareSerial& serial);
    void begin(long baudrate = 9600);
    bool getGPS(float &lat, float &lng);

private:
    SoftwareSerial& gpsSerial;
    TinyGPSPlus gps;
};



#endif
