#include "../include/tft.h"

  #define TFT_CS    D8     // TFT CS  pin is connected to NodeMCU pin D8 - D1
  #define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
  #define TFT_DC    D4    // TFT DC  pin is connected to NodeMCU pin D4 - D2
// #ifdef ALML_TFT
#define BUFFPIXEL 20


Adafruit_ILI9341			* _algfxili_tft = nullptr /*= Adafruit_ILI9341(TFT_CS, TFT_DC)*/;
XPT2046 							* _algfx_touch = nullptr;//(/*cs=*/ D2, /*irq=*/ D1);// D2-D3  D1-D4
U8G2_FOR_ADAFRUIT_GFX	_algfxili_u8g2;
const uint8_t 				* _algfx_font_default = u8g2_font_helvR14_tf;




void calibratePoint(Adafruit_ILI9341 * tft, XPT2046 * touch, uint16_t x, uint16_t y, uint16_t &vi, uint16_t &vj) {
	tft->drawFastHLine(x - 8, y, 16,0xff);
	tft->drawFastVLine(x, y - 8, 16,0xff);
	while (!touch->isTouching()) {
		delay(10);
	}

	touch->getRaw(vi, vj);

	tft->drawFastHLine(x - 8, y, 16, 0);
	tft->drawFastVLine(x, y - 8, 16, 0);
}
void al_gfx_xpt2406::calibrate(Adafruit_ILI9341 * tft, XPT2046 * touch) {
	uint16_t x1, y1, x2, y2;
	uint16_t vi1, vj1, vi2, vj2;

	touch->getCalibrationPoints(x1, y1, x2, y2);
	calibratePoint(tft, touch, x1, y1, vi1, vj1);
	delay(1000);
	calibratePoint(tft, touch, x2, y2, vi2, vj2);

	_calibr_x1 = vi1;
	_calibr_y1 = vj1;
	_calibr_x2 = vi2;
	_calibr_y2 = vj2;	
	touch->setCalibration(_calibr_x1, _calibr_y1, _calibr_x2, _calibr_y2);

	char buf[80];
	sprintf(buf,  "[al_gfx_xpt2406::calibrate]\n\t%d,%d,%d,%d", (int)_calibr_x1, (int)_calibr_y1, (int)_calibr_x2, (int)_calibr_y2);
	Serial.println(buf);
}

void al_gfx_xpt2406::set_rotation(uint8_t dir){
  switch (dir) {
    case 0: _algfx_touch->setRotation(_algfx_touch->ROT0); 		break;
    case 1: _algfx_touch->setRotation(_algfx_touch->ROT90); 	break;
    case 2: _algfx_touch->setRotation(_algfx_touch->ROT180); 	break;
    case 3: _algfx_touch->setRotation(_algfx_touch->ROT270); 	break;
    default: break;
  }	
}
void al_gfx_xpt2406::begin(JsonObject & root){
	ALT_TRACEC("main",  "\n");

	_algfx_touch->begin(_algfxili_tft->width(), _algfxili_tft->height()); 

  switch (_mod_calibration) {
    case calibration_t::CALIBR_LAUNCH: 
    	calibrate( _algfxili_tft,  _algfx_touch);
    break;
    case calibration_t::CALIBR_SETUP: 
    case calibration_t::CALIBR_FS: 		
			_calibr_x1 = root[F("x1")].as<uint16_t>();
			_calibr_y1 = root[F("y1")].as<uint16_t>();
			_calibr_x2 = root[F("x2")].as<uint16_t>();
			_calibr_y2 = root[F("y2")].as<uint16_t>();     	
    	_algfx_touch->setCalibration(_calibr_x1, _calibr_y1, _calibr_x2, _calibr_y2);
    break;
    default: break;
  }

	ALT_TRACEC("main",  "&c:1&s:\t%d,%d,%d,%d\n\tmod_calibration: %d\n", (int)_calibr_x1, (int)_calibr_y1, (int)_calibr_x2, (int)_calibr_y2, _mod_calibration);

}
void al_gfx_xpt2406::set_calibrationMod(uint8_t v) { 
  switch (v) {
    case 0: _mod_calibration = CALIBR_LAUNCH; break;
    case 1: _mod_calibration = CALIBR_SETUP; 	break;
    case 2:	_mod_calibration = CALIBR_FS; 		break;
    case 3:	_mod_calibration = CALIBR_NONE; 	break;
    default: break;
  }		
}
uint8_t al_gfx_xpt2406::get_calibrationMod() {
	return _mod_calibration;
}
void al_gfx_xpt2406::get_pos(uint16_t & x1, uint16_t & y1, uint16_t & x2, uint16_t & y2) {
	x1 = _calibr_x1;
	y1 = _calibr_y1;
	x2 = _calibr_x2;
	y2 = _calibr_y2;		
}


		al_gfx_ili9341::al_gfx_ili9341(size_t cSize) : _config(cSize) {

		  // _algfxili_tft 	= new Adafruit_ILI9341(_pin_cs, _pin_dc);
		  // if ()
		}

		al_gfx_ili9341::al_gfx_ili9341(size_t cSize, uint8_t tftCs, uint8_t tftDC) : _config(cSize) {
			_pin_cs 				= tftCs;
			_pin_dc 				= tftDC;

			_mod_touch 			= TOUCH_DISABLED;

		  _algfxili_tft 	= new Adafruit_ILI9341(_pin_cs, _pin_dc);
		}
		al_gfx_ili9341::al_gfx_ili9341(size_t cSize, uint8_t tftCs, uint8_t tftDC, uint8_t xptCs, uint8_t xptIrq) : _config(cSize)   {
			_pin_cs 					= tftCs;
			_pin_dc 					= tftDC;	
			_pin_xpt2406_cs		= xptCs;	
			_pin_xpt2406_irq	= xptIrq;	

			_mod_touch 				= TOUCH_ENABLED;

		  _algfxili_tft			= new Adafruit_ILI9341(_pin_cs, _pin_dc);
		  _algfx_touch 			= new XPT2046(/*cs=*/ _pin_xpt2406_cs, /*irq=*/ _pin_xpt2406_irq);	
		  _al_gfx_xpt2406		= new al_gfx_xpt2406();	

		  // JsonObject obj = _config.createNestedObject(F("TFT"));
		  // obj[F("cs")] = _pin_cs;
		  // obj[F("dc")] = _pin_dc;
		  // serializeJsonPretty(_config, Serial);Serial.println("");
		}

void al_gfx_ili9341::tft(Adafruit_ILI9341 *& ptr) { ptr = _algfxili_tft;}
void al_gfx_ili9341::u8g2(U8G2_FOR_ADAFRUIT_GFX *& ptr) { ptr = &_algfxili_u8g2;}

boolean al_gfx_ili9341::config_loadDevice() {
	ALT_TRACEC("main", "\n");

	File f = FILESYSTEM.open(FPSTR(ALGFXILI_PATH_CONFIG), "r");
	if (!f) { ALT_TRACEC("main", "&c:1&s:\terror open file \"r\", path: %s\n", ALGFXILI_PATH_CONFIG); return false;}

	_config.clear();_config.garbageCollect();

	DeserializationError error = deserializeJson(_config, f);

	if (!error) {
		#ifdef ALT_DEBUG_TARCE
			serializeJsonPretty(_config, Serial);Serial.println();	
		#endif

	  _pin_cs 					= _config[F("TFT")][F("pin_cs")].as<uint8_t>();
	  _pin_dc 					= _config[F("TFT")][F("pin_dc")].as<uint8_t>();
	  _pin_xpt2406_cs 	= _config[F("TFT")][F("pin_xpt2406_cs")].as<uint8_t>();
	  _pin_xpt2406_irq 	= _config[F("TFT")][F("pin_xpt2406_irq")].as<uint8_t>();

		_rotationDir = _config[F("TFT")][F("rotationDir")];
		ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _rotationDir", _rotationDir);
	  
		set_modTouch(_config[F("TFT")][F("mod_touch")].as<uint8_t>());
		ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _mod_touch", _mod_touch);

	  _algfxili_tft			= new Adafruit_ILI9341(_pin_cs, _pin_dc);

	  if (_mod_touch == touch_t::TOUCH_ENABLED) {
	  	ALT_TRACEC("main", "&c:1&s:\tnew instance of: XPT2046 && al_gfx_xpt2406\n");
		  _algfx_touch 			= new XPT2046(/*cs=*/ _pin_xpt2406_cs, /*irq=*/ _pin_xpt2406_irq);	
		  _al_gfx_xpt2406		= new al_gfx_xpt2406();	
		  set_calibrationMod(_config[F("TFT")][F("TOUCH")][F("mod_calibration")].as<uint8_t>());
			ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _mod_calibration", _al_gfx_xpt2406->get_calibrationMod());			
	  }


	}
	f.close();
	// _config.clear();_config.garbageCollect();
	// if (!AP_deserializeFile(_config, ALGFXILI_PATH_CONFIG)) {
	// 	serializeJsonPretty(_config, Serial);Serial.println();
	// 	return false;
	// }	

	return true;	
}
boolean al_gfx_ili9341::config_read() {
	ALT_TRACEC("main", "\n");

	File f = FILESYSTEM.open(FPSTR(ALGFXILI_PATH_CONFIG), "r");
	if (!f) { ALT_TRACEC("main", "&c:1&s:\terror open file \"r\", path: %s\n", ALGFXILI_PATH_CONFIG); return false;}

	_config.clear();_config.garbageCollect();

	DeserializationError error = deserializeJson(_config, f);
	if (!error) {
		#ifdef ALT_DEBUG_TARCE
			serializeJsonPretty(_config, Serial);Serial.println();	
		#endif

		_rotationDir = _config[F("TFT")][F("rotationDir")];
		ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _rotationDir", _rotationDir);

		set_modTouch(_config[F("TFT")][F("mod_touch")].as<uint8_t>());
		ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _mod_touch", _mod_touch);

		if (_mod_touch == touch_t::TOUCH_ENABLED){
			set_calibrationMod(_config[F("TFT")][F("TOUCH")][F("mod_calibration")].as<uint8_t>());
			ALT_TRACEC("main", "&c:1&s:\t%-25sto %d\n", "set _mod_calibration", _al_gfx_xpt2406->get_calibrationMod());			
		}

	}
	f.close();
	// _config.clear();_config.garbageCollect();
	// if (!AP_deserializeFile(_config, ALGFXILI_PATH_CONFIG)) {
	// 	serializeJsonPretty(_config, Serial);Serial.println();
	// 	return false;
	// }	

	return true;	
}
void al_gfx_ili9341::config_load(){ 
  if (!config_read()) {
  	set_calibrationMod(0);
  }
}

void al_gfx_ili9341::set_modTouch(uint8_t v) { 
  switch (v) {
    case 0: _mod_touch = TOUCH_ENABLED; 	break;
    case 1: _mod_touch = TOUCH_DISABLED; 	break;
    default: break;
  }		
}

void al_gfx_ili9341::set_data(al_gfx_data_t * data){
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;  
  _al_gfx_xpt2406->get_pos(x1, y1, x2, y2);	
	data->_calibr_x1 				= x1;
	data->_calibr_y1 				= y1;
	data->_calibr_x2 				= x2;
	data->_calibr_y2 				= y2;
	data->_pin_cs 					= _pin_cs;
	data->_pin_dc 					= _pin_dc;	
	data->_rotationDir			= _rotationDir;
	data->_pin_xpt2406_cs		= _pin_xpt2406_cs;	
	data->_pin_xpt2406_irq	= _pin_xpt2406_irq;	
	data->_mod_touch				= _mod_touch;	
}
boolean al_gfx_ili9341::config_sav(al_gfx_data_t * data) {

	File f = FILESYSTEM.open(FPSTR(ALGFXILI_PATH_CONFIG), "w");
	if (!f) return false;
	_config.clear();_config.garbageCollect();
  JsonObject obj = _config.createNestedObject(F("TFT"));
  obj[F("pin_cs")] 					= data->_pin_cs;
  obj[F("pin_dc")] 					= data->_pin_dc;
  obj[F("rotationDir")] 		= data->_rotationDir;
  obj[F("pin_xpt2406_cs")] 	= data->_pin_xpt2406_cs;
  obj[F("pin_xpt2406_irq")] = data->_pin_xpt2406_irq;
  obj[F("mod_touch")] 			= data->_mod_touch;
  JsonObject xptobj = obj.createNestedObject(F("TOUCH"));
  xptobj[F("x1")] = data->_calibr_x1;
  xptobj[F("y1")] = data->_calibr_y1;
  xptobj[F("x2")]	= data->_calibr_x2;
  xptobj[F("y2")]	= data->_calibr_y2;  
  xptobj[F("mod_calibration")] = data->_mod_calibration;  
  serializeJson(_config, f);
  f.close();
	return true;	
}
boolean al_gfx_ili9341::config_sav() {
	ALT_TRACEC("main",  "\n");

	File f = FILESYSTEM.open(FPSTR(ALGFXILI_PATH_CONFIG), "w");
	if (!f) { ALT_TRACEC("main", "&c:1&s:\terror open file \"w\", path: %s\n", ALGFXILI_PATH_CONFIG); return false;}
	_config.clear();_config.garbageCollect();
  JsonObject obj = _config.createNestedObject(F("TFT"));
  obj[F("pin_cs")] 					= _pin_cs;
  obj[F("pin_dc")] 					= _pin_dc;
  obj[F("rotationDir")] 		= _rotationDir;
  obj[F("pin_xpt2406_cs")] 	= _pin_xpt2406_cs;
  obj[F("pin_xpt2406_irq")] = _pin_xpt2406_irq;
  obj[F("mod_touch")] 			= _mod_touch;
  JsonObject xptobj = obj.createNestedObject(F("TOUCH"));
  if (_mod_touch == touch_t::TOUCH_ENABLED) {
		uint16_t x1;
		uint16_t y1;
		uint16_t x2;
		uint16_t y2;  
	  _al_gfx_xpt2406->get_pos(x1, y1, x2, y2);
	  xptobj[F("x1")] = x1;
	  xptobj[F("y1")] = y1;
	  xptobj[F("x2")]	= x2;
	  xptobj[F("y2")]	= y2;  
	  xptobj[F("mod_calibration")] = _al_gfx_xpt2406->get_calibrationMod();
	}
  serializeJson(_config, f);
  f.close();
	#ifdef ALT_DEBUG_TARCE
		serializeJsonPretty(_config, Serial);Serial.println();	
	#endif  
	return true;	
}


void al_gfx_ili9341::begin(){

	ALT_TRACEC("main",  "\n");
	ALT_TRACEC("main",  "&c:1&s:\t%-18s: %d\n\t%-18s: %d\n\t%-18s: %d\n\t%-18s: %d\n\t%-18s: %d\n\t%-18s: %d\n", 
		"_pin_cs", _pin_cs, "t_pin_dc", _pin_dc, "_rotationDir", _rotationDir, "_pin_xpt2406", _pin_xpt2406_cs, "_pin_xpt2406", _pin_xpt2406_irq, "_mod_touch: ", _mod_touch);

  _algfxili_tft->begin();
  _algfxili_tft->fillScreen(ILI9341_BLACK);

  if (_mod_touch == touch_t::TOUCH_ENABLED) {
  	JsonObject obj = _config[F("TFT")][F("TOUCH")];
  	_al_gfx_xpt2406->begin(obj);
   	set_calibrationMod(1);
  }

  _algfxili_tft->setRotation(_rotationDir);

  if (_mod_touch == touch_t::TOUCH_ENABLED) _al_gfx_xpt2406->set_rotation(_rotationDir);

  _algfxili_u8g2.begin(*_algfxili_tft); 

}

void al_gfx_ili9341::set_rotationDir(uint8_t v) { _rotationDir = v; }
void al_gfx_ili9341::set_calibrationMod(uint8_t v) {
	if (_mod_touch == touch_t::TOUCH_DISABLED) return;
	_al_gfx_xpt2406->set_calibrationMod(v);
}



void al_gfx_ili9341::clear(){_algfxili_tft->fillScreen(ILI9341_BLACK);}
uint16_t color565(Adafruit_ILI9341 * _tft, uint8_t r, uint8_t g, uint8_t b){
	return _tft->color565(r, g, b);
}





// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

void al_gfx_ili9341::drawBmp(Adafruit_ILI9341 * _tft, const String & filename, uint8_t x, uint16_t y) {
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  // boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0;

	if((x >= _tft->width()) || (y >= _tft->height())) return;
	#if defined(ESP8266)
		bmpFile = FILESYSTEM.open(filename, "r");
	#elif defined(ESP32)
		bmpFile = FILESYSTEM.open(filename, "r");
	#else
	#endif    		
	

	if (!bmpFile) return;

  	if(read16(bmpFile) == 0x4D42) { 							// BMP signature
		read32(bmpFile); 										// "File size"
		(void)read32(bmpFile); 									// Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); 						// Start of image data "Image Offset"

		// Read DIB header
		read32(bmpFile);										// "Header size"
		bmpWidth  = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if(read16(bmpFile) == 1) { 								// # planes -- must be '1'
	 		bmpDepth = read16(bmpFile); 						// bits per pixel
	  		if((bmpDepth == 24) && (read32(bmpFile) == 0)) { 	// 0 = uncompressed
				// goodBmp = true; 								// Supported BMP format -- proceed!
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.				
				if(bmpHeight < 0) {
					bmpHeight = -bmpHeight;
					flip      = false;
				}

        		// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;
				if((x+w-1) >= _tft->width())  w = _tft->width()  - x;
				if((y+h-1) >= _tft->height()) h = _tft->height() - y;
				_tft->setAddrWindow(x, y, x+w-1, y+h-1);
				for (row=0; row<h; row++) { 					// For each scanline...

				/* 	Seek to start of scan line.  It might seem labor-
					intensive to be doing this on every line, but this
					method covers a lot of gritty details like cropping
					and scanline padding.  Also, the seek only takes
					place if the file position actually needs to change
					(avoids a lot of cluster math in SD library). 	*/					
					if(flip)									// Bitmap is stored bottom-to-top order (normal BMP)
						pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
					else     									// Bitmap is stored top-to-bottom
						pos = bmpImageoffset + row * rowSize;
					if(bmpFile.position() != pos) { 			// Need seek?
						bmpFile.seek(pos, SeekSet);
						buffidx = sizeof(sdbuffer); 			// Force buffer reload
					}

					for (col=0; col<w; col++) { 				// For each pixel...
						if (buffidx >= sizeof(sdbuffer)) { 		// Indeed
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; 						// Set index to beginning
						}

            			// Convert pixel from BMP to TFT format, push to display
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];
						_tft->pushColor(_tft->color565(r,g,b));
						yield();
					} 											// end pixel
				} 												// end scanline
	  		} 													// end goodBmp
		}
  	}
 	bmpFile.close();
}

// #endif