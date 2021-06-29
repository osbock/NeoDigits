#include "NeoDigit.h"
#define LEDS_PER_SEGMENT 3
#define NUM_LEDS LEDS_PER_SEGMENT * 7

CRGB leds1[NUM_LEDS];
NeoDigit Digit1(leds1,LEDS_PER_SEGMENT);
// FastLED stuff
#define DATA_PIN A2
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t counter = 0;
void loop() {

  Digit1.display(counter,gHue);
  FastLED.show();
  // do some periodic updates
  EVERY_N_MILLISECONDS( 10 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 1000 ) { counter++; if (counter>9) counter=0;}

}
