#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
int led1Pin = 8;
int ldr1Pin = A0;
int servo1Pin = 4;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("teste 1323");
  servo.attach(servo1Pin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(ldr1Pin, INPUT);
  pinMode(servo1Pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Serial.println(leitura_ultra(trigPin, echoPin));
  // Serial.println(leitura_ldr(ldr1Pin));
  delay(500);
  LeituraLdr(ldr1Pin, led1Pin);
  ControlaCancela(LeituraUltra(trigPin, echoPin), servo1Pin);
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
void LeituraLdr(int ldr1Pin, int led1Pin)
{
  int luminosidade;
  luminosidade = analogRead(ldr1Pin);
  if (luminosidade > 500)
  {
    digitalWrite(led1Pin, LOW);
  }
  else
  {
    digitalWrite(led1Pin, HIGH);
  }
}

//Realiza o controle das cancelas com base na distancia lida pelo sensor ultrassonico
void ControlaCancela(int distancia, int servo1Pin)
{
  if (distancia < 15)
  {
    servo.write(90);
    delay(1000);
  }
  else
    servo.write(0);
}
