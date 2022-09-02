/**
 * MIT License
 * 
 * Copyright (c) 2022 Adrien Grellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LIBEXTERN_H
#define LIBEXTERN_H

#include <Arduino.h>

#include <ArduinoJson.h>

#ifdef FILESYSTEM 
  #if defined USE_LITTLEFS
    #if defined(ESP8266)
      #include <LittleFS.h> 
    #elif defined(ESP32)
      #include <FS.h>
      #include <LITTLEFS.h>
    #endif
  #elif defined USE_SPIFFS
    #include <FS.h>
  #endif
#endif  

#include <SD.h>

// #include <JPEGDecoder.h>


#include <SPI.h>


#include <Adafruit_I2CDevice.h>

#if defined(ESP8266)
  #include <Adafruit_ILI9341esp.h> 
#elif defined(ESP32)
  #include <Adafruit_ILI9341.h>
#endif

// #include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <XPT2046.h>
// #include <XPT2046_Touchscreen.h>
#include <U8g2_for_Adafruit_GFX.h>

#include <LinkedList.h>

#include <adri_timer.h>
#include <altoolslib.h>



#endif // LIBEXTERN_H