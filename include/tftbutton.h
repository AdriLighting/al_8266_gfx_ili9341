#ifndef TFTBUTTON_H
#define TFTBUTTON_H
  #include "libextern.h"
  #include "tft.h"



typedef enum : uint8_t {
	BTM_PAUSE = 0, 
	BTM_UP, 
	BTM_DOWN, 
	BTM_PLAY, 
	BTM_TEXT,
	BTM_FTEXT, 
	BTM_TEXTUTF8, 
	BTM_FTEXTUTF8, 
	BTM_NEXT, 
	BTM_PREV, 
	BTM_RND, 
	BTM_VOLUME, 
	BTM_UNK,
	BTM_SIMPL
} BUTTON_MOD_T;

typedef enum : uint8_t {
	BTMR_BORDER= 0, BTMR_LOGO, BTMR_BORLO
} BUTTON_MOD_RELOWER_T;



class algfxili9341_button
{

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
	BUTTON_MOD_T					_mod;
	BUTTON_MOD_RELOWER_T	_modRelower;
	const uint8_t *	_u8g2_font;
	const GFXfont *	_font;
	boolean 
		_currstate, 
		_laststate;
	boolean _relower = false;
	uint16_t 	_relower_color = ILI9341_WHITE;
	
public:
	algfxili9341_button(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s, uint16_t bc, uint16_t tc);
	~algfxili9341_button(){};

	void set_mod(BUTTON_MOD_T v1) {_mod = v1;}
	void set_font_u8g2(const uint8_t * font);
	void set_font(const GFXfont * font);
	void set_text(const String & txt);
	void set_borderColor( uint16_t c);
	void 		set_pos(int16_t x, int16_t y, int16_t s);
	boolean	set_bgColor(uint16_t newC);
	
	void 		button_borderColor(boolean state, uint16_t c);

	void create_fromLoop();
	void button_upd();

	boolean contains(int16_t x, int16_t y);
	boolean justPressed();
	void press(boolean p) {
		_laststate = _currstate;
		_currstate = p;
	}	
	boolean justReleased();

private:

	void isPressed(uint16_t x, uint16_t y);


	void 		relowerOff();
	void 		button_relower_logo();
	void 		button_relower_border();
	boolean	button_changeTextColor(uint16_t newC);
	void 		button_invertColor(boolean state);
	void 		button_changeSize(int16_t w, int16_t h, int16_t r);
	void 		button_changePS(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s);



	void button_create();
	void button_clear();
	void button_noBc_create();
	void buttonSimple_noBc_create();
	void buttonSimple_noBc_upd(); 

	void button_create_text(const String & text);
	void buttonText_create(const String & text, const GFXfont * font);
	void buttonText_create(const String & text);
	void buttonFromText(const String & text, int16_t btX, int16_t btY);
	void buttonFromText_create(const String & text, int16_t btX, int16_t btY);
	void buttonFromText_create(const String & text, const GFXfont * font);
	void buttonFromText_create(const String & text);
	void button_create_textUtf8(const String & text);

	void buttonTextUtf8_create(const String & text, const uint8_t * font);
	void buttonTextUtf8_create(const String & text);
	void buttonFromTextUtf8(const String & text, int16_t btX, int16_t btY);
	void buttonFromTextUtf8_create(const String & text, int16_t btX, int16_t btY);
	void buttonFromTextUtf8_create(const String & text, const uint8_t * font);
	void buttonFromTextUtf8_create(const String & text);


};
class algfxili9341_screenTouchItem
{
  typedef std::function<void()> callback_function_t;

  algfxili9341_button * _bt;
  callback_function_t _cb = nullptr;
public:
	algfxili9341_screenTouchItem(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s, uint16_t bc, uint16_t tc);
	~algfxili9341_screenTouchItem(){if (_bt) delete _bt; };
  algfxili9341_button * get_button(uint8_t i)	{  return _bt; }
  void set_cb(callback_function_t c1) { _cb = std::move(c1); }
  void get_cb() { if (_cb) _cb(); }
};

class algfxili9341_screenTouch
{

  uint16_t _cX;
  uint16_t _cY;
  int16_t _interval      = -1;
  boolean _resetBorder   = false;
  int16_t _intervalLock  = -1;
  uint8_t _mod = 0; 
  adri_timer * _timer_1   = nullptr;
  adri_timer * _timer_2   = nullptr;
  adri_timer * _timer_3   = nullptr;  

  LList<algfxili9341_screenTouchItem *> _list;

public:
  algfxili9341_screenTouch(){};
  ~algfxili9341_screenTouch(){};

  bool isTouched(XPT2046 * touchScreen);
  void tick();
  void setup();

  int size() 																		{ return _list.size(); }
  void add(algfxili9341_screenTouchItem *btn) 				{ _list.add(btn); }
  void remove(int i) 														{ _list.remove(i); }
  algfxili9341_button * get_button(uint8_t i)		{ return _list.get(i)->get_button(i); }
  algfxili9341_screenTouchItem * get_itemn(uint8_t i)	{ /*Serial.printf("get item: %d/%d\n", i, _list.size()); r*/return _list.get(i);}
  void clear();
  LList<algfxili9341_screenTouchItem *> & get_list(); 
};
#endif // TFTBUTTON_H