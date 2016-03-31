#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>

#include "R2_pins.h"
#include "R2_menu.h"
#include "R2_sd.h"

int workCase=0;

void setup() {
  pinsSetup();
  mallocListFiles(20);
  listFiles(root);
  makeFilesCharList();
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
          break;
         
          case 1:
          break;
         
          case 2:
            workCase=4;
          break;
         
          case 3:
            workCase=3;
          break; 
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
      if( printMenu(filesNames, &curNumOfFiles, numOfFiles-1) == 1){
        clLcd=1;
        if(curNumOfFiles > 0){
          mainFile = sdFileList[curNumOfFiles-1]; 
          Serial.print(mainFile.name());
        }
        currentMainMenu=0;
        currentSecondMenu=0;
        workCase=2;
      }
    break;
  }



}




