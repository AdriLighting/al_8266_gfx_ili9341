#include "../include/tftbutton.h"


algfxili9341_button::algfxili9341_button(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s, uint16_t bc, uint16_t tc) {
	_x 					= x;
	_y 					= y;
	_w 					= w;
	_h 					= h;
	_r 					= r;
	_s 					= s;
	_borderColor 		= ILI9341_LIGHTGREY;
	_backgroundColor 	= bc;
	_oldBackgroundColor = bc;
	_textColor 			= tc;
	_oldTextColor 		= tc;
	_u8g2_font	 		= NULL;
	_font	 			= NULL;
	// _func	 			= noFunc;
	_modRelower 		= BTMR_BORDER;
}

void algfxili9341_button::create_fromLoop(){
	BUTTON_MOD_T mod = _mod;
	switch(mod) {
		// case BTM_VOLUME:	buttonVolume_create(); 			break;
		// case BTM_RND: 		buttonRandom_create(); 			break;
		// case BTM_NEXT: 		buttonNext_create(); 			break;
		// case BTM_PREV: 		buttonPrev_create(); 			break;
		// case BTM_PAUSE: 	buttonPause_create(); 			break;
		// case BTM_PLAY: 		buttonPlay_create(); 			break;
		// case BTM_UP: 		buttonUp_create(); 				break;
		// case BTM_DOWN: 		buttonDown_create(); 			break;
		case BTM_TEXT: 		buttonText_create(""); 			break;
		case BTM_FTEXT: 	buttonFromText_create(_text);	break;
		case BTM_TEXTUTF8:  buttonTextUtf8_create(_text);	break;
		case BTM_FTEXTUTF8: buttonFromTextUtf8_create(_text);	break;		
		case BTM_SIMPL: 	button_noBc_create();				break;		
		default:break;
	}
}
void algfxili9341_button::button_upd(){
	BUTTON_MOD_T mod = _mod;
	switch(mod) {
		// case BTM_VOLUME:	buttonVolume_upd(); 		break;
		// case BTM_RND: 		buttonRandom_upd(); 		break;
		// case BTM_NEXT: 		buttonNext_upd(); 			break;
		// case BTM_PREV: 		buttonPrev_upd(); 			break;
		// case BTM_PAUSE: 	buttonPause_upd(); 			break;
		// case BTM_PLAY: 		buttonPlay_upd(); 			break;
		// case BTM_UP: 		buttonUp_upd(); 			break;
		// case BTM_DOWN: 		buttonDown_upd(); 			break;
		case BTM_TEXT: 		buttonText_create(""); 		break;
		case BTM_FTEXT: 	buttonFromText_create(""); 	break;
		case BTM_TEXTUTF8:  buttonTextUtf8_create(_text);	break;
		case BTM_FTEXTUTF8: buttonFromTextUtf8_create(_text);	break;		
		case BTM_SIMPL: 	button_noBc_create(); 			break;	
		default:break;	
	}
}

/**************************************************************************/
/*!
	@brief    Helper to let us know if a coordinate is within the bounds of the
   button
	@param    x       The X coordinate to check
	@param    y       The Y coordinate to check
	@returns  True if within button graphics outline
*/
/**************************************************************************/
boolean algfxili9341_button::contains(int16_t x, int16_t y) {
  return ((x >= _x) && (x < (int16_t)(_x + _w)) && (y >= _y) &&
		  (y < (int16_t)(_y + _h)));
}

/**************************************************************************/
/*!
   @brief    Query whether the button was pressed since we last checked state
   @returns  True if was not-pressed before, now is.
*/
/**************************************************************************/
boolean algfxili9341_button::justPressed() { return (_currstate && !_laststate); }

/**************************************************************************/
/*!
   @brief    Query whether the button was released since we last checked state
   @returns  True if was pressed before, now is not.
*/
/**************************************************************************/
boolean algfxili9341_button::justReleased() {
  return (!_currstate && _laststate);
}

void algfxili9341_button::isPressed(uint16_t x, uint16_t y){
	
	if (contains(x, y)) {
		// this->_func();
		if (_modRelower==BTMR_LOGO){
			if (this->button_changeTextColor(_relower_color)){
				this->button_upd();
				_relower = true;
			}
		}
		if (_modRelower==BTMR_BORDER){
			if (this->button_changeTextColor(_relower_color)){
				_relower = true;
				button_borderColor(true, ILI9341_GREEN);	
			}
		}		
	}

}
void algfxili9341_button::relowerOff(){
	if (_relower) {
		_relower = false;
		if (_modRelower==BTMR_BORDER){
			button_borderColor(false, 0);
		}
		if (_modRelower==BTMR_LOGO){
			if (button_changeTextColor(_oldTextColor))button_upd();		
		}
	}
}
void algfxili9341_button::button_relower_logo(){
	_modRelower = BTMR_LOGO;
}
void algfxili9341_button::button_relower_border(){
	_modRelower = BTMR_BORDER;
}
boolean algfxili9341_button::button_changeTextColor(uint16_t newC){
	if (newC != _textColor) {_textColor = newC; return true;}
	return false;
}

boolean algfxili9341_button::set_bgColor(uint16_t newC){
	if (newC != _backgroundColor) {_backgroundColor = newC; return true;}
	return false;
}
void algfxili9341_button::button_invertColor(boolean state){
	if (state) {
		_backgroundColor 	= _oldTextColor;
		_textColor 			= _oldBackgroundColor;
	}else {
		_backgroundColor 	= _oldBackgroundColor;
		_textColor 			= _oldTextColor;
	}
}
void algfxili9341_button::set_borderColor( uint16_t c){
	_borderColor = c;
}
void algfxili9341_button::set_font_u8g2(const uint8_t * font) {
	_u8g2_font = font;
}
void algfxili9341_button::set_font(const GFXfont * font) {
	_font = font;
}
void algfxili9341_button::set_text(const String & txt) {
	_text = txt;
}
void algfxili9341_button::set_pos(int16_t x, int16_t y, int16_t s) {
	if (x != -1) _x = x;
	if (y != -1) _y = y;
	if (s != -1) _s = s;
}
void algfxili9341_button::button_changeSize(int16_t w, int16_t h, int16_t r) {
	if (w != -1) _w = w;
	if (h != -1) _h = h;
	if (r != -1) _r = r;
}
void algfxili9341_button::button_changePS(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s) {
	if (x != -1) _x = x;
	if (y != -1) _y = y;	
	if (w != -1) _w = w;
	if (h != -1) _h = h;
	if (r != -1) _r = r;
	if (s != -1) _s = s;
}

void algfxili9341_button::button_borderColor(boolean state, uint16_t c){
	if (state) {
		_algfxili_tft->drawRoundRect(
				_x, 
				_y, 
				_w, 
				_h, 
				_r, 
				c
			);
	}else {
		_algfxili_tft->drawRoundRect(
				_x, 
				_y, 
				_w, 
				_h, 
				_r, 
				_borderColor
			);
	}
}
void algfxili9341_button::button_create(){
	_algfxili_tft->fillRoundRect(
			_x, 
			_y, 
			_w, 
			_h, 
			_r, 
			_backgroundColor
		);
	_algfxili_tft->drawRoundRect(
			_x, 
			_y, 
			_w, 
			_h, 
			_r, 
			_borderColor
		);	
}  
void algfxili9341_button::button_clear(){
	_algfxili_tft->fillRoundRect(
			_x, 
			_y, 
			_w, 
			_h, 
			_r, 
			ILI9341_BLACK
		);
} 
void algfxili9341_button::button_noBc_create(){
	_algfxili_tft->drawRoundRect(
			_x, 
			_y, 
			_w, 
			_h, 
			_r, 
			_borderColor
		);		
}  
void algfxili9341_button::buttonSimple_noBc_create(){
	_mod = BTM_SIMPL;
	button_noBc_create();
} 

void algfxili9341_button::buttonSimple_noBc_upd(){
	button_noBc_create();
}  


/*
	creation du text a ajouter au bouton
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
	return void	
*/
void algfxili9341_button::button_create_text(const String & text) {

	String getText = text;
	if (getText == "") getText = _text;
	if (getText == "") return;

	_algfxili_tft->setFont(_font); 	

	_text	= getText;
	_mod 	= BTM_TEXT;

	int16_t x1, y1;
	uint16_t w, h;
	_algfxili_tft->setTextWrap(false);
	_algfxili_tft->getTextBounds(getText, 0, 0, &x1, &y1, &w, &h);	

	int16_t x0 = _x;
			x0 = x0 + (_w/2);
			x0 = x0 - (w / 2);
	int16_t y0 = _y;
			y0 = y0 + (_h/2);
			y0 = y0 + (h / 2);

	_algfxili_tft->setTextColor(_textColor, ILI9341_BLACK); 		
	_algfxili_tft->setCursor(x0, y0);
	_algfxili_tft->print(getText);	
}
/*
	creation du bouton + texte
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
			police				
	return void	
*/
void algfxili9341_button::buttonText_create(const String & text, const GFXfont * font){
	_mod = BTM_TEXT;
	_font = font;
	button_create();
	button_create_text(text);
}  
void algfxili9341_button::buttonText_create(const String & text){
	_mod = BTM_TEXT;
	button_create();
	button_create_text(text);
}  

/*
	creation du text et de son bouton baser sur la taille du texte
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
			postion x, y du texte
	return void	
*/
void algfxili9341_button::buttonFromText(const String & text, int16_t btX, int16_t btY){

	String getText = text;
	if (getText == "") getText = _text;
	if (getText == "") return;

	_algfxili_tft->setFont(_font); 	

	_text 	= getText;
	_mod 	= BTM_FTEXT;

	int16_t x1, y1;
	uint16_t w, h;
	_algfxili_tft->setTextWrap(false);
	_algfxili_tft->getTextBounds(getText, 0, 0, &x1, &y1, &w, &h);	

	_x = btX;
	_y = btY;
	_w = w + _s;
	_h = h + _s;

	button_create();

	int16_t x0 = _x;
			x0 = x0 + (_w/2);
			x0 = x0 - (w / 2);
	int16_t y0 = _y;
	 		y0 = y0 + (_h/2);
	 		y0 = (y0 + (h / 2)) - 1;

		
	_algfxili_tft->setTextColor(_textColor, _backgroundColor); 		
	_algfxili_tft->setCursor(x0, y0);
	_algfxili_tft->print(getText);		
} 
void algfxili9341_button::buttonFromText_create(const String & text, int16_t btX, int16_t btY){
	buttonFromText(text, btX, btY);
} 
void algfxili9341_button::buttonFromText_create(const String & text, const GFXfont * font) {
	_font = font;
	buttonFromText(text, _x, _y);
} 
void algfxili9341_button::buttonFromText_create(const String & text) {
	buttonFromText(text, _x, _y);
} 





/*
	creation du text a ajouter au bouton
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
	return void	
*/
void algfxili9341_button::button_create_textUtf8(const String & text) {
	
	String getText = text;

	if (getText == "") getText = _text;
	if (getText == "") return;

	_text	= getText;
	_mod 	= BTM_TEXT;

	char buf[120];
	sprintf(buf, "%s", getText.c_str());
	uint16_t w, h;

	_algfxili_u8g2.setFont(_u8g2_font); 	
	_algfxili_u8g2.setFontMode(0);                
	_algfxili_u8g2.setFontDirection(0);  
  	_algfxili_u8g2.setBackgroundColor(_backgroundColor);
  	_algfxili_u8g2.setForegroundColor(_textColor);   

	// ha = _algfxili_u8g2.getFontAscent();
	h = _algfxili_u8g2.getFontAscent() - _algfxili_u8g2.getFontDescent();
	w = _algfxili_u8g2.getUTF8Width(buf);

	int16_t x0 = _x;
			x0 = x0 + (_w/2);
			x0 = x0 - (w / 2);
	int16_t y0 = _y;
			y0 = y0 + ((_h/2) + (h/2));
			y0 = (y0 - 2);

	_algfxili_u8g2.setCursor(x0,y0);   
	_algfxili_u8g2.print(getText);	
}

/*
	creation du bouton + texte
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
			police				
	return void	
*/
void algfxili9341_button::buttonTextUtf8_create(const String & text, const uint8_t * font){
	_mod = BTM_TEXTUTF8;
	_u8g2_font = font;
	button_create();
	button_create_textUtf8(text);
}  
void algfxili9341_button::buttonTextUtf8_create(const String & text){
	_mod = BTM_TEXTUTF8;
	button_create();
	button_create_textUtf8(text);
}  

/*
	creation du text et de son bouton baser sur la taille du texte
	parm : 	ptr ver lobjet bouton,	
			String text || si String == "" alor sa update le text
			postion x, y du texte
	return void	
*/
void algfxili9341_button::buttonFromTextUtf8(const String & text, int16_t btX, int16_t btY){

	String getText = text;
	if (getText == "") getText = _text;
	if (getText == "") return;


	_text 	= getText;
	_mod 	= BTM_FTEXTUTF8;

	char buf[120];
	sprintf(buf, "%s", getText.c_str());
	uint16_t w, h;

	_algfxili_u8g2.setFont(_u8g2_font); 	
	_algfxili_u8g2.setFontMode(1);                
	_algfxili_u8g2.setFontDirection(0);  
  	_algfxili_u8g2.setBackgroundColor(_backgroundColor);
  	_algfxili_u8g2.setForegroundColor(_textColor);    

	// ha = _algfxili_u8g2.getFontAscent();
	h = _algfxili_u8g2.getFontAscent() ;
	w = _algfxili_u8g2.getUTF8Width(buf);

	_x = btX;
	_y = btY;
	_w = w + _s;
	_h = h + _s;

	button_create();
	int h2 = h/2;
	int16_t x0 = _x;
			x0 = x0 + (_w/2);
			x0 = x0 - (w / 2);
	int16_t y0 = _y;
			y0 = y0 + (_h/2);
	 		y0 = y0 + (h2);
	 		// y0 = y0 - ha;

	// _tft->drawFastHLine(_x, y0, _w, _textColor);

	_algfxili_u8g2.setCursor(x0,y0);         
	_algfxili_u8g2.print(getText);		
} 
void algfxili9341_button::buttonFromTextUtf8_create(const String & text, int16_t btX, int16_t btY){
	buttonFromTextUtf8(text, btX, btY);
} 
void algfxili9341_button::buttonFromTextUtf8_create(const String & text, const uint8_t * font) {
	_u8g2_font = font;
	buttonFromTextUtf8(text, _x, _y);
} 
void algfxili9341_button::buttonFromTextUtf8_create(const String & text) {
	buttonFromTextUtf8(text, _x, _y);
} 







algfxili9341_screenTouchItem::algfxili9341_screenTouchItem(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t s, uint16_t bc, uint16_t tc){
	_bt = new algfxili9341_button(x, y, w, h, r, s, bc, tc);
}


void algfxili9341_screenTouch::setup(){
  if (!_timer_1) _timer_1 = new adri_timer(timerMod::ONESHOT, 250, true);
  if (!_timer_2) _timer_2 = new adri_timer(timerMod::REPEAT, 250, true);
  if (!_timer_3) _timer_3 = new adri_timer(timerMod::REPEAT, 250, false);
  _mod = 0;
  _timer_1->activate();  
  _cX = _cY = 0;
}
LList<algfxili9341_screenTouchItem *> & algfxili9341_screenTouch::get_list(){
  return _list;
}
void algfxili9341_screenTouch::clear() {
	Serial.printf("algfxili9341_screenTouch clear - list: %d\n", _list.size());
  while (_list.size()) {
    algfxili9341_screenTouchItem * item = _list.shift();
    delete item;
  }
  _list.clear(); 
}
bool algfxili9341_screenTouch::isTouched(XPT2046 * touchScreen) {
  return touchScreen->isTouching();
}
void algfxili9341_screenTouch::tick(){
	if (!_algfx_touch) return;
	
	if (_list.size() <= 0) return;

  if ( _timer_1->Loop()) {

    if (isTouched(_algfx_touch)) {

      _mod = 0;

      _algfx_touch->getPosition(_cX, _cY);

      // Serial.printf("_cX: %d - _cY: %d\n", _cX, _cY);
      // screenTouchLoop_timer_1->activate();
    } else {
      _cX = _cY = 0xffff;
    }
  } 


  for(uint8_t i = 0; i < _list.size(); ++i) {

    algfxili9341_button * bt = get_button(i);
    algfxili9341_screenTouchItem * item = get_itemn(i);

    bt->press(bt->contains(_cX, _cY));

    if (bt->justPressed()) {

      _timer_2->set_duration(millis()-80);

      if (!_timer_3->isActivate()) {_timer_3->activate();_intervalLock=i;}

      _interval = i;

      bt->button_borderColor(true, ILI9341_GREEN);  

    } 
    if (bt->justReleased()) {

      if (_interval >= 0 ) {

        _mod = 1;
        _timer_1->activate(false);

        if (_timer_2->loop()) {

          // sprintf(buffer, "[%d] - %s - %s", i, ui.button_manage[i]->_screen, curr_screen);
          // Serial.println(buffer);

          bt->button_borderColor(false, 0);

          item->get_cb();
          Serial.printf("[button_loop SC] [%d]\n", _interval);

          _timer_3->activate(false);

        }else {
          _resetBorder = true;
        }

        _interval = -1;

      }

      _mod = 0;
      break;
    }
  }

  if (_timer_3->isActivate()) {
    if (_timer_3->loop(2500)) {
      if ((_interval >= 0 ) && (_intervalLock==_interval)){

        algfxili9341_button * bt = get_button(_interval);
    		algfxili9341_screenTouchItem * item = get_itemn(_interval);

        Serial.printf("[button_loop LC RESET] [%d]\n", _interval);
                    
        bt->button_borderColor(false, 0);

        // int eventPos = ui.button_manage[_interval]->_eventPos;
        // String eventStr = ui.button_manage[_interval]->_enventStr;
        // if (eventStr !="")      ui.button[_interval]->_funcParmStr(eventStr);
        // else if (eventPos == -1)  ui.button[_interval]->_func();
        // else              ui.button[_interval]->_funParm(eventPos);
				item->get_cb();

        _intervalLock  = -1;
        _interval      = -1;

        // timer_1->activate();
        _timer_3->activate(false);
      } 
    } 
  }

  if (_resetBorder) {
    _resetBorder = false;
    _timer_3->activate(false);
    for(uint8_t i = 0; i < _list.size(); ++i) {
      algfxili9341_button * item = get_button(i);
      item->button_borderColor(false, 0);
    }
  }

  switch (_mod) {
    case 0: if (!_timer_1->isActivate()) _timer_1->activate(); break;
    default: break;
  }

} 