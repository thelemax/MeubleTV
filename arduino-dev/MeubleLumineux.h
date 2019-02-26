/*
 MeubleLumineux.h - 
 
 A pin is blinked automatically by one second intervals or by a specified interval
 Methods:
 
 MeubleLumineux_h() - Constructor. Avec les pins par defaut
 
*/
#ifndef MeubleLumineux_h
#define MeubleLumineux_h

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS    92 // Nombre de LEDS par RUBAN
#define LED_TYPE    APA102 //Type de LED
#define COLOR_ORDER BGR // Mode de couleur des LED

//Bandeau 1
#define DATA_PIN_1    12
#define CLK_PIN_1     13

//Bandeau 2
#define DATA_PIN_2    10
#define CLK_PIN_2     11

//Bandeau 3
#define DATA_PIN_3    8
#define CLK_PIN_3     9

//Bandeau 4
#define DATA_PIN_4    6
#define CLK_PIN_4     7

//Luminosité max
#define BRIGHTNESSMAX 64

//Nombre Vertical Max
#define MAX_VERTICAL 15

//Nombre Horizontal Max
#define MAX_HORIZONTAL 120

class MeubleLumineux
{
public:
  MeubleLumineux();
  void clear();
  void show();
  void setBrightness(uint8_t scale);
  void setColor(uint8_t  pos, CRGB color);
  void setTop(uint8_t  i, CRGB color);
  void setBottom(uint8_t  i, CRGB color);
  void setMiddle(uint8_t pos , uint8_t i, CRGB color);
  void rainbow();
private:
  uint8_t cptRainbow;
};
#endif