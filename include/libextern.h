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
#include <Adafruit_ILI9341esp.h> 
// #include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <XPT2046.h>
// #include <XPT2046_Touchscreen.h>
#include <U8g2_for_Adafruit_GFX.h>

#include <LinkedList.h>

#include <adri_timer.h>
#include <altoolslib.h>



#endif // LIBEXTERN_H