#include <SoftwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secret.hpp"

// ソフトウェアUART
SoftwareSerial lsiSerial(6, 5);   // LSI音声合成用

void connectWiFi() {
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

// LSI用関数
void lsiBegin(long baudrate = 9600) { lsiSerial.begin(baudrate); }

void sendToLSI(String s) {
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

// 長文も途切れず発声させる関数
extern SoftwareSerial lsiSerial;

void hatuonn(String text) {
    // シリアルバッファをクリア
    while (lsiSerial.available() > 0) lsiSerial.read();

    const int MAX_CHUNK = 120;     // 安全マージンを持たせて128byte未満
    const int INTERVAL_MS = 40;    // チャンク送信間隔
    int start = 0;

    // 先頭に空白を追加（LSI が '/' 開始を正しく認識しない場合用）
    text = " " + text;

    while (start < text.length()) {
        int end = start + MAX_CHUNK;
        if (end > text.length()) end = text.length();
        String chunk = text.substring(start, end);

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


// APIリクエスト
String queryAPI(float x, float y, String auth, String mode) {
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

// -----------------------------
void setup() {
    Serial.begin(115200);
    lsiBegin(9600);
    connectWiFi();
}

void loop() {
    String response = queryAPI(35.656, 139.543, AUTH, "roma");
    hatuonn(response);
    delay(5000);
  // String longText = "/genzaichiha/choufushi/meibutsuha/jindaijisobadegozaimasu.";
   // hatuonn(longText);

}
