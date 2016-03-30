// include the library code:
#include <LiquidCrystal.h>

int workCase=0;
int lcdCase=0;
int clLcd=0;
const int liczbaOpcji=4;
char *mainMenu[liczbaOpcji]={"START","OPCJE","WYBIERZ PLIK","AUTORZY"};
int currentMainMenu=0;

//PINY
LiquidCrystal lcd(23, 22, 21, 20, 19, 18); 
const int ePinA = 26;
const int ePinB = 25;
const int eClick = 24;


int eLast = 0;


void setup() {
  pinMode (ePinA,INPUT);      //Tryby pinów
  pinMode (ePinB,INPUT);
  pinMode (eClick,INPUT);
  digitalWrite(ePinA, HIGH);  //Software pull-up
  digitalWrite(ePinB, HIGH);
  digitalWrite(eClick, HIGH);
  Serial.begin (9600);        
  lcd.begin(16, 2);          //16 znaków, 2 wiersze
}

void clearLcd(){
  lcd.setCursor(0,0);
  lcd.print("                                        ");
  lcd.setCursor(0,1);
  lcd.print("                                        ");
  lcd.setCursor(0,0);   
}

//Zwraca wartość enkodera 1: lewo, 2:prawo, 3:click, 4:lewo+click, 5:prawo+click
int encoder(){
  int v = 0;
  int nA;
  int nB;
  int nC;
  nA = digitalRead(ePinA);    // Read encoder pins
  nB = digitalRead(ePinB);
  nC = digitalRead(eClick);
    
  if ((eLast) && (!nA)) { 
    if (nB) v+=1;
    else v+=2;
  }
  eLast = nA;
  if(!nC) v+=3;
  return v;
}


void loop() {
  switch(workCase){
  case 0:                      //WIADOMOŚĆ STARTOWA
    lcd.setCursor(0,0);
    lcd.print("R2 PRINT-2 :)");
    lcd.setCursor(0,1);
    lcd.print("Click to start");
    if(!digitalRead(eClick)) {
      clLcd=1;
      workCase=1;
    }
    break;
  case 1:                      //WIADOMOSC STARTOWA 2
    if (clLcd){ 
      clearLcd();
      clLcd=0;
      lcd.setCursor(0,0);
      lcd.print("Witaj w menu");
      lcd.setCursor(0,1);
      lcd.print("Uzyj enkodera!");
      delay(300);
    }
    if(encoder()>0){
      workCase=2;
      clLcd=1;
    }    
    break;
    case 2:
      if(clLcd){
        clearLcd();
        lcd.setCursor(0,0);
        lcd.print("> ");
        lcd.print(mainMenu[currentMainMenu]);      
        lcd.setCursor(0,1);
        lcd.print(mainMenu[(currentMainMenu+1)%liczbaOpcji]);
        clLcd=0;
      }
      int e = encoder();
      switch(e){
         case 1:
           currentMainMenu = (currentMainMenu-1)%liczbaOpcji;
           if(currentMainMenu<0) currentMainMenu=liczbaOpcji-1;
           clLcd=1;
         break;
         case 2:
           currentMainMenu = (currentMainMenu+1)%liczbaOpcji;
           clLcd=1;
         break;
         case 3:
         break; 
      }
    break; 
  }

  
    
}

