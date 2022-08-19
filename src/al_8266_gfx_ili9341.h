#ifndef AL_8266_GFX_ILI9341_H
#define AL_8266_GFX_ILI9341_H

#include "../include/tft.h"
#include "../include/tfttxt.h"
#include "../include/icons.h"
#include "../include/tftbutton.h"

#endif // AL_8266_GFX_ILI9341_H
/*

int wifiQuality_getBarsSignal(long rssi){
	// 5. High quality: 90% ~= -55db
	// 4. Good quality: 75% ~= -65db
	// 3. Medium quality: 50% ~= -75db
	// 2. Low quality: 30% ~= -85db
	// 1. Unusable quality: 8% ~= -96db
	// 0. No signal
  	int bars = 0;
  
	if (rssi > -55) { 
		bars = 4;
	} else if (rssi < -55 & rssi > -65) {
		bars = 4;
	} else if (rssi < -65 & rssi > -75) {
		bars = 3;
	} else if (rssi < -75 & rssi > -85) {
		bars = 2;
	} else if (rssi < -85 & rssi > -96) {
		bars = 1;
	} else {
		bars = 0;
	}
  	return bars;
} 

boolean wifi_icon_isDraw = false;
void screen_main_notifi_wifi(int x, int y){
	if (WiFi.status() != WL_CONNECTED)  {
		if(!wifi_icon_isDraw){
			for (int b=1; b <= 4; b++) tft.fillRect(x + (b*4),y - (b*4), 3, b*4, _color_home);
			wifi_icon_isDraw=true;
		}
		if (screen_main_notifi_hl) 	tft.drawBitmap(x, y-20, wifi25Bitmap, 25, 25, ui.color565(100, 0, 0));
		else 						tft.drawBitmap(x, y-20, wifi25Bitmap, 25, 25, _color_home);
	} else {
		long 	rssi = WiFi.RSSI();
		int 	bars = wifiQuality_getBarsSignal(rssi); 

		if (wifi_icon_isDraw) {
			tft.drawBitmap(x, y, wifi25Bitmap, 25, 25, _color_home);
			wifi_icon_isDraw=false;
		}		
		int cnt = 0;
		for (int b=0; b <= 4; b++) {
			if (cnt <= bars)  	tft.fillRect(x + (b*4),y - (b*4), 3, b*4, ui.color565(100, 100, 50)); 
			else 				tft.fillRect(x + (b*4),y - (b*4), 3, b*4, ui.color565(50, 50, 25)); 
			cnt++;
		}
	}
}

*/