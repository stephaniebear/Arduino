int DS_pin = 2; // Pin 14 ON IC 74HC595
int STCP_pin = 4; // Pin 12 ON IC 74HC595
int SHCP_pin = 3; // Pin 11 ON IC 74HC595

const int ButtonUp = 6;
const int ButtonDown = 7;
const int ButtonTimer = 8;
const int ButtonCounter = 9;

int StatusButtonUp = 0;
int StatusButtonDown = 0;
int StatusButtonTimer = 0;
int StatusButtonCounter = 0;

int StatusMode = 0;
int BackupStatusMode = 0;

unsigned long BackupSec = 0;
unsigned long Sec = 0; 
unsigned long Minute = 0;

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

void setup() {
  //Serial.begin(9600);
  
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(SHCP_pin,OUTPUT);

  pinMode(ButtonUp,INPUT);
  pinMode(ButtonDown,INPUT);
  pinMode(ButtonTimer,INPUT);
  pinMode(ButtonCounter,INPUT);
}

void loop() {
  switch(StatusMode){
    case 0:SetTime();break;
    case 1:Timer();break;
    case 2:Counter();break;
  }
}

void SetTime(){
  update_value = BackupSec;
  updateMillis(update_value);
  
  //-------------------- เพิ่มเวลา
  if((digitalRead(ButtonUp) == HIGH) && Minute < 99){
    StatusButtonUp = 1;
  }
  if((digitalRead(ButtonUp) == LOW) && StatusButtonUp == 1 && Minute < 99){
    Minute += 1;
    StatusButtonUp = 0;
  }
  //--------------------

  //-------------------- ลดเวลา
  if((digitalRead(ButtonDown) == HIGH) && Minute > 0){
    StatusButtonDown = 1;
  }
  if((digitalRead(ButtonDown) == LOW) && StatusButtonDown == 1 && Minute > 0){
    Minute -= 1;
    StatusButtonDown = 0;
  }
  //--------------------

  //-------------------- Timer
  if((digitalRead(ButtonTimer) == HIGH) && Minute <= 99 && Sec <= 60){
    StatusButtonTimer = 1;
  }
  if((digitalRead(ButtonTimer) == LOW) && StatusButtonTimer == 1 && Minute <= 99 && Sec <= 60){
    if(BackupStatusMode == 0 || BackupStatusMode == 1){
      StatusMode = 1;
      BackupStatusMode = 1;
      StatusButtonTimer = 0;
    }
  }
  //--------------------

  //-------------------- StopCounter
  if((digitalRead(ButtonCounter) == HIGH) && Minute >= 0 && Sec >= 0){
    StatusButtonCounter = 1;
  }
  if((digitalRead(ButtonCounter) == LOW) && StatusButtonCounter == 1 && Minute >= 0 && Sec >= 0){
    if(BackupStatusMode == 0 || BackupStatusMode == 2){
      StatusMode = 2;
      BackupStatusMode = 2;
      StatusButtonCounter = 0;
    }
  }
  //--------------------
  
  Show();
}

void Timer(){
  if((Minute == 99) && (Sec == 60)){
    Minute = 99;
    Sec = 60;
    //-------------------- ResetTimer
    if((digitalRead(ButtonTimer) == HIGH)){
      StatusButtonTimer = 1;
      }
    if((digitalRead(ButtonTimer) == LOW) && StatusButtonTimer == 1){
      StatusMode = 0;
      StatusButtonTimer = 0;
      BackupStatusMode = 0;
      Minute = 0;
      Sec = 0;
    }
    //--------------------
  }
  else{
    if((Sec == 60) && (Minute <= 98)){
      Minute ++;
      setMillis(new_value);
    }
    
    if((Minute <= 99) && (Sec <= 60)){
      Sec = ((millis()/1000));
      BackupSec = millis();
    }
  }

  //-------------------- StopTimer
  if((digitalRead(ButtonTimer) == HIGH)){
    StatusButtonTimer = 1;
  }
  if((digitalRead(ButtonTimer) == LOW) && StatusButtonTimer == 1){
    StatusMode = 0;
    StatusButtonTimer = 0;
  }
  //--------------------
  
  Show();
}

void Counter(){
  if((Minute == 0) && (Sec == 0)){
    Minute = 0;
    Sec = 0;
    StatusMode = 0;
    BackupStatusMode = 0;
  }
  else{
    if((Sec == 0) && (Minute >= 0)){
      Minute --;
      setMillis(new_value);
    }
    
    if((Minute >= 0) && (Sec >= 0)){
      Sec = (59-(millis()/1000));
      BackupSec = millis();
    }
  }

  //-------------------- StopCounter
  if((digitalRead(ButtonCounter) == HIGH) ){
    StatusButtonCounter = 1;
  }
  if((digitalRead(ButtonCounter) == LOW) && StatusButtonCounter == 1){
    StatusMode = 0;
    StatusButtonCounter = 0;
  }
  //--------------------
  
  Show();
}

int ChooseNumber(int Number){  
  switch(Number){
    default:
      Number = 64;      // Number 0
    break;
    
    case 1:
      Number = 121;     // Number 1
    break;

    case 2:
      Number = 36;     // Number 2
    break;

    case 3:
      Number = 48;      // Number 3
    break;

    case 4:
      Number = 25;      // Number 4
    break;

    case 5:
      Number = 18;      // Number 5
    break;

    case 6:
      Number = 2;       // Number 6
    break;

    case 7:
      Number = 120;     // Number 7
    break;

    case 8:
      Number = 0;       // Number 8
    break;

    case 9:
      Number = 24;      // Number 9
    break;
  }
  return Number;
}

void Clear(){
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,255);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,255);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,255);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,255);
  digitalWrite(STCP_pin, HIGH);
}

void Show(){
  Clear();
  
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,ChooseNumber(Sec%10));
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,ChooseNumber(Sec/10));
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,ChooseNumber(Minute%10));
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,ChooseNumber(Minute/10));
  digitalWrite(STCP_pin, HIGH);
  
  /*Serial.print(Minute);
  Serial.print(" : ");
  Serial.print(Sec);
  Serial.print("           ");
  Serial.print(ChooseNumber(Minute/10));
  Serial.print(" ");
  Serial.print(ChooseNumber(Minute%10));
  Serial.print(" ");
  Serial.print(ChooseNumber(Sec/10));
  Serial.print(" ");
  Serial.println(ChooseNumber(Sec%10));*/
}

