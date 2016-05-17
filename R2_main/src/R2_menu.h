#ifndef R2_MENU
#define R2_MENU

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "R2_pins.h"

extern int clLcd;
extern const int numMainMenu;
extern const int numAutorzyMenu;
extern char *mainMenu[6];
extern char *autorzyMenu[7];
extern char *tutorialMenu[20];
extern char *opcjeMenu[6];
extern const int numOpcjeMenu;
extern const int numTutorial;
extern int currentMainMenu;
extern int currentSecondMenu;
extern int eLast;



//Czyści LCD
void clearLcd();
//Zwraca wartość enkodera 1: lewo, 2:prawo, 3:click, 4:lewo+click, 5:prawo+click
int encoder();
int lcdPrint01();
int lcdPrint02();
int lcdPrint03();
int lcdPrint04();
int lcdPrint05();
int printMenu(char *tab[], int *curr, int maxM);
int setWidth();

#endif
