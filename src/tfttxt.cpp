#include "../include/tfttxt.h"
// #include <Ticker.h>


// uint8_t UPDATE_BOT_PANEL_INTERVAL_SECS = 10;             // Update bottom-panel every 10 seconds; changed from const to uint8 to allow changes via web-config; 26-Jan-2018, DKF
// bool readyForBotPanelUpdate = false;

// Ticker botPanelTicker;
// #ifdef ALML_TFT

namespace {

}

Tft_txt::Tft_txt(Adafruit_ILI9341 * tft, U8G2_FOR_ADAFRUIT_GFX u8g2){
  _tft  = tft;
  _u8g2   = u8g2;
}

void Tft_txt::textAlignment(TextAlignment alignment) {
  _alignment = alignment;
}
void Tft_txt::textColor(uint16_t c) {
  _tc = _bc = c;
}
void Tft_txt::textColor(uint16_t c, uint16_t bg) {
  _tc = c;
  _bc = bg;
}
void Tft_txt::textPos(int16_t x, int16_t y) {
  _text_x = x;
  _text_y = y;
}
void Tft_txt::textAlign(const String & text) {

  char buf[text.length()+2];
  text.toCharArray(buf, text.length() + 1);
  int16_t x1, y1;
  uint16_t w, h;  
  _tft->getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
  _text_x = (_canvas_w/2)-(w/2);
  // _text_y = (_canvas_h/2);
}
void Tft_txt::textPos(int16_t x, int16_t y, int16_t w, int16_t h){
  _text_x   = x;
  _text_y   = y;
  _text_w   = w;
  _text_h   = h;
}
void Tft_txt::text(const String & text) {
  _text = text;
}
void Tft_txt::textGet_xy(int16_t & x, int16_t & y) {
  x = _text_x;              
  y = _text_y;              
}

void Tft_txt::text_font(const GFXfont * font) {
  _font = font;
}


void Tft_txt::drawString_getWh(const String & text, uint16_t & w, uint16_t & h) {
  char buf[text.length()+2];
  text.toCharArray(buf, text.length() + 1);
  int16_t x1, y1;
  _tft->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
}

void Tft_txt::text_setup() {
  _tft->setTextColor(_tc, _bc);
  _tft->setFont(_font);                   
}

void Tft_txt::drawString(int16_t x, int16_t y, const String & text, uint16_t c, const GFXfont * font) {
  _tc   = _bc = c;
  _font   = font;
  _text   = text;                         
  _tft->setTextColor(_tc, _bc);
  _tft->setFont(_font);
  uint16_t w, h;
  drawString_getWh(text, w, h); 
  switch (_alignment) {
    case LEFT:
      x = x;
      break;
    case CENTER:
      x = x - w / 2;
      break;
    case RIGHT:
      x = x - w;
      break;
  }
  _text_x = x;
  _text_y = y;    
  _tft->setCursor(x, y);
  _tft->print(text);
}
uint16_t Tft_txt::drawString(int16_t x, int16_t y, const String & text, uint16_t c, uint16_t bc, const GFXfont * font) {
  _tc   = c;
  _bc   = bc;
  _font   = font;
  _text   = text;                         
  _tft->setTextColor(_tc, _bc);
  _tft->setFont(_font);
  uint16_t w, h;
  drawString_getWh(text, w, h);
  switch (_alignment) {
    case LEFT:
      x = x;
      break;
    case CENTER:
      x = x - w / 2;
      break;
    case RIGHT:
      x = x - w;
      break;
  } 
  _text_x = x;
  _text_y = y;  
  _tft->fillRect(x, y - h -1, w + 1, h + 4, _bc);
  _tft->setCursor(x, y);
  _tft->print(text);
  return y + h;
}
/*
void Tft_txt::drawStringReverse(int16_t x, int16_t y, const String & text, uint16_t c, uint16_t bc, const GFXfont * font) {
  _tc   = c;
  _bc   = bc;
  _font   = font;
  _text   = text;                         
  _tft->setTextColor(_tc, _bc);
  _tft->setFont(_font);
  uint16_t w, h;
  drawString_getWh(text, w, h);
  switch (_alignment) {
    case LEFT:
      x = x;
      break;
    case CENTER:
      x = x - w / 2;
      break;
    case RIGHT:
      x = x - w;
      break;
  } 
  _text_x = x;
  _text_y = y;  

  // _tft->fillRect(x, y - h -1, w + 1, h + 4, _bc);
  // _tft->setCursor(x, y);
  // _tft->print(text);

}
*/
void Tft_txt::drawStringAling(const String & text, TextAlignment pos) {
  _tft->setFont(_font);

  uint16_t wo, ho;
  drawString_getWh(_text, wo, ho);
  
  int x = _text_x_ref;
  switch (pos) {
    case LEFT:
      x = x;
      break;
    case CENTER:
      x = x - wo / 2;
      break;
    case RIGHT:
      x = x - wo;
      break;
  } 
  _tft->fillRect(x, _text_y - ho -1, wo + 1, ho + 4, _bc);

  _text = text;

  textAlignment(pos);
  drawString(_text_x_ref, _text_y, text, _tc, _bc, _font);
  textAlignment(LEFT);

}

void Tft_txt::drawString(const String & text) {
  _tft->setFont(_font);
  _tft->setCursor(_text_x, _text_y);

  uint16_t wo, ho;
  drawString_getWh(_text, wo, ho);

  uint16_t w, h;
  drawString_getWh(text, w, h);

  if (_tc != _bc) {  
    if (wo>w)   _tft->fillRect(_text_x, _text_y - ho -1,  wo + 1, ho + 4, _bc);
    else      _tft->fillRect(_text_x, _text_y - h -1,   w + 1,  h + 4,  _bc);
  } 

  _text   = text; 

  _tft->print(text);
}

void Tft_txt::drawString() {
  _tft->setFont(_font);
  _tft->setCursor(_text_x, _text_y);

  uint16_t w, h;
  drawString_getWh(_text, w, h);

  if (_tc != _bc) _tft->fillRect(_text_x, _text_y - h -1, w + 1,  h + 4,  _bc);

  _tft->print(_text);
}
void Tft_txt::drawString(const String & text, int16_t w2, int16_t h2) {
  _text   = text;    
  _tft->fillRect(_text_x, _text_y - (h2/2)-4 , w2, h2, _bc);
  _tft->setFont(_font);
  _tft->setCursor(_text_x, _text_y);
  _tft->print(_text);
}

void Tft_txt::drawString(int x, int y, char *text) {
  int16_t x1, y1;
  uint16_t w, h;
  _tft->setTextWrap(false);
  _tft->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  switch (_alignment) {
    case LEFT:
      x1 = x;
      break;
    case CENTER:
      x1 = x - w / 2;
      break;
    case RIGHT:
      x1 = x - w;
      break;
  }
  if (_tc != _bc) {
    _tft->fillRect(x1, y - h -1, w + 1, h + 1, _bc);
  }
  _tft->setCursor(x1, y);
  _tft->print(text);
}

void Tft_txt::drawString(int x, int y, const String & text) {
  char buf[text.length()+2];
  text.toCharArray(buf, text.length() + 1);
  drawString(x, y, buf);
}

void Tft_txt::canvas_create(int16_t x, int16_t y, int16_t w, int16_t h){
  _canvas_x   = x;
  _canvas_y   = y;
  _canvas_w   = w;
  _canvas_h   = h;
  _text_y   = _canvas_h-2;
  _canvas   = new GFXcanvas1(_canvas_w, _canvas_h);
}
void Tft_txt::canvas_pos(int16_t x, int16_t y, int16_t w, int16_t h){
  _canvas_x   = x;
  _canvas_y   = y;
  _canvas_w   = w;
  _canvas_h   = h;
}
void Tft_txt::canvas_display() {
  _tft->drawBitmap(_canvas_x, _canvas_y, _canvas->getBuffer(), _canvas_w, _canvas_h, _tc , _bc);  
  _canvas->fillScreen(ILI9341_BLACK);
  _canvas->setFont(_font);
  _canvas->setCursor(_text_x,  _text_y);
  _canvas->print(_text);
}
void Tft_txt::canvas_update() {
  this->_canvas->fillScreen(ILI9341_BLACK);
  this->_canvas->setCursor(_canvas_x,  _canvas_h-2);
  this->_canvas->print(_text);
}

void Tft_txt::u8g2_setup() {
  _u8g2.setFontMode(_u8g2_mod);                   
  _u8g2.setFontDirection(_u8g2_dir);                    
  _u8g2.setFont(_u8g2_font);                    
  if(_u8g2_mod==0)_u8g2.setBackgroundColor(_bc);                    
  _u8g2.setForegroundColor(_tc);                    
}
  
  
void Tft_txt::u8g2_mod(uint8_t v) {
  _u8g2_mod = v;
}
void Tft_txt::u8g2_dir(uint8_t v) {
  _u8g2_dir = v;
}
void Tft_txt::u8g2_font(const uint8_t * f) {
  _u8g2_font = f;
}

void Tft_txt::u8g2_setup(const String & v, uint16_t tc, uint16_t bc, const uint8_t * f) {
  _u8g2_font = f;
  _u8g2.setFont(f); 

  _u8g2_mod = 0;
  _u8g2.setFontMode(_u8g2_mod);

  _bc = bc;
  _u8g2.setBackgroundColor(bc); 

  _tc = tc;
  _u8g2.setForegroundColor(tc);

  _u8g2.setFontDirection(_u8g2_dir);   

  _text = v;                        

}

void Tft_txt::u8g2_drawR(const int16_t & marge, int16_t x, const int16_t & y, const String & v, uint16_t tc, uint16_t bc, const uint8_t * f) {
  u8g2_setup(v, tc, bc, f);               

  int16_t sW, sH;
  u8g2_get_wh(v, sW, sH);

  x = (_tft->width() - (sW + marge)) ;
  _text_x = x;
  _text_y = y;
  _u8g2.setCursor(x,y);  

  _u8g2.print(v); 
}
void Tft_txt::u8g2_drawC(int16_t x, const int16_t & maxW, const int16_t & y, const String & v, uint16_t tc, uint16_t bc, const uint8_t * f) {

  u8g2_setup(v, tc, bc, f);               

  int16_t sW, sH;
  u8g2_get_wh(v, sW, sH);

  uint8_t sx = (maxW/2) - (sW/2);
  _text_x = x + sx;
  _text_y = y;
  _u8g2.setCursor(_text_x,_text_y); 

  _text = v;                        
  _u8g2.print(v); 
}
void Tft_txt::u8g2_drawC(int16_t x,  const int16_t & y, const String & v, uint16_t tc, uint16_t bc, const uint8_t * f) {

  u8g2_setup(v, tc, bc, f);               

  int16_t sW, sH;
  u8g2_get_wh(v, sW, sH);

  x = (_tft->width()/2) - (sW/2);
  _text_x = x;
  _text_y = y;
  _u8g2.setCursor(x,y); 

  _text = v;                        
  _u8g2.print(v); 
}
void Tft_txt::u8g2_draw( const int16_t & x,  const int16_t & y, const String & v, uint16_t tc, uint16_t bc, const uint8_t * f) {
  _u8g2_font = f;
  _u8g2.setFont(f); 

  _u8g2_mod = 0;
  _u8g2.setFontMode(_u8g2_mod);

  _bc = bc;
  _u8g2.setBackgroundColor(bc); 

  _tc = tc;
  _u8g2.setForegroundColor(tc);

  _u8g2.setFontDirection(_u8g2_dir);                    

  _text_x = x;
  _text_y = y;
  _u8g2.setCursor(x,y);  

  _text = v;                        
  _u8g2.print(v); 
}
void Tft_txt::u8g2_draw(const int16_t & x,  const int16_t & y, const String & v, uint16_t tc, const uint8_t * f) {
  _u8g2_font = f;
  _u8g2.setFont(f);

  _u8g2_mod = 1;
  _u8g2.setFontMode(_u8g2_mod);

  _tc = tc;
  _u8g2.setForegroundColor(tc); 
  
  _u8g2.setFontDirection(_u8g2_dir);                    

  _text_x = x;
  _text_y = y;  
  _u8g2.setCursor(x,y);   

  _text = v;                
  _u8g2.print(v); 
} 
void Tft_txt::u8g2_draw(const int16_t & x,  const int16_t & y, const String & v) {
  _text     = v;                
  _text_x   = x;
  _text_y   = y;  
  _u8g2.setCursor(x,y);                   
  _u8g2.print(v); 
}
void Tft_txt::u8g2_draw(const String & v) {
  _u8g2.setCursor(_text_x, _text_y);   
  _text = v;                
  _u8g2.print(_text); 
}
void Tft_txt::u8g2_draw() {
  _u8g2.setCursor(_text_x, _text_y);                    
  _u8g2.print(_text); 
}

void Tft_txt::u8g2_drawRect(){
  char buffer_text[100];
  sprintf(buffer_text, "%s", _text.c_str());
  int16_t width = _u8g2.getUTF8Width(buffer_text);
  int16_t height = _u8g2.getFontAscent() - _u8g2.getFontDescent();
  _text_w = width;
  _text_h = height;
  _tft->fillRect(_text_x, _text_y-_u8g2.getFontAscent()-1, width, height+2, _bc); 
}
void Tft_txt::u8g2_drawRect(const int16_t & h,  int16_t w){
  u8g2_setup();
  char buffer_text[100];
  sprintf(buffer_text, "%s", _text.c_str());
  int16_t width   = _u8g2.getUTF8Width(buffer_text);
  int16_t height  = _u8g2.getFontAscent() - _u8g2.getFontDescent();
  if (w<width)w = width;
  _tft->fillRect(_text_x, _text_y-_u8g2.getFontAscent()-3, w+5, height+6, _bc); 
  u8g2_draw(_text);
}
void Tft_txt::u8g2_drawRect(const String & v){
  // char buffer_text[100];
  u8g2_drawRect();
  _text = v;
  u8g2_drawRect();
  u8g2_draw(v);
}
void Tft_txt::u8g2_drawRect(const String & v, int16_t x, int16_t y){
  char buffer_text[100];
  sprintf(buffer_text, "%s", v.c_str());
  int16_t width   = _u8g2.getUTF8Width(buffer_text);
  int16_t height  = _u8g2.getFontAscent() - _u8g2.getFontDescent();

  if ((x != _text_x) || (y > _text_y)) {
    u8g2_drawRect();   
    _text_x = x;    
    _text_y = y;    
    u8g2_setup();             
  } 
  if ((width > _text_w) || (height > _text_h)) {
    _text = v;    
    u8g2_setup();             
  }

  u8g2_drawRect();
  u8g2_draw(v);
}
void Tft_txt::u8g2_get_wh(int16_t & w, int16_t & h){
  char buffer_text[100];
  sprintf(buffer_text, "%s", _text.c_str());
  int16_t width   = _u8g2.getUTF8Width(buffer_text);
  int16_t height  = _u8g2.getFontAscent() - _u8g2.getFontDescent();
  w = width;
  h = height;
}
void Tft_txt::u8g2_get_wh(const String & txt, int16_t & w, int16_t & h){
  char buffer_text[100];
  sprintf(buffer_text, "%s", txt.c_str());
  int16_t width   = _u8g2.getUTF8Width(buffer_text);
  int16_t height  = _u8g2.getFontAscent() - _u8g2.getFontDescent();
  w = width;
  h = height;
}










/*
// You need to free the char!
char* MiniGrafx::utf8ascii(String str) {
  uint16_t k = 0;
  uint16_t length = str.length() + 1;

  // Copy the string into a char array
  char* s = (char*) malloc(length * sizeof(char));
  if(!s) {
    //DEBUG_OLEDDISPLAY("[OLEDDISPLAY][utf8ascii] Can't allocate another char array. Drop support for UTF-8.\n");
    return (char*) str.c_str();
  }
  str.toCharArray(s, length);

  length--;

  for (uint16_t i=0; i < length; i++) {
    char c = utf8ascii(s[i]);
    if (c!=0) {
      s[k++]=c;
    }
  }

  s[k]=0;

  // This will leak 's' be sure to free it in the calling function.
  return s;
}

void MiniGrafx::drawStringMaxWidth(int16_t xMove, int16_t yMove, uint16_t maxLineWidth, String strUser) {
  uint16_t firstChar  = readFontData(fontData, FIRST_CHAR_POS);
  uint16_t lineHeight = readFontData(fontData, HEIGHT_POS);

  char* text = utf8ascii(strUser);

  uint16_t length = strlen(text);
  uint16_t lastDrawnPos = 0;
  uint16_t lineNumber = 0;
  uint16_t strWidth = 0;

  uint16_t preferredBreakpoint = 0;
  uint16_t widthAtBreakpoint = 0;

  for (uint16_t i = 0; i < length; i++) {
    strWidth += readFontData(fontData, JUMPTABLE_START + (text[i] - firstChar) * JUMPTABLE_BYTES + JUMPTABLE_WIDTH);

    // Always try to break on a space or dash
    if (text[i] == ' ' || text[i]== '-' || text[i] == '\n') {
      preferredBreakpoint = i;
      widthAtBreakpoint = strWidth;
    }

    if (strWidth >= maxLineWidth || text[i] == '\n') {
      if (preferredBreakpoint == 0) {
        preferredBreakpoint = i;
        widthAtBreakpoint = strWidth;
      }
      drawStringInternal(xMove, yMove + (lineNumber++) * lineHeight , &text[lastDrawnPos], preferredBreakpoint - lastDrawnPos, widthAtBreakpoint);
      lastDrawnPos = preferredBreakpoint + 1;
      // It is possible that we did not draw all letters to i so we need
      // to account for the width of the chars from `i - preferredBreakpoint`
      // by calculating the width we did not draw yet.
      strWidth = strWidth - widthAtBreakpoint;
      preferredBreakpoint = 0;
    }
  }

  // Draw last part if needed
  if (lastDrawnPos < length) {
    drawStringInternal(xMove, yMove + lineNumber * lineHeight , &text[lastDrawnPos], length - lastDrawnPos, getStringWidth(&text[lastDrawnPos], length - lastDrawnPos));
  }

  free(text);
}

*/



/*
void setReadyForBotPanelUpdate() {
  Serial.println("Setting readyForBotPanelUpdate to true");
  readyForBotPanelUpdate = true;
}

// Routine to perform word-wrap display of text string
byte Tft_txt::stringWordWrap(String displayString, byte headerLines, TextAlignment txtAlign, bool truncFlag, int yBase, int maxPanelLines) {
  // The approach in this routine is as follows:
  //    1) Estimate the possible number of chars that can be displayed per line with the
  //       current font.  This is done by first calculating the width in pixels of a 10-character
  //       sample string using the current font.
  //    2) Divide the maximum pixels per line by the average pixel width/char.
  //    3) Now begin scanning the display string starting at the maximum character position per line,
  //       moving backwards from there looking for the first space or ellipse sequence.  If either is found,
  //       then this is an acceptable place to break the line, so display it.
  //    4) Otherwise, keep moving backwards until either is found; break there and display the
  //       segment.
  //    5) Rinse and repeat starting with the character following the break, through the end of
  //       the display string.
  //    6) Of course, need to handle null strings and lines with no break-points (break anyway).
  //    7) The routine keeps track of the number of lines in order to display multiple panels if
  //       required.  It will delay between panels using the default timing used for the bottom
  //       panel.
  // 
  //    The routine will return the count of panels displayed (which can be/is used to determine if
  //    additional panel delays are required.  An optional parameter can be passed to indicate a
  //    number of header lines already printed in the frame to word-wrap.
  //
  //    Added additional optional parameter to set the text alignment to other than the default LEFT.
  //      Added by DK Fowler ... 22-Mar-2017
  //
  //    Modified initial sanitation of the source string to loop until all instances of multiple spaces
  //    are removed.
  //      Modified by DK Fowler ... 22-Mar-2017
  //
  //    Modified routine to added additional optional parameter used to indicate if the passed message string
  //    had been truncated.  This will cause a truncation flag to be displayed following the end of the text.
  //    This is primarily used for the display of weather alerts, which can be truncated due to the fact that
  //    the streaming JSON parser only allocated 512-bytes for each message maximum.  The truncation flag
  //    is now displayed in this routine (vs. in the calling weather-alert routine as it was originally).  This
  //    allows correct delaying at the end of the final display panel.
  //      Modified by DK Fowler ... 08-Apr-2017
  //
  //    Modified routine to allow passing optional parameters to specify the starting vertical display position (yBase)
  //    and maximum panel lines to display for a panel (maxPanelLines).  These were previously hard-coded based on the
  //    original bottom panel position.  They were added as parameters to allow more flexibility in using the routine
  //    to display string-wrapped panels in other screeen regions (such as the forecast panels added for the touch
  //    screen functionality).
  //      Modified by DK Fowler ... 23-Jan-2018
   
  char sampleString[] = "aaaaaaaaaa";  // Adjust sample string as appropriate based on type of typical data
  char testString[50];
  int16_t x1, y1;
  uint16_t w, h, x, y;
  int breakLocation, spaceBreakLocation, ellipseBreakLocation;
  // int xBase, yBase = 245,           // Removed yBase 23-Jan-2018, DKF; now passed as an optional parameter
  // int xBase, xPos = 0, yPos = 245;  // Removed initialization here for yPos, 23-Jan-2018; now initialized based on passed optional parameter yBase.
  int xBase, xPos = 0, yPos;           // Added 03/22/17 DKF to allow more options for initial positioning of text
  // byte maxPanelLines = 6;           // Default maximum panel lines; adjust for font-size changes; removed 23-Jan-2018, DKF; now passed as an optional parameter
  byte lineCnt = 0;                    // Used to track number of lines displayed for this panel
  bool resetTickerFlag = false;
  bool lastPanelDelay = false;         // Added 04/08/17 DKF to indicate a delay is required after display of last display panel
  byte panelCnt = 0;

  // Initialize the starting position yPos based on the passed optional parameter yBase.
  //    Added by DK Fowler ... 23-Jan-2018
  yPos = yBase;
  
  // debug
  long      startExecutionMillis = 0,
            endExecutionMillis = 0,
            executionMillis = 0;

  startExecutionMillis = millis();
  
//  Serial.println("*** stringWordWrap called ***");
  if (displayString == "") return 0;     // Just return and do nothing if the passed display line is null.

// Modified following 22-Mar-2017 to loop until all multiple spaces are removed from the sources string
  while (displayString.indexOf("  ") != -1 ) {
    displayString.replace("  "," ");     // Replace all instances of multiple spaces with one space.
  }
  
  x = 0; y = 20;                       // Sample coordinates used to calculate the max chars per line.
  _tft->getTextBounds(sampleString, x, y, &x1, &y1, &w, &h);
  float pixelsChar = w/10;            // 10 characters in the sample string.
//  Serial.print("Sample string width (pixels):  "); Serial.println(w);
//  Serial.print("Average number of pixels/char (w):  "); Serial.println(pixelsChar,3);

  int charsPerLine = (240 / pixelsChar) - 1;
  int estBreak = charsPerLine;
  int beginLineIndex = 0;

  if (headerLines !=0) {
    lineCnt = headerLines;                         // Added 1-Feb-2017 DKF to handle overflow on text forecast with header line
    yPos = yPos + (headerLines * (h + 6));         // Added 22-Mar-2017 DKF to allow specifying optional different alignments
  } else {
    yPos = yPos + 1;
  }
// Serial.print("*** stringWordWrap...alignment passed = "); Serial.println(txtAlign);
  switch (txtAlign) {                               // Added 22-Mar-2017 DKF to allow specifying optional different alignment than left-justified
    case LEFT:
      textAlignment(LEFT);
      xBase = 0;
      break;
    case RIGHT:
      textAlignment(RIGHT);
      xBase = ILI9341_TFTWIDTH;
      break;
    case CENTER:
      textAlignment(CENTER);
      xBase = ILI9341_TFTWIDTH / 2;
      break;
  }    

  int displayStringLen = displayString.length();
//  Serial.println("***Beginning word wrap of passed string***");
//  Serial.print("Length of passed string:  "); Serial.println(displayStringLen);
//  Serial.print("Calc chars / line:  "); Serial.println(charsPerLine);
  while (estBreak < displayStringLen) {
    // Search backwards from the estimated line break for the first space or "..." sequence
//    Serial.print("Beginning line index:  "); Serial.println(beginLineIndex);
//    Serial.print("Estimated break location:  "); Serial.println(estBreak);
    spaceBreakLocation = (displayString.substring(beginLineIndex,estBreak)).lastIndexOf(" ",estBreak);
    ellipseBreakLocation = (displayString.substring(beginLineIndex,estBreak)).lastIndexOf("...",estBreak)+2;
    // set the break location at the greater of where a space is found or an ellipse sequence
    if (spaceBreakLocation >= ellipseBreakLocation) {
      breakLocation = spaceBreakLocation;
    } else {
      breakLocation = ellipseBreakLocation;
    }
//    Serial.print("Found break location at character:  "); Serial.println(breakLocation);
    // If no space is found in the line segment, force a break at the max chars / line position.
    if (breakLocation == -1) {
      breakLocation = estBreak;
    } else {
      breakLocation = breakLocation + beginLineIndex;
    }
    // Added following logic to test the line to be displayed to make sure it will fit on the display
    // without wrapping.  This was to correct certain rare situations where the combination of certain
    // "wide" characters (such as "W") would cause the line to be too long to fit.
    //    Added by DK Fowler ... 17-Mar-2017
    displayString.substring(beginLineIndex,breakLocation).toCharArray(testString, (breakLocation-beginLineIndex));
    _tft->getTextBounds(testString, x, y, &x1, &y1, &w, &h);
    if (w >= 239) { // max display width; may add logic to get this from the driver in the future vs. hard-coding
      estBreak--;   // decrement the line break estimation and try again...
    } else {
//      _tft->println(displayString.substring(beginLineIndex,breakLocation));
      drawString(xBase, yPos, displayString.substring(beginLineIndex,breakLocation) );
      lineCnt++;
      yPos = yPos + h + 3;
      if (lineCnt >= maxPanelLines) {
        panelCnt++;
        lineCnt = 0;
        yPos = yBase + 1;
        // temporarily detach the bottom panel ticker since we're going to control display
        // of the variable number of message panels in this routine
        botPanelTicker.detach();
        // debug...
        Serial.println("*** stringWordWrap delaying for panel-break view... ***");
        // delayAndCheckTouch(UPDATE_BOT_PANEL_INTERVAL_SECS * 1000);
        // delay(UPDATE_BOT_PANEL_INTERVAL_SECS * 1000);
        Serial.print("stringWordWrap panel-break delay:  time(ms):  "); Serial.println(millis());        
        resetTickerFlag = true;            // flag that the ticker needs to be reattached
        // debug
        // ui.drawString(10, 160, "xBase = " + String(xBase) );
        // ui.drawString(10, 174, "yPos  = " + String(yPos) );
        // delay(2000);
        
        _tft->setCursor(xBase,yPos);         // reset cursor to top of panel
        _tft->fillRect(0, 233, 240, 87, ILI9341_BLACK);   // clear panel for next display
      }
//    Serial.print("["); Serial.print(displayString.substring(beginLineIndex,breakLocation)); Serial.println("]");
      beginLineIndex = breakLocation + 1;
      estBreak = breakLocation + charsPerLine; 
    }  
  }
  if (estBreak >= displayStringLen) {
    //  Display the last string segment
    //    Modified 11-Mar-2018...DK Fowler
    //  Modified the following code to add the truncation indicator to the last display string segment, where applicable.  This can occur 
    //  since the JSON parser only returns the first 512 characters.  This change allows for a "cleaner" display string, as previously, 
    //  it was likely that the last character(s) would be overwritten by the truncation indicator.
    String lastStringSeg = displayString.substring(beginLineIndex);
    if (truncFlag) {
      lastStringSeg = lastStringSeg + "<...>";
    }
    drawString(xBase, yPos, lastStringSeg);
    //lastStringSeg.toCharArray(testString, (lastStringSeg.length()));
    //_tft->getTextBounds(testString, xPos, yPos, &x1, &y1, &w, &h);
    //xPos = xPos + w;
    //_tft->setCursor(xPos, yPos);
    lastPanelDelay = true;
    panelCnt++;               // Added 5-Mar-2018, DKF, to correct bug in returning correct panel count
  }  
//    Serial.print("["); Serial.print(displayString.substring(beginLineIndex)); Serial.println("]");
  if (resetTickerFlag) {
  // First, check to see if a last delay is required for the display of the remaining panel.  This situation could arise rarely
  // when the last string segment to be displayed is at the beginning of a new panel.
  //    Added 04/08/17...DK Fowler
    if (lastPanelDelay) {
      // debug...
      Serial.println("*** stringWordWrap delaying for last panel-break view... ***");
      // delayAndCheckTouch(UPDATE_BOT_PANEL_INTERVAL_SECS * 1000);
      // delay(UPDATE_BOT_PANEL_INTERVAL_SECS * 1000);
      Serial.print("stringWordWrap panel-break delay:  time(ms):  "); Serial.println(millis());        
    }
  // reattach ticker for bottom panel update
    botPanelTicker.attach(UPDATE_BOT_PANEL_INTERVAL_SECS, setReadyForBotPanelUpdate); // To trigger updating bottom-panel on screen
    // force a bottom panel update to get back in sync with the ticker
    readyForBotPanelUpdate = true;
    Serial.print("stringWordWrap reset bot ticker:  time(ms):  "); Serial.println(millis());
  }

// debug
endExecutionMillis = millis();
executionMillis = endExecutionMillis - startExecutionMillis;
Serial.print("*** stringWordWrap execution time:  "); Serial.println(executionMillis);

return panelCnt;
} 
*/