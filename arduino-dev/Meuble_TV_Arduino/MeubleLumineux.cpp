#include <Arduino.h>
#include "MeubleLumineux.h"

uint8_t cptRainbow;

CRGB leds[NB_BANDEAU][NUM_LEDS];

MeubleLumineux::MeubleLumineux(){
  //BAS   3-32
  //COTE1 33-48
  //HAUT  49-78
  //COTE2 0-2 79-91
  
  FastLED.addLeds<APA102, DATA_PIN_1, CLK_PIN_1, COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<APA102, DATA_PIN_2, CLK_PIN_2, COLOR_ORDER>(leds[1], NUM_LEDS);
 // FastLED.addLeds<APA102, DATA_PIN_3, CLK_PIN_3, COLOR_ORDER>(leds[2], NUM_LEDS);
 // FastLED.addLeds<APA102, DATA_PIN_4, CLK_PIN_4, COLOR_ORDER>(leds[3], NUM_LEDS);
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
  if (pos >= 0 && pos <= NB_BANDEAU) {
    for (uint8_t i=0; i < NUM_LEDS;i++) {
      leds[pos][i] = color;
    }
  }
}

void MeubleLumineux::setColor(CRGB color) {
  for (uint8_t j=0; j < NB_BANDEAU; j++) {
    for (uint8_t i=0; i < NUM_LEDS;i++) {
      leds[j][i] = color;
    }
  }
}

void MeubleLumineux::setTop(uint8_t  i, CRGB color) {
  if (i>=0 && i<30) {
    leds[0][78-i] = color;
  } else if (i<60) {
    leds[1][49+i-30] = color;
  } else if (i<90) {
  //  leds[2][49+i-60] = color;    
  } else if (i<120) {
  //  leds[3][49+i-90] = color;
  }
}

void MeubleLumineux::setBottom(uint8_t  i, CRGB color) {
  if (i>=0 && i<30) {
    leds[0][3+i] = color;
  } else if (i<60) {
    leds[1][32-i+30] = color;
  } else if (i<90) {
  //  leds[2][32-i+60] = color;    
  } else if (i<120) {
  //  leds[3][32-i+90] = color;
  }
}

void MeubleLumineux::setMiddle(uint8_t pos, uint8_t i, CRGB color) {
  //COTE1 33-48
  //COTE2 0-2 79-91
  switch (pos) {
    case 0:
      if (i<3) {
        leds[0][0+i] = color;
      } else {
        leds[0][91-i+3] = color;
      }
      break;
    case 30:
    case 1:
      leds[0][33+i] = color;
      break;
    case 31:
    case 2:
      leds[1][33+i] = color;
      break;
    case 60:
    case 3:
      if (i<3) {
        leds[1][0+i] = color;
      } else {
        leds[1][91-i+3] = color;
      }
      break;
    case 61:
    case 4:
    //  leds[2][33+i] = color;
      break;
    case 90:
    case 5:
      if (i<3) {
     //   leds[2][0+i] = color;
      } else {
      //  leds[2][91-i+3] = color;
      }
      break;
    case 91:
    case 6:
    //  leds[3][33+i] = color;
      break;
    case 120:
    case 7:
       if (i<3) {
      //  leds[3][0+i] = color;
      } else {
      //  leds[3][91-i+3] = color;
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
