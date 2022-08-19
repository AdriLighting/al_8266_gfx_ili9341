#ifndef _TFT_H_
#define _TFT_H_
  #include "libextern.h"
	

	// #ifdef ALML_TFT Serial.printf_P(PSTR("[al_sensosApi::httpget] get_httpdata code: %d\n"), code);
		#include "tfttxt.h"
	  #include "icons.h"
	  #include "fonts/ArialRoundedMTBold_10.h"
	  #include "fonts/ArialRoundedMTBold_11.h"
	  #include "fonts/ArialRoundedMTBold_12.h"
	  // #include "fonts/ArialRoundedMTBold_14.h"
	  // #include "fonts/ArialRoundedMTBold_15.h"
	  // #include "fonts/ArialRoundedMTBold_16.h"
	  #include "fonts/SansSerif_plain_14.h"
	  #include "fonts/SansSerif_plain_15.h"
	  #include "fonts/SansSerif_plain_13.h"
	  #include "fonts/SansSerif_plain_12.h"
	  #include "fonts/SansSerif_plain_11.h"
	  #include "fonts/SansSerif_plain_10.h"	
	  #include "fonts/SansSerif_bold_11.h"	
	  #include "fonts/SansSerif_bold_12.h"	
	  #include "fonts/SansSerif_bold_13.h"	
	  #include "fonts/SansSerif_bold_14.h"	
	  #include "fonts/SansSerif_bold_15.h"	

	
	static const char ALGFXILI_PATH_CONFIG [] PROGMEM = "/algfx_config.json";
    
  typedef struct al_gfx_data_t{
		uint16_t 	_calibr_x1 				= 0;
		uint16_t 	_calibr_y1 				= 0;
		uint16_t 	_calibr_x2 				= 0;
		uint16_t 	_calibr_y2 				= 0;
		uint8_t 	_pin_cs 					= 0;
		uint8_t 	_pin_dc 					= 0;	
		uint8_t 	_rotationDir			= 0;
		uint8_t 	_pin_xpt2406_cs		= 0;	
		uint8_t 	_pin_xpt2406_irq	= 0;	
		uint8_t 	_mod_touch				= 0;	
  } al_gfx_data_t;

	class al_gfx_xpt2406 {
	public:
		typedef enum : uint8_t {CALIBR_LAUNCH = 0, CALIBR_SETUP, CALIBR_FS, CALIBR_NONE} calibration_t; 

	private:
		uint8_t _rotationDir	= 0;
		calibration_t _mod_calibration = CALIBR_LAUNCH;
		uint16_t _calibr_x1;
		uint16_t _calibr_y1;
		uint16_t _calibr_x2;
		uint16_t _calibr_y2;
	public:
		al_gfx_xpt2406() {
		};
		~al_gfx_xpt2406() {

		};
		void set_calibrationMod(uint8_t v);
		uint8_t get_calibrationMod() ;
		void set_rotation(uint8_t);
		void begin(JsonObject & root);
		void get_pos(uint16_t & x1, uint16_t & y1, uint16_t & x2, uint16_t & y2);
		void calibrate(Adafruit_ILI9341 * tft, XPT2046 * touch);
	};

	class al_gfx_ili9341 {
	public:
		typedef enum : uint8_t {TOUCH_ENABLED = 0, TOUCH_DISABLED, TOUCH_NONE} touch_t; 
		// typedef enum : uint8_t {CALIBR_LAUNCH = 0, CALIBR_SETUP, CALIBR_FS, ALIBR_NONE} calibration_t; 

	private:	
		DynamicJsonDocument _config;

		al_gfx_xpt2406 * _al_gfx_xpt2406 = nullptr;

		uint8_t _pin_cs 					= 0;
		uint8_t _pin_dc 					= 0;	
		uint8_t _rotationDir			= 0;
		uint8_t _pin_xpt2406_cs		= 0;	
		uint8_t _pin_xpt2406_irq	= 0;	

		// uint8_t _calibration 	= 0;
		touch_t _mod_touch = TOUCH_NONE;
		
		boolean config_read();

	public:


		al_gfx_ili9341(size_t cSize);
		al_gfx_ili9341(size_t cSize, uint8_t tftCs, uint8_t tftDC);
		al_gfx_ili9341(size_t cSize, uint8_t tftCs, uint8_t tftDC, uint8_t xptCs, uint8_t xptIrq);
		~al_gfx_ili9341();

		void tft(Adafruit_ILI9341 *& ptr);
		void u8g2(U8G2_FOR_ADAFRUIT_GFX *& ptr);
		al_gfx_xpt2406 *  xpt2406() { return _al_gfx_xpt2406; };

		void begin();

		void clear();
		void testTxt();
		void drawBmp(Adafruit_ILI9341 * _tft, const String & filename, uint8_t x, uint16_t y);	

		void set_rotationDir(uint8_t v);
		void set_calibrationMod(uint8_t v);
		void set_modTouch(uint8_t v);

		boolean config_loadDevice();
		void config_load();
		boolean config_sav();
		boolean config_sav(al_gfx_data_t * data);
		void set_data(al_gfx_data_t * data);
	};

		extern Adafruit_ILI9341				* _algfxili_tft;
		extern U8G2_FOR_ADAFRUIT_GFX	_algfxili_u8g2;
		extern const uint8_t 					* _algfx_font_default;	
		extern XPT2046 								* _algfx_touch;
		// // extern XPT2046_Touchscreen		_algfx_xpt2406;
		// namespace almlTft {
		// 	void clear();
		// 	void testTxt();
		// 	void begin(uint8_t);
		// 	void drawBmp(Adafruit_ILI9341 * _tft, const String & filename, uint8_t x, uint16_t y);
		// }		
	// #endif

#endif // TFT_H