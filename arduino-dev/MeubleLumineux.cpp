#include <Arduino.h>
#include "MeubleLumineux.h"

uint8_t cptRainbow;
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
  
MeubleLumineux::MeubleLumineux(){
  //BAS   3-32
  //COTE1 33-48
  //HAUT  49-78
  //COTE2 0-2 79-91
  FastLED.addLeds<APA102, DATA_PIN_1, CLK_PIN_1, COLOR_ORDER>(leds1, NUM_LEDS);
  FastLED.addLeds<APA102, DATA_PIN_2, CLK_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS);
  FastLED.addLeds<APA102, DATA_PIN_3, CLK_PIN_3, COLOR_ORDER>(leds3, NUM_LEDS);
  FastLED.addLeds<APA102, DATA_PIN_4, CLK_PIN_4, COLOR_ORDER>(leds4, NUM_LEDS);
}

void MeubleLumineux::clear() {
  FastLED.clear(true);
}
void MeubleLumineux::setBrightness(uint8_t scale) {
  FastLED.setBrightness(scale);
}
void MeubleLumineux::show() {
  FastLED.show();
}
void MeubleLumineux::setColor(uint8_t pos, CRGB color) {
  switch(pos) {
    case 1:
      for (uint8_t i=0; i < NUM_LEDS;i++) {
        leds1[i] = color;
      }
      break;
    case 2:
      for (uint8_t i=0; i < NUM_LEDS;i++) {
        leds2[i] = color;
      }
      break;
    case 3:
      for (uint8_t i=0; i < NUM_LEDS;i++) {
        leds3[i] = color;
      }
      break;
    case 4:
      for (uint8_t i=0; i < NUM_LEDS;i++) {
        leds4[i] = color;
      }
      break;
    default:
      break;
  }
}
void MeubleLumineux::setTop(uint8_t  i, CRGB color) {
  if (i>=0 && i<30) {
    leds1[78-i] = color;
  } else if (i<60) {
    leds2[49+i-30] = color;
  } else if (i<90) {
    leds3[49+i-60] = color;    
  } else if (i<120) {
    leds4[49+i-90] = color;
  }
}
void MeubleLumineux::setBottom(uint8_t  i, CRGB color) {
  if (i>=0 && i<30) {
    leds1[3+i] = color;
  } else if (i<60) {
    leds2[32-i+30] = color;
  } else if (i<90) {
    leds3[32-i+60] = color;    
  } else if (i<120) {
    leds4[32-i+90] = color;
  }
}
void MeubleLumineux::setMiddle(uint8_t pos, uint8_t i, CRGB color) {
  //COTE1 33-48
  //COTE2 0-2 79-91
  switch (pos) {
    case 0:
      if (i<3) {
        leds1[0+i] = color;
      } else {
        leds1[91-i+3] = color;
      }
      break;
    case 30:
    case 1:
      leds1[33+i] = color;
      break;
    case 31:
    case 2:
      leds2[33+i] = color;
      break;
    case 60:
    case 3:
      if (i<3) {
        leds2[0+i] = color;
      } else {
        leds2[91-i+3] = color;
      }
      break;
    case 61:
    case 4:
      leds3[33+i] = color;
      break;
    case 90:
    case 5:
      if (i<3) {
        leds3[0+i] = color;
      } else {
        leds3[91-i+3] = color;
      }
      break;
    case 91:
    case 6:
      leds4[33+i] = color;
      break;
    case 120:
    case 7:
       if (i<3) {
        leds4[0+i] = color;
      } else {
        leds4[91-i+3] = color;
      }
      break;
    default:
      break;
  }
}
void MeubleLumineux::rainbow() {
  for (uint8_t i = 0; i <= MAX_HORIZONTAL; i++) {
   setTop(i,CHSV(i+cptRainbow,255,255));
   setBottom(i,CHSV(i+cptRainbow,255,255));
   for (uint8_t j = 0; j <= MAX_VERTICAL; j++) {
     setMiddle(i, j, CHSV(i+cptRainbow,255,255));
   }
  }
  cptRainbow++;
  if (cptRainbow >= 255) {
    cptRainbow = 0;
  }
}