#include "library.hpp"

// --- LSIクラス ---
LSI::LSI(SoftwareSerial& serial) : lsiSerial(serial) {}

void LSI::lsibegin(long baudrate) { 
    lsiSerial.begin(baudrate); 
}

void LSI::hatuonn(String msg) {
      // シリアルバッファをクリア
    while (lsiSerial.available() > 0) lsiSerial.read();

    const int MAX_CHUNK = 120;     // 安全マージンを持たせて128byte未満
    const int INTERVAL_MS = 40;    // チャンク送信間隔
    int start = 0;

    // 先頭に空白を追加（LSI が '/' 開始を正しく認識しない場合用）
    msg = " " + msg;

    while (start <msg.length()) {
        int end = start + MAX_CHUNK;
        if (end > msg.length()) end = msg.length();
        String chunk = msg.substring(start, end);

        // チャンク送信
        lsiSerial.print(chunk);
        lsiSerial.print("\r");

        // '>' が返るまで待機
        bool received = false;
        unsigned long timeout = millis() + 5000; // 5秒タイムアウト
        while (!received && millis() < timeout) {
            while (lsiSerial.available() > 0) {
                char c = lsiSerial.read();
                if (c == '>') {
                    received = true;
                    break;
                }
            }
            delay(5);
        }

        // 安定化のため少し待つ
        delay(INTERVAL_MS);
        start = end;
    }
}

void LSI::sendToLSI(String s) {
    lsiSerial.print(s);
    lsiSerial.print("\r");
    while (true) {
        if (lsiSerial.available() > 0) {
            char c = lsiSerial.read();
            if (c == '>') break;
        }
        delay(5);
    }
}

String LSI::numToEnglish(char c) {
    switch (c) {
        case '0': return "zero";
        case '1': return "one";
        case '2': return "two";
        case '3': return "three";
        case '4': return "four";
        case '5': return "five";
        case '6': return "six";
        case '7': return "seven";
        case '8': return "eight";
        case '9': return "nine";
        default: return "";
    }
}

String LSI::convertNumberString(String numStr) {
    String result = "";
    for (int i = 0; i < numStr.length(); i++) {
        result += numToEnglish(numStr[i]) + " ";
    }
    return result;
}

// --- GPSManagerクラス ---
GPSManager::GPSManager(SoftwareSerial& serial) : gpsSerial(serial) {}

void GPSManager::begin(long baudrate) {
    gpsSerial.begin(baudrate);
}

bool GPSManager::getGPS(float &lat, float &lng) {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }
    if (gps.location.isValid()) {
        lat = gps.location.lat();
        lng = gps.location.lng();
        return true;
    }
    return false;
}

// --- NetClientクラス ---
NetClient::NetClient() {}

void NetClient::begin(const String &ssid, const String &pass) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

String NetClient::queryAPI(float x, float y, const String &auth, const String &mode) {
      if (WiFi.status() != WL_CONNECTED) return "Wi-Fi not connected";

    // URLをパラメータから生成
    String url = "https://busguide_bot.otterstb-io.org/query?";
    url += "x=" + String(x, 6);
    url += "&y=" + String(y, 6);
    url += "&auth=" + auth;
    url += "&mode=" + mode;

    Serial.println("Request URL: " + url);

    HTTPClient http;
    http.begin(url);
    http.setTimeout(15000); // 15秒まで待つ
    int httpCode = http.GET();
    String payload = "";
    if (httpCode > 0) {
        payload = http.getString();
    }
    http.end();
    return payload;
}



/*
#include "library.hpp"
//ーーーーーーーーーーーーーーーーーーーwifiーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
NetClient::NetClient() {}

void NetClient::begin(const String &ssid, const String &pass) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
    }
}

String NetClient::queryAPI(float x, float y, const String &auth, const String &mode) {
  if (WiFi.status() != WL_CONNECTED) return "Wi-Fi not connected";

    // URLをパラメータから生成
    String url = "https://busguide_bot.otterstb-io.org/query?";
    url += "x=" + String(x, 6);
    url += "&y=" + String(y, 6);
    url += "&auth=" + auth;
    url += "&mode=" + mode;

    Serial.println("Request URL: " + url);

    HTTPClient http;
    http.begin(url);
    http.setTimeout(15000); // 15秒まで待つ
    int httpCode = http.GET();
    String payload = "";
    if (httpCode > 0) {
        payload = http.getString();
    }
    http.end();
    return payload;
}



//ーーーーーーーーーーーーーーーーーーーーーーーーーーーLSIーーーーーーーーーーーーーーーーーーーーーーーーーーー

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


//ーーーーーーーーーーーーーーーーーーーーーーーーーーーGPSーーーーーーーーーーーーーーーーーーーーーーーーーーー
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
    */
