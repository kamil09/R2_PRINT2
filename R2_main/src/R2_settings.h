#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "R2_menu.hpp"


float width=100;    //mm
float height=150;
float speedX=50;    //mm per second
float speedY=2;
float thickness=0.5;

float minW = 50;
int maxW = 180;

float minH = 50;
int maxH = 270;

float minSX = 1;
int minSY = 1;

float maxSX = 60;
int maxSY = 3;

float minT = 0.2;
int maxT = 5;

int setSettings(char *text,float *val, float minV, int maxV, float krok){
	clearLcd();
	lcd.setCursor(0,0);
	lcd.print(text);
	int war=1;
	delay(100);
	while(war==1) {
		if (clLcd) {
			lcd.setCursor(0,1);
			lcd.print("                          ");
			lcd.setCursor(0,1);
			lcd.print(*val);
			clLcd=0;
		}

		int e = encoder();
		switch(e) {
		case 1:
			*val = *val-krok;
			if(*val<minV) *val=minV;
			clLcd=1;
			break;
		case 2:
			*val = *val+krok;
			if(*val>maxV) *val=maxV;
			clLcd=1;
			break;
		case 3:
			war=0;
			break;
		}
	}
	return 0;

}
