#include <esp_wifi.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebSocketsClient.h>

WebSocketsClient wsc;

const char *ssid = "*****";
const char *pass = "*****";

#define SERVER  "192.168.1.15"
#define PORT    3000
#define URL     "/"

void websocketEvent(WStype_t type, uint8_t *data, size_t length){
  switch(type){
    case(WStype_CONNECTED):
      Serial.printf("connected to server\n");
      break;
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\n");
      break;
    case(WStype_TEXT):
      analogWrite(2, atoi((const char *)data));
      break;
  }
}

void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }

  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());

  wsc.begin(SERVER, PORT, URL);
  wsc.onEvent(websocketEvent);
  // try ever 1000 again if connection has failed
  wsc.setReconnectInterval(1000);
}

void loop(){
  wsc.loop();
}



