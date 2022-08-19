#ifndef TFTBUTTON_H
#define TFTBUTTON_H
  #include "libextern.h"
  #include "tft.h"

class algfxili9341_button
{
	Adafruit_ILI9341 		* _tft;
	U8G2_FOR_ADAFRUIT_GFX 	_u8g2;

	int 		_pos;
	int16_t 	_x;
	int16_t 	_y;
	int16_t 	_w;
	int16_t 	_h;
	int16_t 	_r;
	int16_t 	_s;
	uint16_t 	_borderColor;
	uint16_t 	_backgroundColor;
	uint16_t 	_oldBackgroundColor;
	uint16_t 	_textColor;
	uint16_t 	_oldTextColor;
	String 		_text;
	// button_mod 			_mod;
	// button_relower_mod 	_modRelower;
	const uint8_t *	_u8g2_font;
	const GFXfont *	_font;

	
public:
	algfxili9341_button();
	~algfxili9341_button();
	
};

#endif // TFTBUTTON_H