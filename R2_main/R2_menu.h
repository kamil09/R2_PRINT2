#pragma once

extern int clLcd=0;
extern const int numMainMenu=4;
extern const int numAutorzyMenu=7;
extern char *mainMenu[4]={"START","OPCJE","WYBIERZ PLIK","AUTORZY"};
extern char *autorzyMenu[7]={"<< POWROT <<","Kamil Piotrowski","Michal Lewinski","Pawal Kaczmarek","Rafal Wilinski","Szymon Melewski","Tymoteusz Kupcewicz"};
extern int currentMainMenu=0;
extern int currentSecondMenu=0;
extern int eLast = 0;



//Czyści LCD
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

int lcdPrint01(){
  lcd.setCursor(0,0);
  lcd.print("R2 PRINT-2 :)");
  lcd.setCursor(0,1);
  lcd.print("Click to start");
  if(!digitalRead(eClick)) {
      clLcd=1;
      return 1;
    }
  return 0;
}
int lcdPrint02(){
  if (clLcd){
      clearLcd();
      clLcd=0;
      lcd.setCursor(0,0);
      lcd.print("Witaj w menu");
      lcd.setCursor(0,1);
      lcd.print("Uzyj enkodera!");
      delay(300);
    }
  if(encoder()>0) return 1;
  return 0;
}

int lcdPrint03(){
  if (clLcd){
      clearLcd();
      clLcd=0;
      lcd.setCursor(0,0);
      lcd.print("Oj, cos nie dziala");
      lcd.setCursor(0,1);
      lcd.print("NIE WYBRANO PLIKU!");
      delay(300);
    }
  if(encoder()>0) return 1;
  return 0;
}

int lcdPrint04(){
  if (clLcd){
      clearLcd();
      clLcd=0;
      lcd.setCursor(0,0);
      lcd.print("Blad podczas");
      lcd.setCursor(0,1);
      lcd.print("analizy pliku!");
      delay(300);
    }
  if(encoder()>0) return 1;
  return 0;
}

int printMenu(char *tab[], int *curr, int maxM){
   if(clLcd){
    clearLcd();
    lcd.setCursor(0,0);
    lcd.print("> ");
    lcd.print(tab[*curr]);
    lcd.setCursor(0,1);
    lcd.print(tab[(*curr+1)%maxM]);
    clLcd=0;
    delay(500);
  }
  int e = encoder();
  switch(e){
     case 1:
       *curr = (*curr-1)%maxM;
       if(*curr<0) *curr=maxM-1;
       clLcd=1;
     break;
     case 2:
       *curr = (*curr+1)%maxM;
       clLcd=1;
     break;
     case 3:
       return 1;
     break;
  }
  return 0;
}



