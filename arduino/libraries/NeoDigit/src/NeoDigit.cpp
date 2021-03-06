#include "Arduino.h"
#include "NeoDigit.h"



// digit setup
#define LEDS_PER_SEGMENT 3
/*      Segment indices
 *            3
 *           ---
 *        4 |   |  2
 *           -6-   
 *        5 |   |  1
 *           ---
 *            0
 */

static int NeoDigit::allSegments[10][7] = {
  {0,1,2,3,4,5,-1}, //0
  {1,2,-1,-1,-1,-1,-1},//1
  {0,5,6,2,3,-1,-1},   //2
  {3,2,6,1,0,-1,-1},   //3
  {4,6,2,1,-1,-1,-1},  //4
  {3,4,6,1,0,-1,-1},   //5
  {3,4,5,6,0,1,-1},   //6
  {3,2,1,-1,-1,-1,-1}, //7
  {0,1,2,3,4,5,6},     //8
  {6,4,3,2,1,-1,-1}    //9
};
static int NeoDigit::maskSegments[10][7] = {
  {6,-1,-1,-1,-1,-1,-1}, //0
  {3,4,6,5,0,-1,-1},//1
  {4,1,-1,-1,-1,-1,-1},   //2
  {4,5,-1,-1,-1,-1,-1},   //3
  {3,5,0,-1,-1,-1,-1},  //4
  {5,2,-1,-1,-1,-1,-1},   //5
  {2,-1,-1,-1,-1,-1,-1},   //6
  {4,6,5,0,-1,-1,-1}, //7
  {-1,-1,-1,-1,-1,-1,-1},     //8
  {5,0,-1,-1,-1,-1,-1}    //9
};

// this assumes strip initialization is done in the calling code.

NeoDigit::NeoDigit(CRGB *leds, int leds_per_segment){
  _leds_per_segment = leds_per_segment;
  _leds = leds;
}

void NeoDigit::display(int value, int color){
  FastLED.clear();
  // for segments in digit
  for (int i=0 ; (i < 7)  ; i++){
    if (allSegments[value][i] < 0)
      break;
    int segment = allSegments[value][i];
    for (int x=0; x< _leds_per_segment; x++){
      _leds[x+(segment * _leds_per_segment)] = CHSV(color,255,192);
    }
  }
}
// this one blanks the non lit segments for a "masked display"
void NeoDigit::display(int value){
  // for segments in digit
  for (int i=0 ; (i < 7)  ; i++){
    if (maskSegments[value][i] < 0)
      break;
    int segment = maskSegments[value][i];
    //    Serial.print("Segment: ");Serial.println(segment);
    for (int x=0; x< _leds_per_segment; x++){
      _leds[x+(segment * _leds_per_segment)] = 0;
    }
  }
}
