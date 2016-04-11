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

char *mainFile;
char **sdFileList;

int numOfFiles=0;
int maxnumFiles=0;
int curNumOfFiles=0;
unsigned long time;
unsigned long time2;
int picWidth=0;
int picHeight=0;
int *tablicaRys;
File loadedFile;
float loadedFileSize=0;
float loadedBytes=0;

void mallocListFiles(int num){
	maxnumFiles=num;
	sdFileList=(char**)malloc(sizeof(char*)*num);
	sdFileList[0]=(char*)"<< POWROT <<";
}

void listFiles(File dir) {
	while(true) {
		File entry =  dir.openNextFile();
		if (!entry) break;
		Serial.print(entry.name());
		if (entry.isDirectory()) {
			//Serial.println("/");
			//listFiles(entry);
		} else {
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);

			char path[32];
			char *dirname=dir.name();
			strcpy(path,dir.name());
			if(dirname[0] != '/' )
				strcat(path, "/");
			strcat(path, entry.name());

			if(numOfFiles >= maxnumFiles-1) {
				sdFileList=(char**)realloc(sdFileList,sizeof(char*)*(maxnumFiles+10));
				maxnumFiles+=10;
				break;
			}
			sdFileList[numOfFiles+1] = (char*)malloc(sizeof(char)*32);
			strcpy(sdFileList[numOfFiles+1],path);
			//Serial.print(sdFileList[numOfFiles+1]);
			numOfFiles++;
		}
		entry.close();
	}
}

int ascii(){
	int c=loadedFile.read();
	int t=0;
	while(c!=-1 && c!=' ' && c!='\n') {
		t=t*10;
		t=t+(c-'0');
		c=loadedFile.read();
	}
	return t;
}

void zerowanie(int from,int to){
	int i;
	for(i=from; i<to; i++) {
		tablicaRys[i]=0;
	}
}
//Do testow
void wypisywanie(int w){
	int i;
	//Serial.println("wypisywanie tablicy\n");
	for(i=0; i<=w; i++) {
		Serial.print(tablicaRys[i]);
		Serial.print(" ");
	}
	Serial.println("");
}

int linia(){
	int c=loadedFile.read();
	loadedBytes++;
	int k=0;
	int w=0;
	int b=8;
	int i;
	tablicaRys=(int*)malloc(sizeof(int)*b);
	zerowanie(0,b);
	while(c!=-1) {
		for(i=7; i>=0; i--) {
			if(w==(b-1)) {
				b=b+8;
				tablicaRys=(int*)realloc(tablicaRys,sizeof(int)*b);
				zerowanie(w+1,b);
			}
			if((c & (1<<i))!=0) {
				if(tablicaRys[w]>=0) {
					tablicaRys[w]++;
				}
				else{
					w++;
					tablicaRys[w]++;
				}
			}
			else{
				if(tablicaRys[w]<=0) {
					tablicaRys[w]--;
				}
				else{
					w++;
					tablicaRys[w]--;
				}
			}
			k++;
			if(k==picWidth) {
				//k=0;
				return w;
			}
		}
		c=loadedFile.read();
		loadedBytes++;
	}
	return w;
}

int loadBitmap(char *file){
	loadedBytes=0;
	Serial.print(file);
	Serial.print("\n");
	loadedFile=SD.open(file);

	if(!loadedFile) return 1;
	loadedFileSize = loadedFile.size();
	clearLcd();
	clLcd=0;
	lcd.setCursor(0,0);
	lcd.print("Trwa analiza:");
	lcd.setCursor(0,1);
	lcd.print(file);
	time = millis();
	int c=0;
	if((c=loadedFile.read())!=80) {
		Serial.println("zly typ pliku");
		return 2;
	}
	if((c=loadedFile.read())!=52) {
		Serial.println("zly typ pliku");
		return 2;
	}
	loadedBytes+=2;
	c=loadedFile.read();
	do {
		c=loadedFile.read();
		loadedBytes++;
	} while(c!=-1 && c!='\n');
	picWidth=ascii();
	Serial.print("Szerokosc: ");
	Serial.println(picWidth);
	picHeight=ascii();
	Serial.print("Dlugosc: ");
	Serial.println(picHeight);

	//while(c!=-1){
	//c=loadedFile.read();
	//if(c=='\n') Serial.println("NOWA LINIA!");
	//else if(c==' ') Serial.println("SPACJA");
	//else {
	// Serial.print(" ");
	//Serial.print(c);
	// }
	//Serial.print("\n");
	//}

	time2 = millis();
	Serial.print("Koniec!");
	Serial.println(time);
	Serial.println(time2);
	lcd.setCursor(0,0);
	lcd.print("Analiza zakonczona");
	return 0;
}
