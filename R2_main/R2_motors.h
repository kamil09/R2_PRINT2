int delayX=100;
int delayY=100;
float nowX=0;
float nowY=0;
//Liczba krokow silnika na 1mm
const int stepsXPermm = 0;
const int stepsYPermm = 0;
float lineWidth = 1;
float lineHeight = 1;

void servoDown(){
   servo.writeMicroseconds(500);  
}
void servoUp(){
   servo.writeMicroseconds(1500);
}

void calibrate(){
  int t=0;
  Serial.println("Kalibruje");
  Serial.print("x: ");
  while(1){
    t++;
    digitalWrite(motorXStep,HIGH);
    delayMicroseconds(delayX);
    digitalWrite(motorXStep,LOW);
    delayMicroseconds(delayX);
    if(digitalRead(endX)==0){
      Serial.println(t); 
      break;
    }    
  }
  t=0;
  Serial.print("y: ");
  while(1){
    t++;
    digitalWrite(motorYStep,HIGH);
    delayMicroseconds(delayY);
    digitalWrite(motorYStep,LOW);
    delayMicroseconds(delayY);
    if(digitalRead(endY)==0){
      Serial.println(t);
      break;
    }
  }
  nowX=0;
  nowY=0;
}  

void calculateMM(){
    lineWidth=width/picWidth;
    
}

void move(int kroki){
  
}
