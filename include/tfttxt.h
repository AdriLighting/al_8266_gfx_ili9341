#ifndef TFTTXT_H
#define TFTTXT_H

  #include "libextern.h"

// #ifdef ALML_TFT


	#define C_BLACK       0x0000
	#define C_BLUE        0x001F
	#define C_RED         0xF800
	#define C_GREEN       0x07E0
	#define C_CYAN        0x07FF
	#define C_MAGENTA     0xF81F
	#define C_YELLOW      0xFFE0
	#define C_WHITE       0xFFFF
	#define C_LTBLUE      0xB6DF
	#define C_LTTEAL      0xBF5F
	#define C_LTGREEN     0xBFF7
	#define C_LTCYAN      0xC7FF
	#define C_LTRED       0xFD34
	#define C_LTMAGENTA   0xFD5F
	#define C_LTYELLOW    0xFFF8
	#define C_LTORANGE    0xFE73
	#define C_LTPINK      0xFDDF
	#define C_LTPURPLE    0xCCFF
	#define C_LTGREY      0xE71C
	#define C_TEAL        0x0438
	#define C_ORANGE      0xFD20
	#define C_PINK        0xF81F
	#define C_PURPLE      0x801F
	#define C_GREY        0xC618
	#define C_DKBLUE      0x0069
	#define C_DKTEAL      0x020C
	#define C_DKGREEN     0x03E0
	#define C_DKCYAN      0x03EF
	#define C_DKRED       0x6000
	#define C_DKMAGENTA   0x8008
	#define C_DKYELLOW    0x8400
	#define C_DKORANGE    0x8200
	#define C_DKPINK      0x9009
	#define C_DKPURPLE    0x4010
	#define C_DKGREY      0x4A49



enum TextAlignment {
	LEFT, CENTER, RIGHT
};

class Tft_txt
{
	uint16_t 	_tc;
	uint16_t 	_bc;


	const GFXfont * _font;

	uint8_t 			_u8g2_mod 	= 0;
	uint8_t 			_u8g2_dir 	= 0;
	const uint8_t  * 	_u8g2_font = NULL;

public:
	String	_text;
	int16_t _text_x_ref = 1;
	int16_t _text_x = 1;
	int16_t _canvas_x;
	int16_t _canvas_y;		
	int16_t _canvas_w;
	int16_t _canvas_h;	
	int16_t _text_y;
	int16_t _text_w;
	int16_t _text_h;	
	TextAlignment _alignment = LEFT;

	U8G2_FOR_ADAFRUIT_GFX	 _u8g2;
	Adafruit_ILI9341 *	 	_tft;
	GFXcanvas1 * 			_canvas;

	Tft_txt(Adafruit_ILI9341 * tft, U8G2_FOR_ADAFRUIT_GFX u8g2);
	~Tft_txt(){};

	void canvas_create(int16_t x, int16_t y, int16_t w, int16_t h);
	void canvas_pos(int16_t x, int16_t y, int16_t w, int16_t h);
	void canvas_display();
	void canvas_update();

	void textColor(uint16_t c);
	void textAlign(const String & text);
	void textAlignment(TextAlignment alignment);

	void textColor(uint16_t c, uint16_t bg) ;
	void textPos(int16_t x, int16_t y) ;
	void textPos(int16_t x, int16_t y, int16_t w, int16_t h);
	void textGet_xy(int16_t & x, int16_t & y);

	void text_font(const GFXfont * font) ;
	void text_setup();
	void text(const String & s);

	void drawString_getWh(const String & text, uint16_t & w, uint16_t & h);
	void drawString(int16_t x, int16_t y, const String & text, uint16_t c, uint16_t bc, const GFXfont * font);
	void drawString(int16_t x, int16_t y, const String & text, uint16_t c, const GFXfont * font);
	void drawString(const String & text);		
	void drawString();		
	void drawString(const String & text, int16_t w, int16_t h);

	void drawString(int x, int y, char *text);
	void drawString(int x, int y, const String & text);

	void drawStringAling(const String & text, TextAlignment p);

	void u8g2_setup();
	void u8g2_setup(const String & v, uint16_t tc, uint16_t bc, const uint8_t * f);
	void u8g2_draw(const int16_t & x,  const int16_t & y, const String & str);
	void u8g2_draw(const int16_t & x,  const int16_t & y, const String & str, uint16_t tc, const uint8_t * f);
	void u8g2_draw(const int16_t & x,  const int16_t & y, const String & str, uint16_t tc, uint16_t bc, const uint8_t * f);
	void u8g2_drawC(int16_t x, const int16_t & y, const String & str, uint16_t tc, uint16_t bc, const uint8_t * f);
	void u8g2_drawC(int16_t x, const int16_t & maxW, const int16_t & y, const String & str, uint16_t tc, uint16_t bc, const uint8_t * f);
	// void u8g2_drawL(int16_t x, int16_t y, const String & str, uint16_t tc, uint16_t bc, const uint8_t * f);
	void u8g2_drawR(const int16_t & marge, int16_t x, const int16_t & y, const String & str, uint16_t tc, uint16_t bc, const uint8_t * f);

	void u8g2_draw(const String & v);
	void u8g2_draw();
	void u8g2_drawRect();
	void u8g2_drawRect(const String & v);
	void u8g2_drawRect(const String & v, int16_t x, int16_t y)	;
	void u8g2_drawRect(const int16_t & h,  int16_t w)	;
	void u8g2_get_wh(int16_t & w, int16_t & h);
	void u8g2_get_wh(const String & v,int16_t & w, int16_t & h);
	

	void u8g2_mod(uint8_t c); // transparent = 1
	void u8g2_dir(uint8_t c);
	void u8g2_font(const uint8_t * f);

};




// #endif
#endif // TFTTXT_H