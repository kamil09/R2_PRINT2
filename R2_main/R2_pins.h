#pragma once

LiquidCrystal lcd(23, 22, 21, 20, 19, 18);
const int ePinA = 26;
const int ePinB = 25;
const int eClick = 24;

File root;

void pinsSetup(){
  pinMode (ePinA,INPUT);      //Tryby pinów
  pinMode (ePinB,INPUT);
  pinMode (eClick,INPUT);
  digitalWrite(ePinA, HIGH);  //Software pull-up
  digitalWrite(ePinB, HIGH);
  digitalWrite(eClick, HIGH);
  Serial.begin (9600);
  lcd.begin(16, 2);          //16 znaków, 2 wiersze
  Serial.print("Initializing SD card...");
  pinMode(4, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  root = SD.open("/");
}
