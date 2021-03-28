/**************
 *  RobotDyn
 *  Dimmer Library
 *  **************
 * 
 *  The following sketch is meant to turn the lamp on/off with use of a button.
 *  pinMode(14, INPUT); button is connected to 14th pin 
 *  void loop()  ON/OFF button evaluator of dimmer in dim4.setState(ON/OFF);
 *    
 * 
  *  ---------------------- OUTPUT & INPUT Pin table ---------------------
 *  +---------------+-------------------------+-------------------------+
 *  |   Board       | INPUT Pin               | OUTPUT Pin              |
 *  |               | Zero-Cross              |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Lenardo       | D7 (NOT CHANGABLE)      | D0-D6, D8-D13           |
 *  +---------------+-------------------------+-------------------------+
 *  | Mega          | D2 (NOT CHANGABLE)      | D0-D1, D3-D70           |
 *  +---------------+-------------------------+-------------------------+
 *  | Uno           | D2 (NOT CHANGABLE)      | D0-D1, D3-D20           |
 *  +---------------+-------------------------+-------------------------+
 *  | ESP8266       | D1(IO5),    D2(IO4),    | D0(IO16),   D1(IO5),    |
 *  |               | D5(IO14),   D6(IO12),   | D2(IO4),    D5(IO14),   |
 *  |               | D7(IO13),   D8(IO15),   | D6(IO12),   D7(IO13),   |
 *  |               |                         | D8(IO15)                |
 *  +---------------+-------------------------+-------------------------+
 *  | ESP32         | 4(GPI36),   6(GPI34),   | 8(GPO32),   9(GP033),   |
 *  |               | 5(GPI39),   7(GPI35),   | 10(GPIO25), 11(GPIO26), |
 *  |               | 8(GPO32),   9(GP033),   | 12(GPIO27), 13(GPIO14), |
 *  |               | 10(GPI025), 11(GPIO26), | 14(GPIO12), 16(GPIO13), |
 *  |               | 12(GPIO27), 13(GPIO14), | 23(GPIO15), 24(GPIO2),  |
 *  |               | 14(GPIO12), 16(GPIO13), | 25(GPIO0),  26(GPIO4),  |
 *  |               | 21(GPIO7),  23(GPIO15), | 27(GPIO16), 28(GPIO17), |
 *  |               | 24(GPIO2),  25(GPIO0),  | 29(GPIO5),  30(GPIO18), |
 *  |               | 26(GPIO4),  27(GPIO16), | 31(GPIO19), 33(GPIO21), |
 *  |               | 28(GPIO17), 29(GPIO5),  | 34(GPIO3),  35(GPIO1),  |
 *  |               | 30(GPIO18), 31(GPIO19), | 36(GPIO22), 37(GPIO23), |
 *  |               | 33(GPIO21), 35(GPIO1),  |                         |
 *  |               | 36(GPIO22), 37(GPIO23), |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Arduino M0    | D7 (NOT CHANGABLE)      | D0-D6, D8-D13           |
 *  | Arduino Zero  |                         |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Arduino Due   | D0-D53                  | D0-D53                  |
 *  +---------------+-------------------------+-------------------------+
 *  | STM32         | PA0-PA15,PB0-PB15       | PA0-PA15,PB0-PB15       |
 *  | Black Pill    | PC13-PC15               | PC13-PC15               |
 *  | BluePill      |                         |                         |
 *  | Etc...        |                         |                         |
 *  +---------------+-------------------------+-------------------------+
 */



#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <RBDdimmer.h>//

//#define USE_SERIAL  SerialUSB //Serial for boards whith USB serial port

#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"
#define FIREBASE_AUTH "FlowlqsCBeqdvMJxdgxbmEyeiWi2CbSX3KStpCUW"
#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD "cookiebox!1"

dimmerLamp dimmer(12, 5); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero




void setup() {
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  dimmer.setPower(50);


   Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("와이파이에 연결");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("IP에 연결");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //데이터 버퍼 크기 설정
  firebaseData.setBSSLBufferSize(1024, 1024);

  //대용량 데이터 작업시 HTTP 응답하는 버퍼 크기 설정.
  firebaseData.setResponseSize(1024);

  //데이터 베이스 읽기 시간 제한을 1분으로 설정 (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);  //1초 *60 = 1분이란 설정

  //tiny(가장 작은), small(작은), medium(중간), large and unlimited(무제한).
  //크기및 쓰기 제한 시간 소형 1초
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Firebase.setString(firebaseData, "Room_3/board_2/Fan_1", "FA02");
  dht.begin();
}

void loop() {
    dimmer.setState(ON); //name.setState(ON/OFF);  
    dimmer.setState(OFF); //name.setState(ON/OFF);
}




