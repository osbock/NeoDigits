
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    A2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 21

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

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

 int allSegments[10][7] = {
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


// setup() function -- runs once at startup --------------------------------

void setup() {

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(115200);
}
void blank(){
  for(int i =0; i < 7*LEDS_PER_SEGMENT; i++){
    strip.setPixelColor(i, 0);
  }
  strip.show();
}
void digit(int dig, int color){
  blank();
  // for segments in digit
  for (int i=0 ; (i < 7)  ; i++){
    if (allSegments[dig][i] < 0)
      break;
    int segment = allSegments[dig][i];
    for (int x=0; x< LEDS_PER_SEGMENT; x++){
      strip.setPixelColor(x+(segment*LEDS_PER_SEGMENT), color);
    }
    //Serial.println(segment);
  }

  strip.show();
}
// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
 for (int i =0; i <=9; i++)
 {
  Serial.print("Digit: ");Serial.println(i);
  digit(i, strip.Color(0,0,255));
  delay(1000);
 }
}
