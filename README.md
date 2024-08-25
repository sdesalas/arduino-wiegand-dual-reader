# arduino-wiegand-multi-reader
A multi-reader library for Wiegand Access Devices, for Arduino and ESP8266

Based on [`monkeyboard/Wiegand-Protocol-Library-for-Arduino`](https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino).


This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

# Different Wiegand libraries comparison

| Library | Description | Single/Multi Device | Chip Support |
| ---| --- | --- | --- | 
| [Wiegand library](https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino) | This is the easiest and cleanest library to use when only a single wiegand reader is needed. I strongly suggest to use this version if you only need one reader support | Single | Arduino/AVR, ESP8266, ESP32  |
| [Wiegand NG library](https://github.com/jpliew/Wiegand-NG-Multi-Bit-Wiegand-Library-for-Arduino) | This is another single reader library, however it uses dynamic memory to store the raw wiegand thus allowing unlimited bit length to be stored as long as your Arduino board has the memory to store it. I won't recommend to use this library unless you are facing a non-standard wiegand reader that sends out data that will not be decoded by the original Wiegand library. | Single | Arduino/AVR, ESP8266, ESP32  |
| [Multi Wiegand library](https://github.com/jpliew/Multi-Reader-Wiegand-Protocol-Library-for-Arduino) | This library uses pin change interrupt, thus allowing all the pin change interrupt supported pins to be used. With this, multiple readers can also be supported. Due to a workaround (hack) used to overcome the limitation with `attachInterrupt` not being able to be attached to the class method directly, the initialisation of the sketch is more ugly and complicated. | Multi | Arduino/AVR |
| Wiegand Multi Reader (this one) | This library support multiple Wiegand readers (as many as you have pins for), however because it does not depend on the [`PinInterruptChange` library](https://github.com/NicoHood/PinChangeInterrupt) so it can also be used in ESP32/ESP8266 devices | Multi | Arduino/AVR, ESP8266, ESP32  |
