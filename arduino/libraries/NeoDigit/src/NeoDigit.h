#ifndef NeoDigit_h
#define NeoDigit_h
#include "Arduino.h"
#include <FastLED.h>

#define COLOR_RAINBOW -1
class NeoDigit
{
 public:
  NeoDigit(CRGB *leds,int leds_per_segment);
  void display(int value, int color);
  void display(int value); //inverted masked display
 protected:
  int _leds_per_segment;
  CRGB *_leds;
  static int allSegments[10][7];
  static int maskSegments[10][7];

};
#endif
