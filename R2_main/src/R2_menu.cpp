#include "R2_menu.h"

int clLcd=0;
const int numMainMenu=6;
const int numAutorzyMenu=7;
char *mainMenu[6]={(char*)"START",(char*)"OPCJE",(char*)"WYBIERZ PLIK",(char*)"AUTORZY",(char*)"TUTORIAL",(char*)"ZMIEN PISADLO"};
char *autorzyMenu[7]={(char*)"<< POWROT <<",(char*)"Kamil Piotrowski",(char*)"Michal Lewinski",(char*)"Pawal Kaczmarek",(char*)"Rafal Wilinski",(char*)"Szymon Melewski",(char*)"Tymoteusz Kupcewicz"};
char *tutorialMenu[20]={(char*)"<< POWROT <<",  (char*)"To", (char*)"jest", (char*)"tutorial,", (char*)"bardzo", (char*)"zle", (char*)"sie", (char*)"go", (char*)"czyta", (char*)"1", (char*)"2", (char*)"3", (char*)"4", (char*)"5", (char*)"6", (char*)"7", (char*)"8", (char*)"9", (char*)"10"};
char *opcjeMenu[6]={(char*)"<< POWROT <<",(char*)"Szerokosc",(char*)"Wysokosc",(char*)"Predkosc X",(char*)"Predkosc Y",(char*)"Grubosc"};
const int numOpcjeMenu=6;
const int numTutorial=20;
int currentMainMenu=0;
int currentSecondMenu=0;
int eLast = 0;



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
	nA = digitalRead(ePinA); // Read encoder pins
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
	if (clLcd) {
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
	if (clLcd) {
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
	if (clLcd) {
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

int lcdPrint05(){
	if (clLcd) {
		clearLcd();
		clLcd=0;
		lcd.setCursor(0,0);
		lcd.print("Nieznany format!");
		lcd.setCursor(0,1);
		lcd.print("Wym.: .PBM (P4)");
		delay(300);
	}
	if(encoder()>0) return 1;
	return 0;
}

int printMenu(char *tab[], int *curr, int maxM){
	if(clLcd) {
		clearLcd();
		lcd.setCursor(0,0);
		lcd.print("> ");
		lcd.print(tab[*curr]);
		lcd.setCursor(0,1);
		lcd.print(tab[(*curr+1)%maxM]);
		clLcd=0;
		delay(200);
	}
	int e = encoder();
	switch(e) {
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

int setWidth(){
  return 1;
}
