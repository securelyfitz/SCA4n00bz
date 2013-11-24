//modified neopixel's strand_test to give a variety of logic analyzer-viewable pins.
//Added uart serial out to report which pattern was being displayed.
//Added shiftOut() on pin 2 of some loop variables.
//joefitz@securinghardware.com

#include <Adafruit_NeoPixel.h>

#define PIN 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

int dataPin=2;
int clockPin=3;


void setup() {
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  shiftOut(dataPin,clockPin,MSBFIRST,1);
  Serial.println("Red");
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  shiftOut(dataPin,clockPin,MSBFIRST,2);
  Serial.println("Green");
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  shiftOut(dataPin,clockPin,MSBFIRST,3);
  Serial.println("Blue");
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  Serial.println("Rainbow");
  rainbow(20);
  Serial.println("Cycle");
  rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    shiftOut(dataPin,clockPin,MSBFIRST,j);
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    shiftOut(dataPin,clockPin,MSBFIRST,j);
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

