#include <Adafruit_NeoPixel.h>

#define PIN 6
#define STRIPPIN 7
#define LEDCOUNT 10

const int FADE_LENGTH = 8;
const int FADE_SCALE  = 128;
const int PIXEL_COUNT = 67;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel LEDstrip = Adafruit_NeoPixel(LEDCOUNT, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, STRIPPIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, avoid connecting
// on a live circuit... if you must, connect GND first. Minimize
// distance between Arduino and first pixel.

uint8_t eyes[] = {0, 2, 4, 6, 8};
uint8_t eyebrightness[] = {50, 200, 0, 150, 100};
uint8_t eyedirection[] = {1, -1, 1, 1, -1};
int cometled = 0;

void setup() {
  LEDstrip.begin();
  LEDstrip.show(); // Initialize all pixels to 'off'
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  for (uint8_t i = 0; i < 5; i++) {
   eyeGlow(i);
  }

  comet(cometled);
  cometled++;
  if (cometled > (PIXEL_COUNT * 5)) {
    cometled = 0;
  }
  delay(10);

}

// make pairs of eyes glow
void eyeGlow(uint8_t i) {

  if (eyebrightness[i] > 254) {
    eyedirection[i] = -1;
  }
  if (eyebrightness[i] < 1) {
    eyedirection[i] = 1;
  }

  eyebrightness[i] += eyedirection[i];
  uint8_t brightness = 0;
  if (eyebrightness[i] < 55) {
    brightness = 0;
  }
  else {
    brightness = eyebrightness[i] - 55;
  }


  LEDstrip.setPixelColor(eyes[i], brightness, 0, 0);
  LEDstrip.setPixelColor(eyes[i] + 1, brightness, 0, 0);
  LEDstrip.show();

}

void comet (int i) {
    for ( int p = 0 ; p < PIXEL_COUNT ; p++ ) {
      strip.setPixelColor( p, 0 );  //  clear the strip
    }
    drawFade( i, 255, 0, 0);        //  then draw the fade
    strip.show();
}


void drawFade ( int start, uint8_t r, uint8_t g, uint8_t b ) {
  int brightness = PIXEL_COUNT;
  for ( int p = 0 ; p < FADE_LENGTH ; p++ ) {
    strip.setPixelColor(
      ( start - p ) % PIXEL_COUNT,
      strip.Color(
        ( r * brightness ) / 255,
        ( g * brightness ) / 255,
        ( b * brightness ) / 255
      )
    );
    brightness = ( brightness * FADE_SCALE ) / 255;
  }
}



