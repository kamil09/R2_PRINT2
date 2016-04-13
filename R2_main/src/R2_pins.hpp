#ifndef R2_pins
#define R2_pins

#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

extern LiquidCrystal lcd;
extern const int ePinA;
extern const int ePinB;
extern const int eClick;
extern const int servPin;
extern const int motorXDir;
extern const int motorXStep;
extern const int motorYDir;
extern const int motorYStep;
extern const int endX;
extern const int endY;

static File root;
static Servo servo;

void pinsSetup();

#endif
