#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>


unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("ssid", "password");

  for (int i = 0; i < 20 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() - previousMillis >= 3 * 1000) {
    previousMillis = millis();

    Serial.println(".");

    subirDatos();
  }
}

void subirDatos() {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  String url = "https://docs.google.com/forms/d/e/1FAIpQLSe3qJO3OatfA6ANZAVtWxNX78XdFuopBXlju0yoyHgT3_jabg/formResponse?";
  url += "&entry.950923689=";
  url += String(millis()/1000);

  url += "&entry.186011706=";
  url += String(WiFi.RSSI());

  url += "&entry.1322507513=";
  url += WiFi.SSID();

  Serial.println(url);


  if (http.begin(client, url)) {
    int httpCode = http.GET();

    Serial.println(httpCode);  //200 => ok
  }
}
