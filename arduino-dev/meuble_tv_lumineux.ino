#include "MeubleLumineux.h"

MeubleLumineux meubleTV;

String message = "";
String ligneCommandePrecedente = "";
String ligneCommande = "";
int indexCommande = 0;

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

String getLigneCommande(String message, int index) {
  return getValue(message,'|',index);
}

String getCommande(String ligneCommande) {
  return getValue(ligneCommande,';',0);
}

String getString(String ligneCommande, int index) {
  return getValue(ligneCommande,';',index);
}

int getInt(String ligneCommande, int index) {
  return getValue(ligneCommande,';',index).toInt();
}

CRGB getCRGB(String ligneCommande, int index) {
	int red = getInt(ligneCommande, index);
    int green = getInt(ligneCommande, index + 1);
    int blue = getInt(ligneCommande, index + 2);
    return CRGB(red, green, blue);
}

void traiterCommande(String ligneCommande) {
  String commande = getCommande(ligneCommande);
  if (ligneCommandePrecedente == ligneCommande) {
    return;  
  }
  ligneCommandePrecedente = ligneCommande;
  //On Evite de retraiter une commande "statique"
  if (commande == "RAINBOW") {
    meubleTV.rainbow();
    meubleTV.show();
  } else if (commande == "SLEEP") {
    delay(getInt(ligneCommande, 1));
  } else if (commande == "LOOP") {
	indexCommande = 0;
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
    meubleTV.setColor(getCRGB(ligneCommande, 1));
    meubleTV.show();
  } else if (commande == "SHOW") {
    meubleTV.show();
  } else if (commande == "CLEAR") {
    meubleTV.clear();
  } else if (commande == "BRIGHT") {
    meubleTV.setBrightness( getInt(ligneCommande, 1));
  } else if (commande == "COLORP") {
    meubleTV.setColor(getInt(ligneCommande, 1), getCRGB(ligneCommande, 2));
  } else if (commande == "TOP") {
    meubleTV.setTop(getInt(ligneCommande, 1), getCRGB(ligneCommande, 2));
  } else if (commande == "BOTTOM") {
    meubleTV.setBottom(getInt(ligneCommande, 1), getCRGB(ligneCommande, 2));
  } else if (commande == "MIDDLE") {
    meubleTV.setMiddle(getInt(ligneCommande, 1), getInt(ligneCommande, 2), getCRGB(ligneCommande, 3));
  }
}

void setup() {
  Serial.begin(9600);
   
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
}

void loop() {
  //Reception du message
  if (Serial.available() > 0) {
    message = Serial.readStringUntil('\n');
	indexCommande = 0;
  }
  ligneCommande = getLigneCommande(message, indexCommande);
		
  if (ligneCommande != "") {
	indexCommande++;
	traiterCommande(ligneCommande);
  }
}
