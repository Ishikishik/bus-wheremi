#ifndef MY_LSI_H
#define MY_LSI_H

#include <Arduino.h>
#include <SoftwareSerial.h>

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

#endif
