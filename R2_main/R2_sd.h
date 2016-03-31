File *sdFileList;
File mainFile;
char **filesNames;
int numOfFiles=0;
int maxnumFiles=0;
int curNumOfFiles=0;

void mallocListFiles(int num){
 maxnumFiles=num;
 sdFileList=(File*)malloc(sizeof(File)*num);
}

void listFiles(File dir) { 
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) break;
   
     if (entry.isDirectory()) {
       Serial.println("/");
       listFiles(entry);
     } else {
       Serial.print(entry.name());
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
       if(numOfFiles >= maxnumFiles){
          sdFileList=(File*)realloc(sdFileList,sizeof(File)*(maxnumFiles+10));
          maxnumFiles+=10;
       }
       sdFileList[numOfFiles]=entry;
       numOfFiles++;
     }
     entry.close();
   }
}

void makeFilesCharList(){
  numOfFiles+=2;
  filesNames = (char**)malloc(sizeof(char*)*numOfFiles);
  filesNames[0]="<< POWROT <<";
  for (int i=1; i<numOfFiles; i++) filesNames[i]= sdFileList[i-1].name();
  
}
