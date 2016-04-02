char *mainFile;
char **sdFileList;

int numOfFiles=0;
int maxnumFiles=0;
int curNumOfFiles=0;
unsigned long time;
unsigned long time2;

void mallocListFiles(int num){
 maxnumFiles=num;
 sdFileList=(char**)malloc(sizeof(char*)*num);
 sdFileList[0]="<< POWROT <<";
}

void listFiles(File dir) { 
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) break;
     Serial.print(entry.name());
     
     if (entry.isDirectory()) {
       Serial.println("/");
       listFiles(entry);
     } else {
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
       
       char path[32];
       char *dirname=dir.name();
       strcpy(path,dir.name());
       if(dirname[0] != '/' )
         strcat(path, "/");
       strcat(path, entry.name());
       
       if(numOfFiles >= maxnumFiles-1){
          sdFileList=(char**)realloc(sdFileList,sizeof(char*)*(maxnumFiles+10));
          maxnumFiles+=10;
          break;
       }
       sdFileList[numOfFiles+1] = (char*)malloc(sizeof(char)*32);
       strcpy(sdFileList[numOfFiles+1],path);
       Serial.print(sdFileList[numOfFiles+1]);
       numOfFiles++;
     }
     entry.close();
   }
}

int loadBitmap(char *file){
 Serial.print(file);
 Serial.print("\n");
 File loadedFile;
 loadedFile=SD.open(file);
 
 if(!loadedFile) return 1;
 clearLcd();
 clLcd=0;
 lcd.setCursor(0,0);
 lcd.print("Trwa analiza:");
 lcd.setCursor(0,1);
 lcd.print(file);
 time = millis();
  int c=0;
  while(c!=-1){
    c=loadedFile.read();
    if(c=='\n') Serial.println("NOWA LINIA!");
    else if(c==' ') Serial.println("SPACJA");
    else Serial.println(c); 
    //Serial.print("\n");
  }
  time2 = millis();
  Serial.print("Koniec!");
  
  Serial.println(time);
  Serial.println(time2);
  lcd.setCursor(0,0);
  lcd.print("Analiza zakonczona");
 
 
 return 0; 
}
