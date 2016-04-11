
int printImage(){
	int t=0;
	int i;
	int k=0;
	int mm=0;
	pixelMm();
	clearLcd();
	lcd.setCursor(0,0);
	lcd.print("Trwa drukowanie");

	for(i=0; i<picHeight; i++) {
		lcd.setCursor(0,1);
		lcd.print((loadedBytes/loadedFileSize)*100);
		lcd.print(" %                                 ");
		t=linia();
		if(strona==0) {
			for (k=0; k<=t; k++) {
				if (tablicaRys[k]==0) {
					break;
				}
				if(tablicaRys[k] < 0) {
					servoUp();
				}
				else
				if(tablicaRys[k] > 0) {
					servoDown();
				}
				//PRZELICZ na mm
				//PRZESUN SILNIK NA OSI X
				mm=abs(tablicaRys[k])*lineWidth;
				moveMotorX(mm/stepsXPerMm);
			}
		}else{
			for (k=t; k>=0; k--) {
				if (tablicaRys[k]==0) {
					continue;
				}
				if(tablicaRys[k] < 0) {
					servoUp();
				}
				else
				if(tablicaRys[k] > 0) {
					servoDown();
				}
				//PRZELICZ na mm
				//PRZESUN SILNIK NA OSI X
				mm=abs(tablicaRys[k])*lineWidth;
				moveMotorX(mm/stepsXPerMm);
			}
		}
		//PRZESUN SILNIKI NA OSI Y
		moveMotorY(lineHeight/stepsYPerMm);
		strona = 1 - strona;
		free(tablicaRys);
	}
}
