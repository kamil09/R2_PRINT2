#ifndef R2_SET
#define R2_SET

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "R2_menu.h"


extern float width;    //mm
extern float height;
extern float speedX;    //mm per second
extern float speedY;
extern float thickness;

extern float minW;
extern int maxW;

extern float minH;
extern int maxH;

extern float minSX;
extern int minSY;

extern float maxSX;
extern int maxSY;

extern float minT;
extern int maxT;

int setSettings(char *text,float *val, float minV, int maxV, float krok);

#endif
