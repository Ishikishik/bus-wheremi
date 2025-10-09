#include "library.hpp"


//ーーーーーーーーーーーーーーーーーーーwifiーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
void WiFiManager::setupWiFi(const char* ssid, const char* pass) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}


//ーーーーーーーーーーーーーーーーーーーーーーーーーーーLSIーーーーーーーーーーーーーーーーーーーーーーーーーーー
LSI::LSI(SoftwareSerial& serial) : lsiSerial(serial) {}

void LSI::begin(long baudrate) {//lsiのシリアル通信を開始
    lsiSerial.begin(baudrate);
}

void LSI::hatuonn(String msg) {//メッセージを発音する。ローマ字で指示、/で句点
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

void LSI::sendToLSI(String s) {//LSIとのシリアル通信を担当(下請け)
    lsiSerial.print(s);
    lsiSerial.print("\r"); // 改行で送信完了

    while (true) {
        if (lsiSerial.available() > 0) {
            char c = lsiSerial.read();
            if (c == '>') {
                break;
            }
        }
        delay(5);
    }
}

String LSI::convertNumberString(String numStr) {//数字をローマ字に変換する(デバック用)
    String result = "";
    for (int i = 0; i < numStr.length(); i++) {
        result += numToEnglish(numStr[i]);
    }
    return result;
}

String LSI::numToEnglish(char c) {//数字ローマ字変換表(デバック用)
    switch (c) {
        case '0': return "zero";
        case '1': return "ichi";
        case '2': return "ni";
        case '3': return "sann";
        case '4': return "yonn";
        case '5': return "goo";
        case '6': return "roku";
        case '7': return "nana";
        case '8': return "hachi";
        case '9': return "kyuu";
        default: return "";
    }
}


/*ーーーーーーーーーーーーーーーーーーーーーーーーーーーGPSーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
GPSManager::GPSManager(SoftwareSerial& serial) : gpsSerial(serial) {}

void GPSManager::begin(long baudrate) {
    gpsSerial.begin(baudrate);
}

bool GPSManager::getGPS(float &lat, float &lng) {
    unsigned long start = millis();
    while (millis() - start < 1000) { // 最大1秒間データを読む
        while (gpsSerial.available() > 0) {
            gps.encode(gpsSerial.read());
        }
        if (gps.location.isUpdated()) {
            lat = gps.location.lat();
            lng = gps.location.lng();
            return true;
        }
    }
    return false;
}
