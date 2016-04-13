#ifndef R2_pins
#define R2_pins

#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

extern LiquidCrystal lcd;
extern int ePinA;
extern int ePinB;
extern int eClick;
extern int servPin;
extern int motorXDir;
extern int motorXStep;
extern int motorYDir;
extern int motorYStep;
extern int endX;
extern int endY;

static File root;
static Servo servo;

void pinsSetup();

#endif
