//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 RTC; 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define prim 6
#define segm 7
#define term 8
#define quam 9
#define quim 10
#define rem A0

int flag = 1;
long preMillis = 0;
long interval = 4000;

void setup()
{
  pinMode(prim, INPUT_PULLUP);
  pinMode(segm, INPUT_PULLUP);
  pinMode(term, INPUT_PULLUP);
  pinMode(quam, INPUT_PULLUP);
  pinMode(quim, INPUT_PULLUP);
  pinMode(rem, INPUT_PULLUP);
  
  Serial.begin(9600);//Inicializacao da serial
  Wire.begin();//Inicializacao do protocolo wire
  RTC.begin();//Inicializacao do modulo RTC
 //Verifica se o modulo esta funcionando ou nao
    if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    //    Ajusta a data/hora do Clock com a data/hora em que o codigo foi compilado, basta descomentar a linha
    //    RTC.adjust(DateTime(__DATE__, __TIME__));
}
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Inicializando");
  lcd.setCursor(3, 1);
  lcd.print(" Sistema");
  delay(800);
   
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 1; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(240);
  }
  //Rolagem para a direita
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(240);
  }
    //Rolagem para a esquerda
  for (int posicao = 0; posicao < 2; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(240);
  }
  delay(100);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Tomate Car");
  lcd.setCursor(3,1);
  lcd.print("Sistema OK");
  delay(1700);
    //lcd.clear();
}
 
void loop() //---------------------------------- LOOP ----------------------

{
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 15V):
  float voltage = sensorValue * (15.0 / 1023.0);

  unsigned long atualMillis = millis();
  
  if (atualMillis - preMillis > interval)
  {
    preMillis = atualMillis;
    if (flag == 1)
    {
      flag = 2;
      lcd.setCursor(0,0);
      lcd.print("Temp27C ");
      lcd.setCursor(8,0);
      lcd.print("Bat ");
      lcd.setCursor(12,0);
      lcd.print(voltage);
    }else if (flag == 2)
    {
      flag = 3;
    lcd.setCursor(0,0);    
    lcd.print("                  ");  
    lcd.setCursor(0,0);
    DateTime now = RTC.now();//Recuperando a data e hora atual
    lcd.print(now.day(), DEC);//Imprimindo o dia
    lcd.print('/');
    lcd.print(now.month(), DEC);//Recuperando o mes
    lcd.print('/');
    lcd.print(now.year(), DEC);//Recuperando o ano
    lcd.print(' ');
    lcd.print(now.hour(), DEC);//Recuperando a hora
    lcd.print(':');
    lcd.print(now.minute(), DEC);//Recuperando os minutos
   // lcd.print(now.second(), DEC);//Recuperando os segundos
    
    }else{
     flag = 1;
     lcd.setCursor(0,0);
     lcd.print("USE O CINTO! ! !");
    }
  }
  lcd.setCursor(0, 1);
  if (!digitalRead(prim)){
    lcd.print("Primeira Marcha!");

  }else if (!digitalRead(segm)){
    lcd.print(" Segunda Marcha!");

      }else if (!digitalRead(term)){
    lcd.print("Terceira Marcha!");

      }else if (!digitalRead(quam)){
     lcd.print(" Quarta Marcha!");

       }else if (!digitalRead(quim)){
      lcd.print(" Quinta Marcha!");
      
      }else if (!digitalRead(rem)){
      lcd.print("<- MARCHA  RE ->");

  }else{
  lcd.print("  PONTO MORTO!  ");
  }
}
