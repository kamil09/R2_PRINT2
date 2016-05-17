#ifndef R2_SD
#define R2_SD

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "R2_menu.h"
#include "R2_settings.h"

extern char *mainFile;
extern char **sdFileList;

extern int numOfFiles;
extern int maxnumFiles;
extern int curNumOfFiles;
extern unsigned long time;
extern unsigned long time2;
extern int picWidth;
extern int picHeight;
extern int *tablicaRys;
extern File loadedFile;
extern float loadedFileSize;
extern float loadedBytes;

void mallocListFiles(int num);

void listFiles(File dir);

int ascii();

void zerowanie(int from,int to);
//Do testow
void wypisywanie(int w);

int linia();

int loadBitmap(char *file);

#endif
