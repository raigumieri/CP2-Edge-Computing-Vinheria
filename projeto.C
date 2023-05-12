//Chamando a biblioteca do LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 7, 8, 9, 10);

//Sensor de Luminosidade
int ledverde = 4; //Led Verde
int ledamarelo = 5; //Led Amarelo
int ledvermelho = 6; //Led Vermelho
float LDR = A0; //Fotorresistor
int valorLDR = 0; //Vai ler as informações do LDR (LDR = 0)
int buzzer = 3;//Variável do piezo

//Sensores de Temperatura e Umidade
const int analogIn = A1; //Sensor de Temperatura
int umidade = 0; //Sensor de Umidade
int ValorBruto= 0; //Valor Bruto
double Voltagem = 0; //Voltagem
double tempC = 0; //Temperatura em °C

int ledvermelhoT = 1; //Led de Temperatura
int ledamareloT = 2; //Led de Temperatura


//-----------------------------------------------------------------------------

void setup() {
  
  pinMode(ledverde, OUTPUT); //Led Verde(Receber informação)
  pinMode(ledamarelo, OUTPUT); //Led Amarelo(Receber informação)
  pinMode(ledvermelho, OUTPUT); //Led Vermelho(Receber informação)
  
  pinMode(LDR, INPUT); //Fotorresistor(Enviar informação)
  pinMode(buzzer, OUTPUT); //Piezo(Receber informação)
  pinMode(A1, INPUT); //Temperatura(Enviar informação) 
  
  pinMode(ledamareloT, OUTPUT); //Led Amarelo Temp.(Receber informação)
  pinMode(ledvermelhoT, OUTPUT); //Led Vermelho Temp.(Receber informação)
  
  
  lcd.begin(16,2); //Ligando o LCD
  
  
}

//-----------------------------------------------------------------------------

void loop() {
  
  valorLDR = analogRead(LDR); //Vai ler o LDR e armazenar no valorLDR
  
  //Luminosidade adequada (LED VERDE)
  if(valorLDR <= 100) {
    
    digitalWrite(ledvermelho, 0);
    digitalWrite(ledamarelo, 0);
    digitalWrite(ledverde, 1);
    noTone(buzzer);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Luminosidade");
    lcd.setCursor(0,1);
    lcd.print("Adequada");
    
    delay(2000);
    
  }
    
  //Luminosidade em alerta (LED AMARELO)
  if(valorLDR > 100 && valorLDR < 150) {
    
    digitalWrite(ledvermelho, 0);
    digitalWrite(ledamarelo, 1);
    digitalWrite(ledverde, 0);
    noTone(buzzer);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ambiente a Meia");
    lcd.setCursor(0,1);
    lcd.print("Luz");

    delay(2000);
  }
     
  //Problema de luminosidade (LED VERMELHO)
  if(valorLDR >= 150) {   
 
    digitalWrite(ledvermelho, 1);
    digitalWrite(ledamarelo, 0);
    digitalWrite(ledverde, 0);
    tone(buzzer, 1000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ambiente Muito");
    lcd.setCursor(0,1);
    lcd.print("Claro");
    
    delay(2000);
  }
  
    
//-----------------------------------------------------------------------------
  
//Sensor de Temperatura
  
  ValorBruto = analogRead(analogIn);
  Voltagem = (ValorBruto / 1023.0) * 5000; //5000 para obter milivots.
  tempC = (Voltagem-500) * 0.1;

  
  if(tempC >= 10 && tempC <= 15){
    
   digitalWrite(ledvermelhoT, 0);
   digitalWrite(ledamareloT, 0); 
   noTone(buzzer);   
    
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Temperatura OK");
   lcd.setCursor(0,1);
   lcd.print("Temp. = "); lcd.print(tempC); lcd.print("C");
    
   delay(2000);
           
  }
  
  
  if(tempC > 16){
  
    digitalWrite(ledvermelhoT, 1);
    digitalWrite(ledamareloT, 0);
    tone(buzzer, 2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA");  
    lcd.setCursor(0,1);
    lcd.print("Temp. = "); lcd.print(tempC); lcd.print("C");
 
    delay(2000);
  } 
  
  if(tempC < 9){
    
digitalWrite(ledamareloT, 1);
    digitalWrite(ledvermelhoT, 0);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp. BAIXA");    
    lcd.setCursor(0,1);
    lcd.print("Temp. = "); lcd.print(tempC); lcd.print("C");

    
    delay(2000);
  }
  
//-----------------------------------------------------------------------------
  
//Sensor de Umidade (Potenciômetro)
  
  umidade = analogRead(A2);
  int umidade_P(map(umidade, 0, 1023, 0, 100));
  
  if(umidade >=50 && umidade <=70){
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade OK");
  lcd.setCursor(0,1);
  lcd.print("Umidade = "); lcd.print(umidade_P); lcd.print("%");
    
  delay(2000);
  } 
  
  if(umidade > 70){
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade ALTA");
  lcd.setCursor(0,1);
  lcd.print("Umidade = "); lcd.print(umidade_P); lcd.print("%");
    
  delay(2000);
  } 
  
  if(umidade < 50){
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade BAIXA"); 
  lcd.setCursor(0,1);
  lcd.print("Umidade = "); lcd.print(umidade_P); lcd.print("%");
    
  delay(2000);
  } 
 

  
  
}
