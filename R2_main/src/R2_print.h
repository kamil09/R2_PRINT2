#ifndef MAIN_LIB
	#define MAIN_LIB
	#include <Arduino.h>
	#include <Wire.h>
	#include <LiquidCrystal.h>
	#include <SPI.h>
	#include <SD.h>
	#include <Servo.h>
#endif
#ifndef R2_PINS
	#define R2_PINS
	#include "R2_pins.h"
#endif
#ifndef R2_MENU
	#define R2_MENU
	#include "R2_menu.h"
#endif
#ifndef R2_SETTINGS
	#define R2_SETTINGS
	#include "R2_settings.h"
#endif
#ifndef R2_SD
	#define R2_SD
	#include "R2_sd.h"
#endif
#ifndef R2_MOTOR
	#define R2_MOTOR
	#include "R2_motors.h"
#endif


int printImage(){
	int t=0;
	int i;
	int k=0;
	int mm=0;
	pixelMm();
	clearLcd();
	lcd.setCursor(0,0);
	lcd.print("Trwa drukowanie");

	for(i=0; i<picHeight; i++) {
		lcd.setCursor(0,1);
		lcd.print((loadedBytes/loadedFileSize)*100);
		lcd.print(" %                                 ");
		t=linia();
		wypisywanie(t);
		if(strona==0) {
			for (k=0; k<=t; k++) {
				if (tablicaRys[k]==0) {
					break;
				}
				if(tablicaRys[k] < 0) {
					servoUp();
				}
				else
				if(tablicaRys[k] > 0) {
					servoDown();
				}
				//PRZELICZ na mm
				//PRZESUN SILNIK NA OSI X
				mm=abs(tablicaRys[k])*lineWidth;
				moveMotorX(mm/stepsXPerMm);
			}
		}else{
			for (k=t; k>=0; k--) {
				if (tablicaRys[k]==0) {
					continue;
				}
				if(tablicaRys[k] < 0) {
					servoUp();
				}
				else
				if(tablicaRys[k] > 0) {
					servoDown();
				}
				//PRZELICZ na mm
				//PRZESUN SILNIK NA OSI X
				mm=abs(tablicaRys[k])*lineWidth;
				moveMotorX(mm/stepsXPerMm);
			}
		}
		//PRZESUN SILNIKI NA OSI Y
		moveMotorY(lineHeight/stepsYPerMm);
		strona = 1 - strona;
		free(tablicaRys);
	}
	return 0;
}
