#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#include "R2_pins.h"
#include "R2_menu.h"
#include "R2_settings.h"
#include "R2_sd.h"
#include "R2_motors.h"
#include "R2_print.h"

int workCase=0;

void setup() {
  pinsSetup();
  mallocListFiles(20);
  listFiles(root);
  //makeFilesCharList();
}


void loop() {
  
  switch(workCase){
  case 0:                      //WIADOMOŚĆ STARTOWA
    if (lcdPrint01() == 1) workCase=1;
    break;
    
  case 1:                      //WIADOMOSC STARTOWA 2
    if (lcdPrint02() == 1) {
      workCase=2;
      clLcd=1;
    }
    break;
    
    case 2:                    //Glowne MENU 
      if( printMenu(mainMenu, &currentMainMenu, numMainMenu) == 1){
         //Serial.print(currentMainMenu);
         clLcd=1;
         switch(currentMainMenu){
          case 0:
            workCase=5;
          break;
         
          case 1:
            workCase=91;
          break;
         
          case 2:
            workCase=4;
          break;
         
          case 3:
            workCase=3;
          break;
          
          case 4:
            workCase=22;
          break;
              
         }
      }
    break;
    case 22:
      if( printMenu(tutorialMenu, &currentSecondMenu, numTutorial) == 1){
        clLcd=1;
        if(currentSecondMenu == 0){
           currentMainMenu=0;
           currentSecondMenu=0;
           workCase=2;
        }
      }
    break;
    case 3:                    //WYPISYWANIE AUTOROW
      if( printMenu(autorzyMenu, &currentSecondMenu, numAutorzyMenu) == 1){
        clLcd=1;
        if(currentSecondMenu == 0){
           currentMainMenu=0;
           currentSecondMenu=0;
           workCase=2;
        }
      }
    break;
    
    case 4:
      if( printMenu(sdFileList, &curNumOfFiles, numOfFiles+1) == 1){
        clLcd=1;
        if(curNumOfFiles > 0){
          mainFile = sdFileList[curNumOfFiles]; 
          Serial.print(mainFile);
        }
        currentMainMenu=0;
        currentSecondMenu=0;
        workCase=2;
      }
    break;
    case 5:
      if(mainFile){
        int val = loadBitmap(mainFile);
        if(val == 1){
          if (lcdPrint04() == 1) {
            workCase=2;
            clLcd=1;
          }
        }
        else if (val == 2){
          if (lcdPrint05() == 1) {
            workCase=2;
            clLcd=1;
          }
        }
        else
          workCase=6;
      }
      else{
        if (lcdPrint03() == 1) {
          workCase=2;
          clLcd=1;
        }
      }
    break;
    case 6:
      //calibrate();
      printImage();
      
      workCase=2;
      clLcd=1;
    break;
    
    case 91:
      if( printMenu(opcjeMenu, &currentSecondMenu, numOpcjeMenu) == 1){
        clLcd=1;
        delay(100);
        switch(currentSecondMenu){
           case 0:
             currentMainMenu=0;
             currentSecondMenu=0;
             workCase=2;
           break;
           case 1:
             setSettings((char*)"Szerokosc [mm]",&width,minW,maxW,0.5);
             while(!digitalRead(eClick));
             clLcd=1;
           break;
           case 2:
             setSettings((char*)"Wysokosc [mm]",&height,minH,maxH,0.5);
             while(!digitalRead(eClick));
             clLcd=1;
           break;
           case 3:
             setSettings((char*)"Predkosc X[mm/s]",&speedX,minSX,maxSX,0.5);
             while(!digitalRead(eClick));
             clLcd=1;
           break;
           case 4:
             setSettings((char*)"Predkosc YX[mm/s]",&speedY,minSY,maxSY,0.5);
             while(!digitalRead(eClick));
             clLcd=1;
           break;
           case 5:
             setSettings((char*)"Grubosc [mm]",&thickness,minT,maxT,0.1);
             while(!digitalRead(eClick));
             clLcd=1;
           break;
        }
      }
    break;
  }
}




