//---------------------------------------------ตั้งค่าขา
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

int Digit_1 = 13; //Digit 1
int Digit_2 = 12; //Digit 2
int Digit_3 = 11; //Digit 3
int Digit_4 = 10; //Digit 4

int pinUP = A0;
int pinDOWN = A1;
int pinRESET = A2;

//---------------------------------------------
//--------------------------------------------- จำสถานะของสวิตส์
int StatusUP = 0;
int StatusDOWN = 0;
int StatusRESET = 0;
//--------------------------------------------- 
/*
int CheckUP = 0;
int CheckDOWN = 0;
*/
//--------------------------------------------- ตัวเลข
int Number = 0;
//---------------------------------------------

void setup() {
  
  //Serial.begin(9600);
  
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G

  pinMode(Digit_1, OUTPUT);  //Digit 1
  pinMode(Digit_2, OUTPUT);  //Digit 2
  pinMode(Digit_3, OUTPUT);  //Digit 3
  pinMode(Digit_4, OUTPUT);  //Digit 4

  pinMode(pinUP, INPUT);
  pinMode(pinDOWN, INPUT);
  pinMode(pinRESET, INPUT);
  
}
void loop(){
  /*Serial.print("Pin Up : ");
  Serial.print(digitalRead(pinUP));
  Serial.print(" Pin Down : ");
  Serial.print(digitalRead(pinDOWN));
  Serial.print(" Pin Reset : ");
  Serial.println(digitalRead(pinRESET));*/
 
//----------------------------------------------------- สวิตส์ กดขึ้น UP

  if(digitalRead(pinUP) == HIGH && Number != 9999){
    StatusUP = 1;
    /*if(StatusUP >= 1000){
      Number ++;
      StatusUP = 500;
      CheckUP = 1;
    }*/
  }
  else if(digitalRead(pinUP) == LOW && StatusUP == 1 && Number != 9999/* && CheckUP != 1*/){
    Number = Number + 1;
    StatusUP = 0;
  }
  else{
    StatusUP = 0;
    CheckUP = 0;
  }
  
//----------------------------------------------------- สวิตส์ กดลง Down

  if(digitalRead(pinDOWN) == HIGH && Number != 0){
    StatusDOWN = 1;
    /*if(StatusDOWN >= 1000){
      Number --;
      StatusDOWN = 500;
      CheckDOWN = 1;
    }*/
  }
  else if(digitalRead(pinDOWN) == LOW && StatusDOWN == 1 && Number != 0/* && CheckDOWN != 1*/){
    Number = Number - 1;
    StatusDOWN = 0;
  }
  else{
    StatusDOWN = 0;
    CheckDOWN = 0;
  }
  
//----------------------------------------------------- สวิตส์ กดรีค่า Reset
  
  if(digitalRead(pinRESET) == HIGH){
    StatusRESET = 1;
  }
  
  else if(digitalRead(pinRESET) == LOW && StatusRESET == 1){
    Number = 0;
    StatusRESET = 0;
  }
  else{
    StatusRESET = 0;
  }

//----------------------------------------------------- เลือกดิจิตที่แสดง Select Digit

  SelectDigit(1);
  ChooseNumber(Number/1000);
  OffSevenSegment();

  SelectDigit(2);
  ChooseNumber((Number/100)%10);
  OffSevenSegment();

  SelectDigit(3);
  ChooseNumber((Number/10)%10);
  OffSevenSegment();

  SelectDigit(4);
  ChooseNumber(Number%10);
  OffSevenSegment();
}

void ChooseNumber(int ChooseNum){
  if(ChooseNum == 0){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
  }

  else if(ChooseNum == 1){
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
  }

  else if(ChooseNum == 2){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
    digitalWrite(e,LOW);
    digitalWrite(d,LOW);
  }

  else if(ChooseNum == 3){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
  }

  else if(ChooseNum == 4){
    digitalWrite(f,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
    digitalWrite(c,LOW);
  }

  else if(ChooseNum == 5){
    digitalWrite(a,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
  }

  else if(ChooseNum == 6){
    digitalWrite(a,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
  }

  else if(ChooseNum == 7){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
  }

  else if(ChooseNum == 8){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }

  else if(ChooseNum == 9){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
    digitalWrite(f,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
  }
}

void OffSevenSegment(){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void SelectDigit(int Select){
  digitalWrite(Digit_1, LOW);
  digitalWrite(Digit_2, LOW);
  digitalWrite(Digit_3, LOW);
  digitalWrite(Digit_4, LOW);
  switch(Select){
    case 1:digitalWrite(Digit_1, HIGH);break;
    case 2:digitalWrite(Digit_2, HIGH);break;
    case 3:digitalWrite(Digit_3, HIGH);break;
    case 4:digitalWrite(Digit_4, HIGH);break;
  }
}

