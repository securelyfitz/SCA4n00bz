// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, July 25, 2013
//    This version modified by joefitz@securinghardware.com to add interactive eeprom read/write from serial console
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>


void eeprom_i2c_write(byte address, byte from_addr, byte data) {
  Wire.beginTransmission(address);
  Wire.write(from_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte eeprom_i2c_read(int address, int from_addr) {
  Wire.beginTransmission(address);
  Wire.write(from_addr);
  Wire.endTransmission();

  Wire.requestFrom(address, 1);
  if(Wire.available())
    return Wire.read();
  else
    return 0xFF;
}


void setup()
{
  Serial.begin(9600);
  Wire.begin();

  byte error, address;
  int nDevices;

  Serial.println("Scanning for I2C devices...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found.\n");
  else
  {
    Serial.println("done.\n");
    Serial.println("To read an EEPROM: [Device Address]R[offset]C[# bytes]");
    Serial.println("    Example: 80R00 or 80R00C8");
    Serial.println("To write an EEPROM: [Device Address]W[offset]D[Data]D[Data]...");
    Serial.println("    Example: 80W00D255 or 80W01D37D9D129D56D1D0D0 or 80W01D169D8D9D0D132D35D0 or 80W01D180D4D19D134");
    Serial.println("\n Pardon my bad coding, you must enter decimal numbers, and there is minimal error checking");
  }
  Serial.println("To rescan, press the reset button\n");
  Serial.print(">");
}

void loop()
{
  byte address,offset,count;
  byte rORw,d,c;
  byte writeData;
  if (Serial.available() > 0) {
    address = Serial.parseInt();
    Serial.print("Device 0x");
    Serial.print(address,HEX);
    Serial.println(":");
    rORw = Serial.read();
    if (rORw=='R')
    {
      offset = Serial.parseInt();
      Serial.print("Reading from 0x");
      Serial.println(offset,HEX);
      c = Serial.read();
      if (c=='C')
      {
        count = Serial.parseInt();
        Serial.print("bytes to read:");
        Serial.println(count);
      }
      else count=1;
      for (int i=0;i<count;i++)
      {
        Serial.print(offset+i,HEX);
        Serial.print(": ");
        Serial.println(eeprom_i2c_read(address,offset+i),HEX);
      }
    }
    else if (rORw=='W')
    {
      offset = Serial.parseInt();
      while(Serial.available()>0)
      {
        d = Serial.read();
        if (d=='D')
        {
          writeData = Serial.parseInt();
          Serial.print(offset,HEX);
          Serial.print(": ");
          Serial.println(writeData,HEX);
          eeprom_i2c_write(address,offset++,writeData);
        }
        else Serial.println("Error Parsing Command\n");
      }
    }
    else Serial.println("Error Parsing Command\n");
    Serial.print(">");
  }    
}

