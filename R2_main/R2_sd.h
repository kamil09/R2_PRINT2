char *mainFile;
char **sdFileList;

int numOfFiles=0;
int maxnumFiles=0;
int curNumOfFiles=0;
unsigned long time;
unsigned long time2;
int picWidth=0;
int picHeight=0;
int tablicaRys[10];
File loadedFile;

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
       
       if(numOfFiles >= maxnumFiles-1){
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
  while(c!=-1 && c!=' ' && c!='\n'){
    t=t*10;
    t=t+(c-'0');
    c=loadedFile.read();
  }
  return t;
}

void zerowanie(int from,int to){
  int i;
  for(i=from;i<=to;i++){
    tablicaRys[i]=0;
  }
}
//Do testow
void wypisywanie(int w){
  int i;
  Serial.println("wypisywanie tablicy");
  for(i=0;i<=w;i++){
    Serial.print(tablicaRys[i]);
    Serial.print(" ");
  }
  
}

void linia(){
  int c=loadedFile.read();
  int k=0;
  int w=0;
  //int b=0;
  int i;
  //tablicaRys=(int*)malloc(sizeof(int)*10);  
  zerowanie(0,9); 
  while(c!=-1){
    for(i=8;i>=0;i--){
       k++; 
       if(k==picWidth){
          k=0;
          break;
       }
      if(c & (1<<i)==1){
         if(tablicaRys[w]>=0){
           tablicaRys[w]++;
         }
         else{
           w++;
           tablicaRys[w]++;
         }
      }
      else{
         if(tablicaRys[w]<=0){
           tablicaRys[w]--;
         }
         else{
           w++;
           tablicaRys[w]--;
         }
      }
    }
    c=loadedFile.read();
 }
 wypisywanie(w);
}

int loadBitmap(char *file){
 Serial.print(file);
 Serial.print("\n");
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
  if((c=loadedFile.read())!=80){
    Serial.println("zly typ pliku");
    return 2;
  }
  if((c=loadedFile.read())!=52){
    Serial.println("zly typ pliku");
    return 2;
  }
  c=loadedFile.read();
  do{
    c=loadedFile.read();
  }while(c!=-1 && c!='\n');
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
  linia(); 
  time2 = millis();
  Serial.print("Koniec!");  
  Serial.println(time);
  Serial.println(time2);
  lcd.setCursor(0,0);
  lcd.print("Analiza zakonczona");
 
 
 return 0; 
}
