# arduino-wiegand-multi-reader

A multi-reader library for Wiegand Access Devices, for Arduino _and_ ESP8266/ESP32.

Supports protocols for 4 bit, 8 bit, 24 bit, 26 bit, 32 bit and 34 bit Wiegand.

Based on [`monkeyboard/Wiegand-Protocol-Library-for-Arduino`](https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino).

<img width="500" src="img/IMG_20240825_192013.jpg">

# Different Wiegand libraries comparison

| Library | Description | Single/Multi Device | Chip Support |
| ---| --- | --- | --- | 
| [Wiegand library](https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino) | This is the easiest and cleanest library to use when only a single wiegand reader is needed. I strongly suggest to use this version if you only need one reader support | Single | Arduino/AVR, ESP8266, ESP32  |
| [Multi Wiegand library](https://github.com/jpliew/Multi-Reader-Wiegand-Protocol-Library-for-Arduino) | This library uses pin change interrupt, thus allowing all the pin change interrupt supported pins to be used. With this, multiple readers can also be supported. Due to a workaround (hack) used to overcome the limitation with `attachInterrupt` not being able to be attached to the class method directly, the initialisation of the sketch is more ugly and complicated. | Multi | Arduino/AVR |
| **Wiegand Multi Reader** (this one) | This library support multiple Wiegand readers (as many as you have pins for), however it can also be used in ESP32/ESP8266 devices. | Multi | Arduino/AVR, ESP8266, ESP32  |

# Usage

This example is for ESP8266 boards.

If you're using a newer ESP32 board make sure you replace `ICACHE_RAM_ATTR` below with `IRAM_ATTR`.

```cpp

#include "WiegandMultiReader.h"

// Define Reader 1 (Card reader)
WIEGAND cardReader();
int cardPinD0 = 5; // D1 (GPIO5) GREEN "D0"
int cardPinD1 = 4; // D2 (GPIO4) WHITE "D1"
int cardStatusLED = 0; // D3 (GPIO0) STATUS LED --> ON = OK
void ICACHE_RAM_ATTR cardReadD0() {
  cardReader.ReadD0();
}
void ICACHE_RAM_ATTR cardReadD1() {
  cardReader.ReadD1();
}

// Define Reader 2 (Keypad)
WIEGAND keypadReader();
int keypadPinD0 = 12; // D6 (GPIO12) GREEN "D0"
int keypadPinD1 = 13; // D7 (GPIO13) WHITE "D1"
int keypadStatusLED = 14; // D5 (GPIO14) STATUS LED --> ON = OK
void ICACHE_RAM_ATTR keypadReadD0() {
  keypadReader.ReadD0();
}
void ICACHE_RAM_ATTR keypadReadD1() {
  keypadReader.ReadD1();
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.println("Starting Wiegand Card Reader..");
  pinMode(cardPinD0, INPUT);
  pinMode(cardPinD1, INPUT);
  pinMode(cardStatusLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(cardPinD0), cardReadD0, FALLING);
  attachInterrupt(digitalPinToInterrupt(cardPinD1), cardReadD1, FALLING);

  Serial.println("Starting Wiegand Keypad..");
  pinMode(keypadPinD0, INPUT);
  pinMode(keypadPinD1, INPUT);
  pinMode(keypadStatusLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(keypadPinD0), keypadReadD0, FALLING);
  attachInterrupt(digitalPinToInterrupt(keypadPinD1), keypadReadD1, FALLING);
  
  Serial.println("Ready for input..");
}

void loop() {
  if(cardReader.available())
  {
    Serial.print("cardReader WG HEX = ");
    Serial.print(cardReader.getCode(),HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(cardReader.getCode());
    Serial.print(", Type W");
    Serial.println(cardReader.getWiegandType());    
  }
  if(keypadReader.available())
  {
    Serial.print("keypadReader WG HEX = ");
    Serial.print(keypadReader.getCode(),HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(keypadReader.getCode());
    Serial.print(", Type W");
    Serial.println(keypadReader.getWiegandType());    
  }
  // Status LEDs     (=> ON if device connected properly)
  delay(50);
  digitalWrite(cardStatusLED, digitalRead(cardPinD0) & digitalRead(cardPinD1));
  digitalWrite(keypadStatusLED, digitalRead(keypadPinD0) & digitalRead(keypadPinD1));
}

```

<img src="docs/sketch.png">

# Licensing / Credits

_This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version._

_This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details._
