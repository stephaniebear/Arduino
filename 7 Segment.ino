 #include <Keypad.h>
int DS_pin = 4;   // Pin 14 ON IC 74HC595
int STCP_pin = 3; // Pin 12 ON IC 74HC595
int SHCP_pin = 2; // Pin 11 ON IC 74HC595

//const int D5 = A4    //Digit 5
const int D4 = A3;   //Digit 4
const int D3 = A2;   //Digit 3
const int D2 = A1;   //Digit 2
const int D1 = A0;   //Digit 1

int Time = 1;   //delay 7Segment

int NumberDigit1 = 0;
int NumberDigit2 = 0;
int NumberDigit3 = 0;
int NumberDigit4 = 0;
//int NumberDigit5 = 0;

int Status = 0;
int ModeSet = 0;
int UnUse = 0;
int StatusSetUpDigit = 0;

//-------------KeyBoad-------------

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6};

Keypad inputKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//---------------------------------

void setup() {
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(SHCP_pin,OUTPUT);

  pinMode(D4,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D1,OUTPUT);

  Serial.begin(9600);
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
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,16);
  digitalWrite(STCP_pin, HIGH); 
  break;

  case 10:
  // "-"
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,63);      // "-"
  digitalWrite(STCP_pin, HIGH); 
  break;
  }
}

void Clear(){
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin,SHCP_pin,MSBFIRST,127);
  digitalWrite(STCP_pin, HIGH);
  delay(1);
}

void ChooseDigit(int ChooseDigit){
  //digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
  switch(ChooseDigit){
    case 1:digitalWrite(D1, LOW);break;
    case 2:digitalWrite(D2, LOW);break;
    case 3:digitalWrite(D3, LOW);break;
    //case 5:digitalWrite(D5, LOW);break;
    default:digitalWrite(D4, LOW);break;
  }
}

void ShowSeg(){

  Clear();
  ChooseDigit(1);
  ChooseNumber(NumberDigit1%10);
  delay(Time);


  Clear();
  ChooseDigit(2);
  ChooseNumber(NumberDigit2%10);
  delay(Time);


  Clear();
  ChooseDigit(3);
  ChooseNumber(NumberDigit3%10);
  delay(Time);


  Clear();
  ChooseDigit(4);
  ChooseNumber(NumberDigit4%10);
  delay(Time);
/*
  Clear();
  ChooseDigit(5);
  ChooseNumber(NumberDigit5%10);
  delay(Time);*/
}

//--------------------------------------------------------

void SetUpSeg(int SelectDigit){

  switch(SelectDigit){
    case 1 :
    Clear();
    ChooseDigit(1);
    ChooseNumber(NumberDigit1%10);
    delay(Time);
    Clear();
    ChooseDigit(2);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(3);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(4);
    ChooseNumber(10);
    delay(Time);
    /*Clear();
    ChooseDigit(5);
    ChooseNumber(10);
    delay(Time);*/
    break;
    
    case 2 :
    Clear();
    ChooseDigit(2);
    ChooseNumber(NumberDigit2%10);
    delay(Time);
    Clear();
    ChooseDigit(1);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(3);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(4);
    ChooseNumber(10);
    delay(Time);
    /*Clear();
    ChooseDigit(5);
    ChooseNumber(10);
    delay(Time);*/
    break;

    case 3 :
    Clear();
    ChooseDigit(3);
    ChooseNumber(NumberDigit3%10);
    delay(Time);
    Clear();
    ChooseDigit(1);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(2);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(4);
    ChooseNumber(10);
    delay(Time);
    /*Clear();
    ChooseDigit(5);
    ChooseNumber(10);
    delay(Time);*/
    break;

    case 4 :
    Clear();
    ChooseDigit(4);
    ChooseNumber(NumberDigit4%10);
    delay(Time);
    Clear();
    ChooseDigit(1);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(2);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(3);
    ChooseNumber(10);
    delay(Time);
    /*Clear();
    ChooseDigit(5);
    ChooseNumber(10);
    delay(Time);*/
    break;

/*  case 5 :
    Clear();
    ChooseDigit(5);
    ChooseNumber(NumberDigit5%10);
    delay(Time);
    Clear();
    ChooseDigit(1);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(2);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(3);
    ChooseNumber(10);
    delay(Time);
    Clear();
    ChooseDigit(4);
    ChooseNumber(10);
    delay(Time);
    break;*/

    case 6 :      // ALL "-"
    Clear();
    ChooseDigit(1);
    ChooseNumber(10);
    delay(Time);
    
    Clear();
    ChooseDigit(2);
    ChooseNumber(10);
    delay(Time);
    
    Clear();
    ChooseDigit(3);
    ChooseNumber(10);
    delay(Time);
    
    Clear();
    ChooseDigit(4);
    ChooseNumber(10);
    delay(Time);
   /* Clear();
    ChooseDigit(5);
    ChooseNumber(10);
    delay(Time);*/
    break;
  }
}

//--------------------------------------------------------

void loop() {
  
  char keyPad = inputKeypad.getKey();

  if((keyPad == '*') && (UnUse == 0)){
   UnUse = 1;
   StatusSetUpDigit = 1;
  }

  if((Status == 0) && (UnUse == 0)){
    ShowSeg();
  }

  if(StatusSetUpDigit == 1){
    switch(keyPad){
      case '1' :ModeSet = 1;break;
      case '2' :ModeSet = 2;break;
      case '3' :ModeSet = 3;break;
      case '4' :ModeSet = 4;break;
      /*case '5' :ModeSet = 5;break;*/
    }
    
    switch(ModeSet){
      default :SetUpSeg(6);break;
      case 1 :SetUpSeg(1);break;
      case 2 :SetUpSeg(2);break;
      case 3 :SetUpSeg(3);break;
      case 4 :SetUpSeg(4);break;
      //case 5 :SetUpSeg(5);break;
    }
    
    if(keyPad == '#'){
      switch(ModeSet){
        case 1 : keyPad = NumberDigit1;break;
        case 2 : keyPad = NumberDigit2;break;
        case 3 : keyPad = NumberDigit3;break;
        case 4 : keyPad = NumberDigit4;break;
        //case 5 : keyPad = NumberDigit5;break;
      }
      Status = 1;
      StatusSetUpDigit = 0;
    }
  }

  if(Status == 1){
    switch(ModeSet){
      case 1 :
        switch(keyPad){
        case '1' : NumberDigit1 = 1 ; break;
        case '2' : NumberDigit1 = 2 ; break;
        case '3' : NumberDigit1 = 3 ; break;
        case '4' : NumberDigit1 = 4 ; break;
        case '5' : NumberDigit1 = 5 ; break;
        case '6' : NumberDigit1 = 6 ; break;
        case '7' : NumberDigit1 = 7 ; break;
        case '8' : NumberDigit1 = 8 ; break;
        case '9' : NumberDigit1 = 9 ; break;
        case '0' : NumberDigit1 = 0 ; break;
        }
      
        SetUpSeg(1);
      
        if(keyPad == '#'){
          Status = 0;
          ModeSet = 0;
          UnUse = 0;
        }
        break;

       case 2 :
        switch(keyPad){
        case '1' : NumberDigit2 = 1 ; break;
        case '2' : NumberDigit2 = 2 ; break;
        case '3' : NumberDigit2 = 3 ; break;
        case '4' : NumberDigit2 = 4 ; break;
        case '5' : NumberDigit2 = 5 ; break;
        case '6' : NumberDigit2 = 6 ; break;
        case '7' : NumberDigit2 = 7 ; break;
        case '8' : NumberDigit2 = 8 ; break;
        case '9' : NumberDigit2 = 9 ; break;
        case '0' : NumberDigit2 = 0 ; break;
        }
      
        SetUpSeg(2);
      
        if(keyPad == '#'){
          Status = 0;
          ModeSet = 0;
          UnUse = 0;
        }
        break;
        
       case 3 :
        switch(keyPad){
        case '1' : NumberDigit3 = 1 ; break;
        case '2' : NumberDigit3 = 2 ; break;
        case '3' : NumberDigit3 = 3 ; break;
        case '4' : NumberDigit3 = 4 ; break;
        case '5' : NumberDigit3 = 5 ; break;
        case '6' : NumberDigit3 = 6 ; break;
        case '7' : NumberDigit3 = 7 ; break;
        case '8' : NumberDigit3 = 8 ; break;
        case '9' : NumberDigit3 = 9 ; break;
        case '0' : NumberDigit3 = 0 ; break;
        }
      
        SetUpSeg(3);
      
        if(keyPad == '#'){
          Status = 0;
          ModeSet = 0;
          UnUse = 0;
        }
        break;

       case 4 :
        switch(keyPad){
        case '1' : NumberDigit4 = 1 ; break;
        case '2' : NumberDigit4 = 2 ; break;
        case '3' : NumberDigit4 = 3 ; break;
        case '4' : NumberDigit4 = 4 ; break;
        case '5' : NumberDigit4 = 5 ; break;
        case '6' : NumberDigit4 = 6 ; break;
        case '7' : NumberDigit4 = 7 ; break;
        case '8' : NumberDigit4 = 8 ; break;
        case '9' : NumberDigit4 = 9 ; break;
        case '0' : NumberDigit4 = 0 ; break;
        }
      
        SetUpSeg(4);
      
        if(keyPad == '#'){
          Status = 0;
          ModeSet = 0;
          UnUse = 0;
        }
        break;

       /*case 5 :
        switch(keyPad){
        case '1' : NumberDigit5 = 1 ; break;
        case '2' : NumberDigit5 = 2 ; break;
        case '3' : NumberDigit5 = 3 ; break;
        case '4' : NumberDigit5 = 4 ; break;
        case '5' : NumberDigit5 = 5 ; break;
        case '6' : NumberDigit5 = 6 ; break;
        case '7' : NumberDigit5 = 7 ; break;
        case '8' : NumberDigit5 = 8 ; break;
        case '9' : NumberDigit5 = 9 ; break;
        case '0' : NumberDigit5 = 0 ; break;
        }
      
        SetUpSeg(5);
      
        if(keyPad == '#'){
          Status = 0;
          ModeSet = 0;
          UnUse = 0;
        }
        break;*/
    }
  }
  
  if(keyPad){
    Serial.print("KeyPad : ");
    Serial.println(keyPad);
  }
  
}
