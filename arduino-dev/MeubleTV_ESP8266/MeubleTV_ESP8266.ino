#define zzDEBUG

#ifdef DEBUG
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_PRINTLN2(x,y) Serial.println(x,y)
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINT2(x,y) Serial.print(x,y)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTLN2(x,y)
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINT2(x,y)
#endif 

#include "Arduino.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "chez_nous";
const char* password = "Nursse: Une fille moi!";
byte mac[6]; 
 
ESP8266WebServer server(80);
 
// Serving Hello world
void getHelloWord() {
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}

void getIndex() {
  String resp = "<!doctype html>";
  resp += "<html lang=\"fr\">";
  resp += "<head>";
  resp += "<meta charset=\"utf-8\">";
  resp += "<meta http-equiv=\"X-UA-Compatible\" content=\"chrome=1\">";
  resp += "<link rel=\"stylesheet\" href=\"https://raw.githubusercontent.com/bebraw/colorjoe/master/css/colorjoe.css\">";
  resp += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\">";
  resp += "<script src='https://raw.githubusercontent.com/bebraw/colorjoe/master/js/scale.fix.js'></script>";
  resp += "<script language=\"javascript\">";
  resp += "fixScale(document);main();function main(){var val=document.getElementById('rgbValue');var hVal=document.getElementById('hslaValue');";
  resp += "colorjoe.registerExtra('text',function(p,joe,o){e(p,o.text?o.text:'text');});function e(parent,text){var elem=document.createElement('div');elem.innerHTML=text;parent.appendChild(elem);}";
  resp += "colorjoe.rgb('rgbPicker').on('change',function(c){console.log(Math.round(c.red()*255)+';'+Math.round(c.green()*255)+';'+Math.round(c.blue()*255));const Http=new XMLHttpRequest();";
  resp += "const url='http://192.168.1.139:8080/api/color/'+Math.round(c.red()*255)+';'+Math.round(c.green()*255)+';'+Math.round(c.blue()*255);Http.open(\"GET\",url);Http.send();";
  resp += "Http.onreadystatechange=(e)=>{console.log(Http.responseText)}}).update();colorjoe.rgb('extraPicker','#113c38',['close','currentColor',['fields',{space:'RGB',limit:255,fix:2}],'hex','text',['text',{text:'param demo'}]]);";
  resp += "colorjoe.hsl('hslPicker','#113c38',['alpha','currentColor',['fields',{space:'HSLA',limit:100}],['fields',{space:'CMYKA',limit:100}],'hex']).on('change',function(c){hVal.innerHTML='Alpha: '+c.alpha().toFixed(2);}).update();";
  resp += "var cj=colorjoe.rgb('closeablePicker','red',['close','currentColor']);document.getElementById('showPicker').onclick=function(e){e.preventDefault();cj.show();};}";
  resp += "</script>";
  resp += "</head>";
  resp += "<body>";
  resp += "<div id=\"rgbPicker\"></div>";
   resp += "</body>";
  resp += "</html>";

  server.send(200, "text/html", resp);
}

void getOff() {
    sendInfoToArduino("OFF");
    server.send(200, "text/json", checkInfoFromArduino());
}

void getOn() {
    sendInfoToArduino("RAINBOW");
    server.send(200, "text/json", checkInfoFromArduino());
}

// Define routing
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
            F("Welcome to the REST Web Server"));
    });
    server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
    server.on(F("/api/off"), HTTP_GET, getOff);
    server.on(F("/api/on"), HTTP_GET, getOn);
    server.on(F("/index.html"), HTTP_GET, getIndex);
}
 
// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


String checkInfoFromArduino()
{
  bool StringReady;
  String jsonString;
 
  while (Serial.available()){
   jsonString=Serial.readString();
   StringReady = true;
  }
  if (StringReady){
    /*
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    if(!root.success()) {
      //Serial.println("parseObject() failed");
      return ;
    }
    return root["payload"];
    */

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);  

    if (error) {
      return "ERROR : "+jsonString + " - " + error.f_str();
    }
    
    return doc["payload"];
  }
  return "";
}

void sendInfoToArduino(String payload)
{
  /*
  DynamicJsonBuffer jbuffer;
  JsonObject& root = jbuffer.createObject();
  root["payload"] = command;
  root.printTo(Serial);
  Serial.println();
  */
   StaticJsonDocument<200> doc;
   doc["payload"] = payload;
   serializeJson(doc, Serial);
   Serial.println();
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINTLN(".");
  }
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("Connected to ");
  DEBUG_PRINTLN(ssid);
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN("WiFi Connected");

  
  WiFi.macAddress(mac);
  DEBUG_PRINT("MAC: ");
  DEBUG_PRINT2(mac[5],HEX);
  DEBUG_PRINT(":");
  DEBUG_PRINT2(mac[4],HEX);
  DEBUG_PRINT(":");
  DEBUG_PRINT2(mac[3],HEX);
  DEBUG_PRINT(":");
  DEBUG_PRINT2(mac[2],HEX);
  DEBUG_PRINT(":");
  DEBUG_PRINT2(mac[1],HEX);
  DEBUG_PRINT(":");
  DEBUG_PRINTLN2(mac[0],HEX);
  DEBUG_PRINTLN("");
 

 
  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    DEBUG_PRINTLN("MDNS responder started");
  }
 
  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  DEBUG_PRINTLN("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
}
