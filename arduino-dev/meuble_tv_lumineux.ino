#include "MeubleLumineux.h"

MeubleLumineux meubleTV;

String message = "";
String messagePrecedent = "";
String commande = "";

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for (int i=0; i<=maxIndex && found<=index; i++) {
    if (data.charAt(i)==separator || i==maxIndex) {
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Serial.begin(9600);
   
  meubleTV = MeubleLumineux();
  
  //Sequence de démarrage
  meubleTV.clear();
  meubleTV.setBrightness(20);
  meubleTV.setColor(1,CRGB::White);
  meubleTV.setColor(2,CRGB::White);
  meubleTV.setColor(3,CRGB::White);
  meubleTV.setColor(4,CRGB::White);
  meubleTV.show();
  delay(3000);
  meubleTV.clear();
  meubleTV.setBrightness(255);
  meubleTV.show();
}

void loop() {
  //Reception du message
  if (Serial.available() > 0) {
	  message = Serial.readStringUntil('\n');
	  commande = getValue(message,';',0);
  }

  //Traitement des commandes Scenario
  if (commande == "rainbow") {
	meubleTV.rainbow();
	meubleTV.show();
  } else if (messagePrecedent != message) {
	//On Evite de retraiter une commande "statique"
	if (commande == "off") {
	  meubleTV.clear();
	  meubleTV.show();
    } else if (commande == "white") {
	  meubleTV.setColor(CRGB::White);
	  meubleTV.show();
    } else if (commande == "blue") {
	  meubleTV.setColor(CRGB::Blue);
	  meubleTV.show();
    } else if (commande == "red") {
	  meubleTV.setColor(CRGB::Red);
	  meubleTV.show();
    } else if (commande == "green") {
	  meubleTV.setColor(CRGB::Green);
	  meubleTV.show();
    } else if (commande == "color") {
	  int red = getValue(message,';',1).toInt();
	  int green = getValue(message,';',2).toInt();
	  int blue = getValue(message,';',3).toInt();
	  meubleTV.setColor(CRGB(red, green, blue));
	  meubleTV.show();
    } else if (commande == "show") {
	  meubleTV.show();
    } else if (commande == "clear") {
	  meubleTV.clear();
    } else if (commande == "setBrightness") {
	  int scale = getValue(message,';',1).toInt();
	  meubleTV.setBrightness(scale);
    } else if (commande == "setColor") {
	  uint8_t  pos = getValue(message,';',1).toInt();
	  int red = getValue(message,';',2).toInt();
	  int green = getValue(message,';',3).toInt();
	  int blue = getValue(message,';',4).toInt();
	  meubleTV.setColor(pos, CRGB(red, green, blue));
    } else if (commande == "setTop") {
	  uint8_t  pos = getValue(message,';',1).toInt();
	  int red = getValue(message,';',2).toInt();
	  int green = getValue(message,';',3).toInt();
	  int blue = getValue(message,';',4).toInt();
	  meubleTV.setTop(pos, CRGB(red, green, blue));
    } else if (commande == "setBottom") {
	  uint8_t  pos = getValue(message,';',1).toInt();
	  int red = getValue(message,';',2).toInt();
	  int green = getValue(message,';',3).toInt();
	  int blue = getValue(message,';',4).toInt();
	  meubleTV.setBottom(pos, CRGB(red, green, blue));
    } else if (commande == "setMiddle") {
	  uint8_t  pos = getValue(message,';',1).toInt();
	  uint8_t  i = getValue(message,';',2).toInt();
	  int red = getValue(message,';',3).toInt();
	  int green = getValue(message,';',4).toInt();
	  int blue = getValue(message,';',5).toInt();
	  meubleTV.setMiddle(pos, i, CRGB(red, green, blue));
    } else if (commande == "rainbow") {
	  meubleTV.rainbow();
    }
  }
  messagePrecedent = message;
}
