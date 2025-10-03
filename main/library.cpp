#include "library.hpp"

LSI::LSI(SoftwareSerial& serial) : mySerial(serial) {}

void LSI::begin(long baudrate) {
    mySerial.begin(baudrate);
}

void LSI::hatuonn(String msg) {
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

void LSI::sendToLSI(String s) {
    mySerial.print(s);
    mySerial.print("\r"); // 改行で送信完了

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
