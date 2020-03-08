unsigned long time;

unsigned long endTime1 = 0;
unsigned long endTime2 = 0;
unsigned long endTime3 = 0;
unsigned long endTime4 = 0;

const int ButtonCoins = 2;

const int Button1 = 3;
const int Button2 = 4;
const int Button3 = 5;
const int Button4 = 6;

const int Power1 = 7;
const int Power2 = 8;
const int Power3 = 9;
const int Power4 = 10;

int StateButton1 = 0;
int StateButton2 = 0;
int StateButton3 = 0;
int StateButton4 = 0;

int Coins = 0;

//---------- Reset Millis ----------//
extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}

//---------- ----------- ----------//

void setup() {
  Serial.begin(9600);

  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  pinMode(Button4, INPUT);

  pinMode(Power1, OUTPUT);
  pinMode(Power2, OUTPUT);
  pinMode(Power3, OUTPUT);
  pinMode(Power4, OUTPUT);

  
  pinMode(ButtonCoins, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonCoins), CountCoin, FALLING);

  digitalWrite(Power1, LOW);
  digitalWrite(Power2, LOW);
  digitalWrite(Power3, LOW);
  digitalWrite(Power4, LOW);
}

void loop() {
  
  time = millis()/1000;

  SetEndTime();
  Power();
  Show();
  ResetMillis();
}

void CountCoin(){
  delay(1000);
  if(digitalRead(ButtonCoins) == 0){
    Coins++;
  }
}

void SetEndTime(){
  if(Coins > 0){
    if(digitalRead(Button1) == HIGH){
      StateButton1 = 1;
      endTime1 = time + (Coins * 30);
      Coins = 0;
    }
    if(digitalRead(Button2) == HIGH){
      StateButton2 = 1;
      endTime2 = time + (Coins * 30);
      Coins = 0;
    }
    if(digitalRead(Button3) == HIGH){
      StateButton3 = 1;
      endTime3 = time + (Coins * 30);
      Coins = 0;
    }
    if(digitalRead(Button4) == HIGH){
      StateButton4 = 1;
      endTime4 = time + (Coins * 30);
      Coins = 0;
    }
  }
}

void Power(){
  if(StateButton1 == 1){
    if(time <= endTime1){
      digitalWrite(Power1, HIGH);
    }
    else{
      StateButton1 = 0;
      digitalWrite(Power1, LOW);
    }
  }
  
  if(StateButton2 == 1){
    if(time <= endTime2){
      digitalWrite(Power2, HIGH);
    }
    else{
      StateButton2 = 0;
      digitalWrite(Power2, LOW);
    }
  }
  
  if(StateButton3 == 1){
    if(time <= endTime3){
      digitalWrite(Power3, HIGH);
    }
    else{
      StateButton3 = 0;
      digitalWrite(Power3, LOW);
    }
  }

  if(StateButton4 == 1){
    if(time <= endTime4){
      digitalWrite(Power4, HIGH);
    }
    else{
      StateButton4 = 0;
      digitalWrite(Power4, LOW);
    }
  }
}

void ResetMillis(){
  if(StateButton1 == 0 && StateButton2 == 0 && StateButton3 == 0 && StateButton4 == 0){
    setMillis(new_value);
  }
}

void Show(){
  Serial.print("Coins : ");
  Serial.print(Coins);
  Serial.print(" Time : ");
  Serial.print(time);
  Serial.print(" Power I : ");
  Serial.print(StateButton1);
  Serial.print(" Power II : ");
  Serial.print(StateButton2);
  Serial.print(" Power III : ");
  Serial.print(StateButton3);
  Serial.print(" Power IV : ");
  Serial.println(StateButton4);
}

