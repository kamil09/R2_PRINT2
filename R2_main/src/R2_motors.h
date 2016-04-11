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

int delayX=100;
int delayY=100;
float nowX=0;
float nowY=0;
//Liczba krokow silnika na 1mm
const int stepsXPerMm = 1;
const int stepsYPerMm = 1;
float lineWidth = 1;
float lineHeight = 1;
int pozycjaY = 0; // 0 - dlugopis podniesiony 1 - dlugopis opuszczony
int strona = 0; // 0 - lewa strona 1 - prawa strona

void servoDown(){
	if(pozycjaY==1) {
		return;
	}
	servo.writeMicroseconds(500);
	pozycjaY=1;
}
void servoUp(){
	if(pozycjaY==0) {
		return;
	}
	servo.writeMicroseconds(1500);
	pozycjaY=0;
}

void calibrate(){
	int t=0;
	Serial.println("Kalibruje");
	Serial.print("x: ");
	while(1) {
		t++;
		digitalWrite(motorXStep,HIGH);
		delayMicroseconds(delayX);
		digitalWrite(motorXStep,LOW);
		delayMicroseconds(delayX);
		if(digitalRead(endX)==0) {
			Serial.println(t);
			break;
		}
	}
	t=0;
	Serial.print("y: ");
	while(1) {
		t++;
		digitalWrite(motorYStep,HIGH);
		delayMicroseconds(delayY);
		digitalWrite(motorYStep,LOW);
		delayMicroseconds(delayY);
		if(digitalRead(endY)==0) {
			Serial.println(t);
			break;
		}
	}
	servoUp();
	nowX=0;
	nowY=0;
	strona=0;
}

void pixelMm(){
	lineWidth=width/picWidth; //ile milimetrow ma szerokosc 1 piksel
	lineHeight=height/picHeight;
}

void moveMotorX(int kroki){
	int i;
  //**********************NALEZY SPRAWDZIC**************************8
	if(strona==0) {
		digitalWrite(motorXDir,LOW);
	}
	else{
		digitalWrite(motorXDir,HIGH);
	}
	for(i=0; i<kroki; i++) {
		digitalWrite(motorXStep,HIGH);
		delayMicroseconds(delayX);
		digitalWrite(motorXStep,LOW);
		delayMicroseconds(delayX);
	}
}


void moveMotorY(int kroki){
	int i;
	for(i=0; i<kroki; i++) {
		digitalWrite(motorYStep,HIGH);
		delayMicroseconds(delayY);
		digitalWrite(motorYStep,LOW);
		delayMicroseconds(delayY);
	}
}
