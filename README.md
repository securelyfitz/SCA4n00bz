SCA4n00bz
=========

Timing-based Sidechannel Attacks for Hardware N00bz workshop

Built around an ultra low-cost kit of hardware hacking tools, this workshop provides  instructions stepping through the process of conducting a timing side channel attack against a PIN validation system. 
The workshop provides a beginner-level hardware hacking project with no soldering and
minimal flashing lights. It will show exactly how cheap and feasible hardware attacks really are, and introduce some basic tools for hardware hacking.

Contents
========
* Arduino-compatible ATMega328p Pro Micro.
* Cypress EZ-USBFX2 based 8 channel 24 MHz Logic Analyzer
* Keypad
* LED strip
* Proble clips, wires, etc.
* Instruction manual
* Bootable USB drive with Lubuntu 12.04 and necessary software

Files
=====
The kit includes a USB key with a bootable Lubuntu 12.04 minimal install, and all the tools/files compiled and in place. 

username: user

password:password


Due to quirks of USB passthrough, virtualizaton generally doesn't work for the USB logic analyzer. OSX + Parallels works, every other tested combination is a study in frustration.

If you intend to use the tools further or would just rather not trust my usb drives, the instructions and files are here.

There are three parts: Arduino, Pulseview, and workshop files.

Arduino
-------
Arduino is easy. You can install it from the package manager, or just download the easy installer from http://arduino.cc/en/Main/Software
The workshop usues 1.0.5 but should work fine with other versions

Pulseview
---------
Pulseview is more difficult. I believe fedora includes it as a package, but most platforms require building it from source.
First get the open source firmware: http://sigrok.org/wiki/Fx2lafw
Then, navigate to http://sigrok.org/wiki/Main_Page and choose your OS under 'Documentation' You need to build libsigrok and then pulseview

Workshop Files
--------------
Uzip libraries.zip into your ~/sketchbook/, ~/arduino/ ~/Documents/sketchbook, or ~/Documents/arduino, whichever your install happens to use. This includes the LED driving (Neopixel), 'Keypad', and 'Password' libraries, plus the sample code used in the activities.
