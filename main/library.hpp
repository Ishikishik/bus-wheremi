#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secret.hpp" 

class LSI {
public:
    // コンストラクタでSoftwareSerialインスタンスを渡す
    LSI(SoftwareSerial& serial);
    // 初期化
    void lsibegin(long baudrate = 9600);
    // 発声させる
    void hatuonn(String msg);
    void sendToLSI(String s);
    //数字をローマ字に変換する
    String convertNumberString(String numStr);

private:
    SoftwareSerial& lsiSerial;
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


class NetClient {
public:
    NetClient();
    void begin(const String &ssid, const String &pass);
    String queryAPI(float x, float y, const String &auth, const String &mode);

};


#endif
