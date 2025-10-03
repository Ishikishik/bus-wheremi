#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// -----------------------------
// ソフトウェアUART
// -----------------------------
SoftwareSerial gpsSerial(5, 6);   // GPSモジュール用
SoftwareSerial lsiSerial(0, 1);   // LSI音声合成用

TinyGPSPlus gps;

// -----------------------------
// LSI用関数
// -----------------------------
void lsiBegin(long baudrate = 9600) {
  lsiSerial.begin(baudrate);
}

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

void hatuonn(String msg) {
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

// -----------------------------
// 数字を英語に変換
// -----------------------------
String numToEnglish(char c) {
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

String convertNumberString(String numStr) {
  String result = "";
  for (int i = 0; i < numStr.length(); i++) {
    result += numToEnglish(numStr[i]);
  }
  return result;
}

// -----------------------------
// Arduino setup/loop
// -----------------------------
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  lsiBegin(9600);
  Serial.println("GPS + LSI test start");
}

void loop() {
  // GPSデータ受信
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // 新しい位置情報があれば発声
  if (gps.location.isUpdated()) {
    String latitudeStr = String(gps.location.lat(), 6);
    String longitudeStr = String(gps.location.lng(), 6);

    String latitudeSpeech = "idoha " + convertNumberString(latitudeStr);
    String longitudeSpeech = "keidoha " + convertNumberString(longitudeStr);

    hatuonn(latitudeSpeech + "/" + longitudeSpeech);  // /で区切ると順番に発声

    // デバッグ
    Serial.println(latitudeSpeech);
    Serial.println(longitudeSpeech);

    delay(1000); // 発声間隔
  }
}

/*
#include <SoftwareSerial.h>

// SoftwareSerialインスタンスを作成（ピン番号は環境に合わせて設定してください）
SoftwareSerial lsiSerial(0, 1);    // LSI用
SoftwareSerial gpsSerial(5, 6);    // GPS用

String gpsData = "";    // GPSから受信した生データを保持
bool gpsReady = false;  // 新しいGPSデータがあるか

// -----------------------------
// 数字を英語に変換する関数
// -----------------------------
String numToEnglish(char c) {
  switch (c) {
    case '0': return "zero";
    case '1': return "ichi";
    case '2': return "ni";
    case '3': return "sann";
    case '4': return "yonn";
    case '5': return "go";
    case '6': return "roku";
    case '7': return "nana";
    case '8': return "hachi";
    case '9': return "ku";
    default: return "";
  }
}

// -----------------------------
// GPS文字列から数字だけを抽出
// -----------------------------
String extractNumbers(String msg) {
  String result = "";
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i];
    if (c >= '0' && c <= '9') {
      result += numToEnglish(c) + " ";
    }
  }
  return result;
}

// -----------------------------
// 文字列をLSIに送信して発声
// -----------------------------
void hatuonn(String msg) {
  String segment = "";
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i];
    if (c == ' ') {
      sendToLSI(segment);
      segment = "";
    } else {
      segment += c;
    }
  }
  if (segment.length() > 0) sendToLSI(segment);
}

void sendToLSI(String s) {
  lsiSerial.print(s);
  lsiSerial.print("\r");

  // 発声準備完了を待つ
  while (true) {
    if (lsiSerial.available() > 0) {
      char c = lsiSerial.read();
      if (c == '>') break;
    }
    delay(5);
  }
}

// -----------------------------
// setup
// -----------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("GPS->LSI Test Start");

  lsiSerial.begin(9600);
  gpsSerial.begin(9600);
}

// -----------------------------
// GPS受信処理
// -----------------------------
void readGPS() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    gpsData += c;

    if (c == '\n') { // 1行受信したら
      gpsReady = true;
    }
  }
}

// -----------------------------
// GPSデータをLSIで読み上げ
// -----------------------------
void sendGPS2LSI() {
  if (gpsReady) {
    String numbersOnly = extractNumbers(gpsData);
    if (numbersOnly.length() > 0) {
      hatuonn(numbersOnly);
    }
    gpsReady = false;
    gpsData = "";
  }
}

// -----------------------------
// loop
// -----------------------------
void loop() {
  readGPS();
  sendGPS2LSI();
  delay(5000);
}

*/

/*
#include <SoftwareSerial.h>

// LSI 用 UART
SoftwareSerial mySerial(0, 1);

// GPS 用 UART
SoftwareSerial gpsSerial(5, 6);

// 関数プロトタイプ
String numToEnglish(char c);
String extractNumbers(String str);
void hatuonn(String msg);
void sendToLSI(String s);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("SoftwareSerial LSI & GPS start");

  mySerial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  if (gpsSerial.available()) {
    String gpsData = gpsSerial.readStringUntil('\n');
    String numbersOnly = extractNumbers(gpsData);
    hatuonn(numbersOnly);
  }
  delay(3000);
}

// 数字だけを抽出
String extractNumbers(String str) {
  String result = "";
  for (int i = 0; i < str.length(); i++) {
    char c = str[i];
    if (c >= '0' && c <= '9') {
      result += numToEnglish(c);
      result += " ";
    }
  }
  return result;
}

// 数字を英語文字列に変換
String numToEnglish(char c) {
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

// LSI で文字列を読み上げ
void hatuonn(String msg) {
  String segment = "";
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i];
    if (c == ' ') {
      sendToLSI(segment);
      segment = "";
    } else {
      segment += c;
    }
  }
  if (segment.length() > 0) sendToLSI(segment);
}

// LSI に送信
void sendToLSI(String s) {
  mySerial.print(s);
  mySerial.print("\r");
  while (true) {
    if (mySerial.available() > 0) {
      char c = mySerial.read();
      if (c == '>') break;
    }
    delay(5);
  }
}
*/