#include <ArduinoJson.h>
#include "MeubleLumineux.h"

MeubleLumineux meubleTV;

CRGB getRGB(DynamicJsonDocument doc) {
  return CRGB(doc["color"][0], doc["color"][1], doc["color"][2]);
}

String commandePrecedente = "";
String traiterCommande(DynamicJsonDocument doc) {
  String commande = doc["payload"];
  if (commandePrecedente == commande) {
    return "NoChange : " + commande;
  }
  commandePrecedente = commande;
  //On Evite de retraiter une commande "statique"
  if (commande == "RAINBOW") {
    meubleTV.rainbow();
    meubleTV.show();
  } else if (commande == "OFF") {
    meubleTV.clear();
    meubleTV.show();
  } else if (commande == "WHITE") {
    meubleTV.setColor(CRGB::White);
    meubleTV.show();
  } else if (commande == "BLUE") {
    meubleTV.setColor(CRGB::Blue);
    meubleTV.show();
  } else if (commande == "RED") {
    meubleTV.setColor(CRGB::Red);
    meubleTV.show();
  } else if (commande == "GREEN") {
    meubleTV.setColor(CRGB::Green);
    meubleTV.show();
  } else if (commande == "MAGENTA") {
    meubleTV.setColor(CRGB::Fuchsia);
    meubleTV.show();
  } else if (commande == "CYAN") {
    meubleTV.setColor(CRGB::Cyan);
    meubleTV.show();
  } else if (commande == "YELLOW") {
    meubleTV.setColor(CRGB::Yellow);
    meubleTV.show();
  } else if (commande == "GRAY") {
    meubleTV.setColor(CRGB::Gray);
    meubleTV.show();
  } else if (commande == "PINK") {
    meubleTV.setColor(CRGB::HotPink);
    meubleTV.show();
  } else if (commande == "PURPLE") {
    meubleTV.setColor(CRGB::Purple);
    meubleTV.show();
  } else if (commande == "ORANGE") {
    meubleTV.setColor(CRGB::OrangeRed);
    meubleTV.show();
  } else if (commande == "COLOR") {
    meubleTV.setColor(getRGB(doc));
    meubleTV.show();
    /*
  } else if (commande == "SHOW") {
    meubleTV.show();
  } else if (commande == "CLEAR") {
    meubleTV.clear();
  } else if (commande == "BRIGHT") {
    meubleTV.setBrightness(doc["brightness"]);
   
  } else if (commande == "COLORP") {
    meubleTV.setColor(doc["pos"], getRGB(doc));
  } else if (commande == "TOP") {
    meubleTV.setTop(doc["pos"], getRGB(doc));
  } else if (commande == "BOTTOM") {
    meubleTV.setBottom(doc["pos"], getRGB(doc));
  } else if (commande == "MIDDLE") {
    meubleTV.setMiddle(doc["pos"][0], doc["pos"][1], getRGB(doc));
  */
  } else {
    return "Unknown : " + commande;
  }
  return "OK :" + commande;
}

void setup() {
  meubleTV = MeubleLumineux();
  
  //Sequence de démarrage
  meubleTV.clear();
  meubleTV.setBrightness(1);
  meubleTV.setColor(CRGB::Blue);
  meubleTV.show();
  delay(3000);
  meubleTV.clear();
  meubleTV.setBrightness(255);
  meubleTV.show();

  Serial.begin(115200);
}

bool messageReady = false;
void loop() {
  String message = "";
  while (Serial.available()) {
    message = Serial.readString();
    messageReady = true;
  }    
  if (messageReady) {
    DynamicJsonDocument doc(64);
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
      Serial.print(F("deserializeJson failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }
    if (doc["type"] == "request") {
      doc["type"] = "response";
      doc["payload"] = traiterCommande(doc);
      serializeJson(doc, Serial);
    }
    messageReady = false;
  }
}
