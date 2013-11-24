/*
||  Simple Password Entry Using Matrix Keypad
||  4/5/2012 Updates Nathan Sobieck: Nathan@Sobisource.com
||
||  7/2013 updated by joefitz@securinghardware.com
||  fixed password not reset after check
||  added support for LED strip output
||  pulled colorWipe from adafruit neopixel library and reversed direction of wipe.
||  all so it looks pretty to demonstrate a timing side channel attack against password.checkPassword()
*/


//* is to validate password   
//# is to reset password attempt

/////////////////////////////////////////////////////////////////

#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip

#define LEDPIN 10

Password password = Password( "1234" );
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, LEDPIN, NEO_GRB + NEO_KHZ800);

int keycount=0;

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  strip.begin();
  strip.show();
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword(); keycount=0;
	  case '#': password.reset(); keycount=0; colorWipe(strip.Color(0,0,0),0); break;
	  default: password.append(eKey); strip.setPixelColor(keycount++, strip.Color(0,0,63));
     }
     strip.show();
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
    colorWipe(strip.Color(0, 63, 0), 50); // Red
    //Add code to run if it works
  }else{
    Serial.println("Wrong");
    colorWipe(strip.Color(63, 0, 0), 50); // Red
    //add code to run if it did not work
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i-1, c);
      strip.show();
      delay(wait);
  }
}
