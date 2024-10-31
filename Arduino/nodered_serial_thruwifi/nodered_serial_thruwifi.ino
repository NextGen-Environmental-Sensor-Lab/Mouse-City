/*
Read Software serial and send it through Wifi to Node-red
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <SoftwareSerial.h>

const char *ssid = "NGENSMOTO";
const char *password = "N63n5adm1n";

SoftwareSerial swSerial(D5, D6);  // rx tx rsoftserial bcause esp8266 Serial1 only transmits :(

char StrContains(char *, char *);
int doPOST(HTTPClient &, String);

void setup() {
  Serial.begin(57600);
  delay(8000);
  Serial.println(__FILE__);

  swSerial.begin(9600);  //Initialize software serial with 2400 baud for '205 Ozone Monitor'

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print(" connected!\n");
}

void loop() {
  char rs232Buffer[128] = "";
  int indx = 0;
  char tmpr = 0x00;
  String payload;

  if ((WiFi.status() == WL_CONNECTED)) {
    // READ FROM sw-SERIAL
    while (swSerial.available() > 0) {  // if data from rs232 available get it
      tmpr = swSerial.read();
      //Serial.println(tmpr, HEX);
      rs232Buffer[indx++] = tmpr;
      delay(10);
    }

    if (tmpr == 0x0A || tmpr == 0x0D || tmpr == 0x03) {  // if end of line from rs232 send to Google Sheets (CR, LF or EOT)

      if (rs232Buffer[indx - 2] == 0x0A || rs232Buffer[indx - 2] == 0x0D || rs232Buffer[indx - 2] == 0x03)
        rs232Buffer[indx - 2] = 0;  // there may be two terminating chars...
      else
        rs232Buffer[indx - 1] = 0;  // terminate as c string with a zero

      if (StrContains(rs232Buffer, "ON"))
        digitalWrite(LED_BUILTIN, LOW);
      if (StrContains(rs232Buffer, "OFF"))
        digitalWrite(LED_BUILTIN, HIGH);

      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

      // Ignore SSL certificate validation
      client->setInsecure();

      HTTPClient https;

      String payload_prefix = "{\"command\": \"appendRow\", \"sheet_name\": \"Sheet1\", \"values\": \"";
      String payload_suffix = "\"}";
      String payload = payload_prefix + String(rs232Buffer) + payload_suffix;
      Serial.printf("payload: %s\n",payload.c_str());

      if (https.begin(*client, "https://ngens.environmentalcrossroads.net/nodered/hello-raw")) {  // HTTPS
        doPOST(https, payload);
        https.end();
      } else {
        Serial.printf("HTTPS for POST Unable to connect\n");
      }
    }
  }
}


// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind) {
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);

  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    } else {
      found = 0;
    }
    index++;
  }
  return 0;
}

//
int doPOST(HTTPClient &https, String jsonData) {

  https.addHeader("Content-Type", "application/json");
  //https.addHeader("Content-Type", "text/plain");
  https.setAuthorization("ngensadmin", "N63n5adm1n");
  int httpsResponseCode = https.POST(jsonData);
  Serial.printf("HTTP POST response code: %d\n", httpsResponseCode);

  return httpsResponseCode;
}
