int DS_pin = 13; // Pin 14 ON IC 74HC595
int STCP_pin = 12; // Pin 12 ON IC 74HC595
int SHCP_pin = 11; // Pin 11 ON IC 74HC595

int D4 = 10;  //Digit 4
int D3 = 9;   //Digit 3
int D2 = 8;   //Digit 2
int D1 = 7;   //Digit 1

int Time = 5; //delay 7Segment Defult = 5

//----------------------------- Switch --------------------------------------------------------------------------------------------------------
const int StartPin = 2;
const int ResetPin = 3;
const int TimeUpPin = 4;
const int TimeDownPin = 5;

boolean StartPinState = 0;
boolean TimeUpPinState = 0;
boolean TimeDownPinState = 0;

int Status = 0;

unsigned long BackUpSec = 0;
unsigned long Sec = 00; 
unsigned long Minute = 05;

//----------------------------------- Reset Millis ---------------------------------------

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}

//----------------------------------------------------------------------------------------
//----------------------------------- Update Millis ---------------------------------------

unsigned long update_value = 0;

void updateMillis(unsigned long update_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = update_millis;
  SREG = oldSREG;
}

//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
//----------------------------- 7 Segment ------------------------------
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(SHCP_pin,OUTPUT);

  pinMode(D4,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D1,OUTPUT);
//----------------------------------------------------------------------
//----------------------------- Switch ---------------------------------
  pinMode(StartPin, INPUT);
  pinMode(ResetPin, INPUT);
  pinMode(TimeUpPin, INPUT);
  pinMode(TimeDownPin, INPUT);
//----------------------------------------------------------------------
}

void ChooseNumber(int ChooseNum){
  switch(ChooseNum){ 
   default:
   // Number 0
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,64);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 1:
  // Number 1
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,121);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 2:
  // Number 2
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,36);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 3:
  // Number 3
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,48);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 4:
  // Number 4
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,25);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 5:
  // Number 5
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,18);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 6:
  // Number 6
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,2);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 7:
  // Number 7
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,120);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 8:
  // Number 8
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,0);
  digitalWrite(STCP_pin, HIGH);
  break;

  case 9:
  // Number 9
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,24);
  digitalWrite(STCP_pin, HIGH); 
  break;
  }
}

void ChooseDigit(int ChooseDigit){
  digitalWrite(D4, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
  switch(ChooseDigit){
    case 1:digitalWrite(D1, LOW);break;
    case 2:digitalWrite(D2, LOW);break;
    case 3:digitalWrite(D3, LOW);break;
    default:digitalWrite(D4, LOW);break;
  }
}

void Show7Seg(){
  if(Sec == 60){
    //Minute Tens
    ChooseDigit(1);
    ChooseNumber(((Minute+1)/10)%10);
    delay(Time);

   //Minute Ones
   ChooseDigit(2);
   ChooseNumber((Minute+1)%10);
   delay(Time);

   //Sec Tens
   ChooseDigit(3);
   ChooseNumber(0);
   delay(Time);

   //Sec Ones
   ChooseDigit(4);
   ChooseNumber(0);
   delay(Time);
  }
  
  else{
   //Minute Tens
   ChooseDigit(1);
   ChooseNumber((Minute/10)%10);
   delay(Time);

   //Minute Ones
   ChooseDigit(2);
   ChooseNumber(Minute%10);
   delay(Time);

   //Sec Tens
   ChooseDigit(3);
   ChooseNumber((Sec/10)%10);
   delay(Time);

   //Sec Ones
   ChooseDigit(4);
   ChooseNumber(Sec%10);
   delay(Time); 
  }
}

//----------------------------- Switch --------------------------------------------------------------------------------------------------------
//----------------------------------- ShowCounter ----------------------------------------

void ShowCounter(){
  
  StartPinState = digitalRead(StartPin);
  
  if((digitalRead(StartPin) == LOW) && (Status == 1)){
    if((Minute == 0) && (Sec == 0)){
      Status = 0;
      Minute = 00;
      Sec = 00;
      Show7Seg();
      //Serial.println("RESET MINUTE");
      }
      
    else{
      //Reset Millis
      if((Sec == 0) && (Minute > 0)){
        Show7Seg();
        Minute --;
        setMillis(new_value);
        
        //Serial.println("SUB MINUTE");
      }

      if((Minute >= 0) && (Sec >= 0)){
        Sec = (60-(millis()/1000));
        BackUpSec = millis();
        //Serial.println("SUB SEC");
      }
      
      Serial.print(Minute);
      Serial.print(" : ");
      Serial.println(Sec);
      Show7Seg();
      }
   }
   
   //else if((digitalRead(StartPin) == HIGH) && (Status == 1)){
    if((StartPinState == HIGH) && (Status == 1)){
      Show7Seg();
      if(digitalRead(StartPin) == LOW){
        Serial.println("Stop");
        Status = 0;
      }
   }
}

//----------------------------------------------------------------------------------------

//------------------------------------- SetUp --------------------------------------------
void SetUp(){

  StartPinState = digitalRead(StartPin);
  //Serial.println(StartPinState);
  
  if((digitalRead(StartPin) == LOW) && (Status == 0)){    
    //SetUpPin On LOW
    //StartPinState = digitalRead(StartPin);
    TimeUpPinState = digitalRead(TimeUpPin);
    TimeDownPinState = digitalRead(TimeDownPin);
    
    Serial.println("Set Up");
    Show7Seg();

    update_value = BackUpSec;
    updateMillis(update_value);

    if(digitalRead(ResetPin) == HIGH){
      setMillis(new_value);
      Minute = 00;
      Sec = 00;
      
      Serial.print("Reset Time = ");
      Serial.print(Minute);
      Serial.print(" : ");
      Serial.println(Sec);
      //แสดงบน 7Segment
      Show7Seg();
    }
    
    //if(digitalRead(TimeUpPin) == HIGH && (Minute <=94)){
    if((TimeUpPinState == HIGH) && (Minute <=94)){
      if(digitalRead(TimeUpPin) == LOW){
        Minute = Minute + 5;
        Serial.println(Minute);
        //แสดงบน 7Segment
        Show7Seg();
      }
    }
    
    //if((digitalRead(TimeDownPin) == HIGH) && (Minute >= 5)){
    if((TimeDownPinState == HIGH) && (Minute >= 5)){
      if(digitalRead(TimeDownPin) == LOW){
        Minute = Minute - 5;
        Serial.println(Minute);
        //แสดงบน 7Segment
        Show7Seg();
      }
    }
  }
    
    if((StartPinState == HIGH) && (Sec >= 0)){
      Show7Seg();
      if(digitalRead(StartPin) == LOW){
        Serial.println("Start");
        Status = 1;
      }
    }
}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------


void loop() {
  switch(Status){
    case 0: SetUp();break;
    case 1: ShowCounter();;break;
  }
}
