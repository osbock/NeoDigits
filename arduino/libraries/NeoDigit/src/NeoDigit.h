#ifndef NeoDigit_h
#define NeoDigit_h
#include "Arduino.h"
#include <FastLED.h>
class NeoDigit
{
 public:
  NeoDigit(CRGB *leds,int leds_per_segment);
  void display(int value, int color);
 protected:
  int _leds_per_segment;
  CRGB *_leds;
  static int allSegments[10][7];

};
#endif
