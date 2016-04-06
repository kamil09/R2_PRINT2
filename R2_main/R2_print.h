int printImage(){
  int t=0;
  int i;
  int k=0;
  
  clearLcd();
  lcd.setCursor(0,0);
   lcd.print("Trwa drukowanie");
  
  for(i=0;i<picHeight;i++){
    lcd.setCursor(0,1);
    lcd.print(loadedBytes/loadedFileSize*100);
    lcd.print(" %                                 "); 
    
    t=linia();
    //wypisywanie(t);
    for (k=0;k<=t;k++){
       if(tablicaRys[k] < 0){
         servoUp();
         //PRZELICZ na mm
         //PRZESUŃ SILNIK NA OSI X
       }
       else
       if(tablicaRys[k] > 0){
         servoDown();
         //PRZELICZ na mm
         //PRZESUN SILNIK NA OSI X
       }
    }
    //PRZESUN SILNIKI NA OSI Y
     
    free(tablicaRys);
   }
}
