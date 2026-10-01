#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo;
const int pinLDR = A0;
const int pinLED = 3;
const int pinTMP = A1;
const int pinSuelo = A2;
LiquidCrystal lcd(12, 11, 5, 4, 6, 7);

void setup() {
  servo.attach(2);
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  int luz = analogRead(pinLDR);// 0 a 1023
  int lectura = analogRead(pinTMP);               // 0 a 1023
  int lecturat = analogRead(pinSuelo);   // 0 a 1023
  int humedad = map(lecturat, 0, 876, 0, 100);
  humedad = constrain(humedad, 0, 100);
  float voltaje = lectura * 5.0 / 1024.0;         // convierte a voltios
  float temperaturaC = (voltaje - 0.5) * 100.0;
  if (luz<100){
  	digitalWrite(pinLED, HIGH);
  } else{
    digitalWrite(pinLED, LOW);
  }
  Serial.print("Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println(" °C");
  if (temperaturaC > 24 && temperaturaC < 26){
    ;
  }else if (temperaturaC < 24 || lecturat > 100){
  	servo.write(0);
  }else{
  	servo.write(90);
  }
  Serial.println(lecturat);
  lcd.setCursor(0, 0);          // fila de arriba
  lcd.print("Temp: ");
  lcd.print(temperaturaC, 1);
  lcd.print(" C   ");
  lcd.setCursor(0, 1);          // fila de arriba
  lcd.print("Hum: ");
  lcd.print(humedad, 1);
  lcd.print(" %   "); 
  delay(1000);
}