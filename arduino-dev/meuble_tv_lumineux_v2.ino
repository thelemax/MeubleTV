#include "MeubleLumineux.h"
#include "Commande.h"
#include <SoftwareSerial.h>


#define RX_PIN 2
#define TX_PIN 3

#define LED_PIN 13

#define FIRST_CHAR '>'
#define LAST_CHAR '$'

MeubleLumineux meubleTV;

String donneesRecues = "";
String message = ""; 
String messagePrecedent = "";

// mets en place un nouveau port série
SoftwareSerial mySerial =  SoftwareSerial(RX_PIN, TX_PIN);

CommandeManager cmd = new CommandeManager(meubleTV);
cmd.addCommande(new Off());
cmd.addCommande(new S());
  
void setup() {
  // définition du modes des broches pour tx, rx:
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
   
  // régler le débit de données pour le port SoftwareSerial
  mySerial.begin(9600);
   
  pinMode(LED_PIN, OUTPUT);
  meubleTV = MeubleLumineux();
  meubleTV.clear();
  meubleTV.setBrightness(50);
  meubleTV.setColor(1,CRGB::White);
  meubleTV.setColor(2,CRGB::White);
  meubleTV.setColor(3,CRGB::White);
  meubleTV.setColor(4,CRGB::White);
  meubleTV.show();
  delay(5000);
  meubleTV.clear();
  meubleTV.show();
  
  mySerial.println("ARDUINO SETUP OK");
}

boolean isCommand = false;

void loop() {
  if (mySerial.available() > 0) {
    char caractere = mySerial.read();
    if (caractere == FIRST_CHAR) {
      isCommand = true;
    } else if (isCommand) {
      if (caractere == LAST_CHAR) {
        message = donneesRecues;
        mySerial.println(message);
        donneesRecues = "";
        isCommand = false;
      } else {
        donneesRecues += caractere;
      }
    }
  }

  cmd.analyserCommande(message, messagePrecedent == message);
  messagePrecedent = message;
/*  
  
 if (message == "S1") {
    meubleTV.rainbow();
    meubleTV.show();
  } else if (message == "S2" && messagePrecedent != message) {
    meubleTV.setColor(1,CRGB::White);
    meubleTV.setColor(2,CRGB::White);
    meubleTV.setColor(3,CRGB::White);
    meubleTV.setColor(4,CRGB::White);
    meubleTV.show();
  } else if (message == "S3" && messagePrecedent != message) {
    meubleTV.setColor(1,CRGB::Blue);
    meubleTV.setColor(2,CRGB::Blue);
    meubleTV.setColor(3,CRGB::Blue);
    meubleTV.setColor(4,CRGB::Blue);
    meubleTV.show();
  } else if (message == "S4" && messagePrecedent != message) {
    meubleTV.setColor(1,CRGB::Red);
    meubleTV.setColor(2,CRGB::Red);
    meubleTV.setColor(3,CRGB::Red);
    meubleTV.setColor(4,CRGB::Red);
    meubleTV.show();
  } else if (message == "S5" && messagePrecedent != message) {
    meubleTV.setColor(1,CRGB::Green);
    meubleTV.setColor(2,CRGB::Green);
    meubleTV.setColor(3,CRGB::Green);
    meubleTV.setColor(4,CRGB::Green);
    meubleTV.show();
  } else if (message == "OFF" && messagePrecedent != message) {
    meubleTV.clear();
    meubleTV.show();
  }
  */

  delay(10);
}
