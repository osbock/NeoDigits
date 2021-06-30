#include "NeoDigit.h"
#define LEDS_PER_SEGMENT 3
#define NUM_LEDS LEDS_PER_SEGMENT * 7

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
NeoDigit Digit1(leds1,LEDS_PER_SEGMENT);
NeoDigit Digit2(leds2,LEDS_PER_SEGMENT);
// FastLED stuff
#define DATA_PIN1 2
#define DATA_PIN2 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN1,COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN2,COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t counter = 0;
void loop() {

  fill_solid(leds1,NUM_LEDS,CRGB::Magenta);
  fill_solid(leds2,NUM_LEDS,CRGB::Magenta);
  if (counter/10 > 0)
    Digit1.display(counter/10);
  else
    fill_solid(leds1,NUM_LEDS,CRGB::Black);
  Digit2.display(counter-(counter/10)*10);
  //Digit1.display(counter,gHue);
  FastLED.show();
  // do some periodic updates
  EVERY_N_MILLISECONDS( 10 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 200 ) { counter++; if (counter>99) counter=0;}

}
