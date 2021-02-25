/*
 MeubleLumineux.h - 
 
 A pin is blinked automatically by one second intervals or by a specified interval
 Methods:
 
 MeubleLumineux_h() - Constructor. Avec les pins par defaut
 
*/
#ifndef MeubleLumineux_h
#define MeubleLumineux_h

#define FASTLED_INTERNAL // Eliminates a compiler warning

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS    92 // Nombre de LEDS par RUBAN
#define LED_TYPE    APA102 //Type de LED
#define COLOR_ORDER BGR // Mode de couleur des LED

#define NB_BANDEAU     2

//Bandeau 1
#define CLK_PIN_1     11
#define DATA_PIN_1    10

//Bandeau 2
#define CLK_PIN_2     9
#define DATA_PIN_2    8

//Bandeau 3
#define CLK_PIN_3     7
#define DATA_PIN_3    6

//Bandeau 4
#define CLK_PIN_4     5
#define DATA_PIN_4    4

//Luminosit� max
#define BRIGHTNESSMAX 64

//Nombre Vertical Max
#define MAX_VERTICAL 15

//Nombre Horizontal Max
#define MAX_HORIZONTAL 120

class MeubleLumineux {
public:
  MeubleLumineux();
  void clear();
  void show();
  void setBrightness(uint8_t scale);
  void setColor(uint8_t  pos, CRGB color);
  void setColor(CRGB color);
  void setTop(uint8_t  i, CRGB color);
  void setBottom(uint8_t  i, CRGB color);
  void setMiddle(uint8_t pos , uint8_t i, CRGB color);
  void rainbow();
private:
  uint8_t cptRainbow;
};
#endif
