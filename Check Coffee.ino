int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;

float voltage1 = 0;
float voltage2 = 0;
float voltage3 = 0;
float voltage4 = 0;

const int Relay1 = 30; // Port Digital 30 ขา Relay ตัวที่ 1
const int Relay2 = 31; // Port Digital 31 ขา Relay ตัวที่ 2
const int Relay3 = 32; // Port Digital 32 ขา Relay ตัวที่ 3
const int Relay4 = 33; // Port Digital 33 ขา Relay ตัวที่ 4

void setup() {
  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1, LOW);
  delay(5);
  digitalWrite(Relay2, LOW);
  delay(5);
  digitalWrite(Relay3, LOW);
  delay(5);
  digitalWrite(Relay4, LOW);
  delay(5);
}

void loop() {
  sensorValue1 = analogRead(A0); // Sensor 1
  sensorValue2 = analogRead(A1); // Sensor 2
  sensorValue3 = analogRead(A2); // Sensor 3
  sensorValue4 = analogRead(A3); // Sensor 4
  
  voltage1 = sensorValue1 * (5.0 / 1023.0); // แปลงค่าเป็นไฟ 5 V
  voltage2 = sensorValue2 * (5.0 / 1023.0);
  voltage3 = sensorValue3 * (5.0 / 1023.0);
  voltage4 = sensorValue4 * (5.0 / 1023.0);

  Serial.print(voltage1);
  Serial.print(" ");
  Serial.print(voltage2);
  Serial.print(" ");
  Serial.print(voltage3);
  Serial.print(" ");
  Serial.println(voltage4);
  
  if(voltage1 <= 3){                //ถ้าไฟน้อยกว่า 3V 
    delay(15);                      //หน่วงเวลา 15 ms
    digitalWrite(Relay1, HIGH);     //สั่ง Relay ตัวที่ 1 ทำงาน
    delay(60);                      //หน่วงเวลา 60 ms
  }
  digitalWrite(Relay1, LOW);        //สั่ง Relay หยุดการทำงาน
  delay(3);

  if(voltage2 <= 3){
    delay(15);
    digitalWrite(Relay2, HIGH);
    delay(60);
  }
  digitalWrite(Relay2, LOW);
  delay(3);
  
  if(voltage3 <= 3){
    delay(15);
    digitalWrite(Relay3, HIGH);
    delay(60);
  }
  digitalWrite(Relay3, LOW);
  delay(3);

  if(voltage4 <= 3){
    delay(15);
    digitalWrite(Relay4, HIGH);
    delay(60);
  }
  digitalWrite(Relay4, LOW);
  delay(3);
}
