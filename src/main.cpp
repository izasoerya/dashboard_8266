#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Models.h"

TimerVar taskTimer1(5000);
TimerVar taskTimer2(2000);

WiFiClientSecure client;
String serverPath = "https://httpbin.org/post";

void httpPost() {
    client.setInsecure();
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client, serverPath.c_str());

        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");
      
        if (httpResponseCode>0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        }
        else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } 
    else {
        Serial.println("WiFi Disconnected");
    }
}

void connectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    connectToWiFi();
}

void loop() {
    // put your main code here, to run repeatedly:
    if (millis() > taskTimer1.currentTime) {
        httpPost();
        taskTimer1.currentTime += taskTimer1.interval;
    }
    if (millis() > taskTimer2.currentTime) {

        taskTimer2.currentTime += taskTimer2.interval;
    }
}
