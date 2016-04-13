#include "R2_pins.hpp"

LiquidCrystal lcd(23, 22, 21, 20, 19, 18);
int ePinA = 26;
int ePinB = 25;
int eClick = 24;
int servPin = 15;
int motorXDir = 30;
int motorXStep = 31;
int motorYDir = 28;
int motorYStep = 29;
int endX = 0;
int endY = 1;

void pinsSetup(){
	pinMode (ePinA,INPUT); //Tryby pinów
	pinMode (ePinB,INPUT);
	pinMode (eClick,INPUT);
	digitalWrite(ePinA, HIGH); //Software pull-up
	digitalWrite(ePinB, HIGH);
	digitalWrite(eClick, HIGH);
	digitalWrite(endX, HIGH);
	digitalWrite(endY,HIGH);

	//Silniki musza sie obracac w dobra strone przy kalibracji
	digitalWrite(motorXDir,LOW);
	digitalWrite(motorYDir,LOW);

	Serial.begin (9600);
	lcd.begin(16, 2);    //16 znaków, 2 wiersze
	Serial.print("Initializing SD card...");
	pinMode(4, OUTPUT);
	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");
	root = SD.open("/");
	servo.attach(servPin);
}
