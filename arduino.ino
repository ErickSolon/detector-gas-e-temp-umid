#define sensorGas A0
#define botaoMenu 8
#define botaoGas 6
#define botaoUmidadeEtemperatura 7
#define DHTPIN 9
#define DHTTYPE DHT11

#include "DHT.h"
#include <LiquidCrystal.h>

DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(sensorGas, INPUT);
  pinMode(botaoGas, INPUT_PULLUP);
  pinMode(botaoUmidadeEtemperatura, INPUT_PULLUP);
  pinMode(botaoMenu, INPUT_PULLUP);
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(botaoGas) == LOW) {
    lcd.clear();
    while(true) {
      sensorDeGas();      
    }
  }

  if(digitalRead(botaoMenu) == LOW) {
    lcd.clear();
    while(true) {
      lcd.setCursor(0, 0);
      lcd.print("E ... S. Gas");
      lcd.setCursor(0, 1);
      lcd.print("D ... S. Temp."); 
      delay(500); 
    }

    
  }

  if(digitalRead(botaoUmidadeEtemperatura) == LOW) {
    lcd.clear();
    while(true) {
      sensorDeTemperatura();
    }
  }
}

void sensorDeGas() {
  int sensorGasDetectando = analogRead(sensorGas);

  Serial.println(sensorGasDetectando);
  
  if(sensorGasDetectando >= 200) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Detectado!");
    lcd.setCursor(4, 1);
    lcd.print("NVL: " + String(sensorGasDetectando));
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas nao detect.!");
    lcd.setCursor(4, 1);
    lcd.print("NVL: " + String(sensorGasDetectando));
  }

  lcd.display();
  delay(500);  
}

void sensorDeTemperatura() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade: " + String(umidade) + String("%"));
  lcd.setCursor(0, 1);
  lcd.print("Temp.: " + String(temperatura) + String("C"));

  delay(1000);
}
