#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int trig1Pin = 2;
int echo1Pin = 3;
int trig2Pin = 5;
int echo2Pin = 6;
int led1Pin = 8;
int led2Pin = 9;
int led3Pin = 10;
int led4Pin = 11;
int led5Pin = 12;
int led6Pin = 13;
int ldr1Pin = A0;
int ldr2Pin = A1;
int ldr3Pin = A2;
int ldr4Pin = A3;
int ldr5Pin = A4;
int ldr6Pin = A5;
int servo1Pin = 4;
int servo2Pin = 7;
int vagas = 0;
Servo servo1;
Servo servo2;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  pinMode(trig1Pin, OUTPUT);
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(ldr1Pin, INPUT);
  pinMode(ldr2Pin, INPUT);
  pinMode(ldr3Pin, INPUT);
  pinMode(ldr4Pin, INPUT);
  pinMode(ldr5Pin, INPUT);
  pinMode(ldr6Pin, INPUT);
  pinMode(servo1Pin, OUTPUT);
  pinMode(servo2Pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  vagas = LeituraLdr(ldr1Pin, led2Pin) + LeituraLdr(ldr2Pin, led4Pin) + LeituraLdr(ldr3Pin, led6Pin) + LeituraLdr(ldr4Pin, led1Pin) + LeituraLdr(ldr5Pin, led3Pin) + LeituraLdr(ldr6Pin, led5Pin);
  // 250 250 250 200 200 250
  if(vagas != 0)
  {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Seja bem vindo!");

    lcd.setCursor(2, 2);
    lcd.print("Vagas livres: ");
    lcd.print(vagas);
    ControlaCancela1(LeituraUltra(trig1Pin, echo1Pin), servo1Pin);
    ControlaCancela2(LeituraUltra(trig2Pin, echo2Pin), servo2Pin);
  }
  else
  {
    lcd.setCursor(2, 0);
    lcd.print("Estamos lotados!");

    lcd.setCursor(2, 2);
    lcd.print("Vagas livres: ");
    lcd.print(vagas);
    ControlaCancela2(LeituraUltra(trig2Pin, echo2Pin), servo2Pin);
  }
  Serial.println(LeituraUltra(trig2Pin, echo2Pin));
  //Serial.println(analogRead(ldr1Pin));
}

//Realiza a leitura do sensor ultrassonico e retorna a distancia detectada
int LeituraUltra(int trigPin, int echoPin)
{
  long duration = 0, distancia = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distancia = duration /29 / 2;
  return distancia;
}

//Realiza a leitura do ldr e liga ou desliga o led com base na luminosidade
int LeituraLdr(int ldrPin, int ledPin)
{
  int luminosidade;
  luminosidade = analogRead(ldrPin);
  if (luminosidade > 800)
  {
    digitalWrite(ledPin, LOW);
    return 0;
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    return 1;
  }
  
}

//Realiza o controle das cancelas com base na distancia lida pelo sensor ultrassonico
void ControlaCancela1(int distancia, int servoPin)
{
  if (distancia < 6)
  {
    servo1.write(90);
    delay(2500);
  }
  else
    servo1.write(180);
}

void ControlaCancela2(int distancia, int servoPin)
{
  if (distancia < 9)
  {
    servo2.write(10);
    delay(2500);
  }                
  else
    servo2.write(77);
}
