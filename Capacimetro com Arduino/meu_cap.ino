#include <LiquidCrystal.h> //inclui biblioteca lcd

#define carga         7          // Digital 11 vai carregar o capacitor
#define descarga      6          // Digital 10 vai descarregar o capacitor
#define resistor       3266.0F    // Resistor de carga utilizado no projeto, valores mais baixo                                   
#define capLoad        A0         // medida de tensão (carga no capacitor) no pino analógico 0

// ---  LCD ---
LiquidCrystal disp(13,  //RS no digital 13
                   12,  //EN no digital 12
                   11,  //D4 no digital 11
                   10,  //D5 no digital 10
                    9,  //D6 no digital  9
                    8); //D7 no digital  8

unsigned long Time01;             // Tempo inicial
unsigned long Time02;             // Tempo transcorrido
float microFarads;                // Armazena o valor da capacitância em µF
float nanoFarads;                 // Armazana o valor da capacitância em nF
float valorSerial = 0;                // Armazena o valor pra saída serial

// ------------------------------------------------ SETUP ---
void setup()
{
    Serial.begin(9600);
      Serial.println(" CAPACIMETRO");
    pinMode(carga, OUTPUT);         //Configura pino de carga como saída digital
       
    digitalWrite(carga, LOW);       //Inicializa pino de carga
    
    disp.begin(16, 2);              //Display lcd 16 x 2
    disp.setCursor(2,0);            //Posiciona cursor na coluna 3, linha 1
    disp.print("Capacimetro");      //Escreve no display

   

} //end setup

// ----------------------------------------------- Loop Infinito ---
void loop()
{
  
  digitalWrite(carga, HIGH);              //Saída de carga em nível alto (carrega o capacitor com a tensão de alimentação do Arduino)
  Time01 = millis();                       //Armazena a contagem de programa em mili segundos em Time01
  while(analogRead(capLoad) < 647){ }      // Aguarda até atingir 63,2% da tensão da fonte
  
  Time02 = millis() - Time01;              // Calcula o tempo transcorrido
  microFarads = ((float)Time02 / resistor) * 1000;     // Calcula a Capacitância em Micro Farads
  if (microFarads > 1)                //Capacitância maior que 1uF?
  {                                   //Sim...
    disp.setCursor(5,1);              //Posiciona cursor na coluna 6, linha 2
    disp.print((long)microFarads);    //Imprime valor atual da capacitância em uF
    disp.print(" uF");                //Imprime "uF"
    if (valorSerial != (long)microFarads){
      Serial.print((long)microFarads);
      Serial.println(F( "uF"));
      valorSerial = ((long)microFarads);
    }
   
  } //end if
  else
  {
    nanoFarads = microFarads * 1000.0;      // Converte uF para nF
    disp.setCursor(5,1);              //Posiciona cursor na coluna 6, linha 2
    disp.print((long)nanoFarads);     //Imprime valor atual da capacitância em nF
    disp.print(" nF");                //Imprime "nF"
    if (valorSerial != (long)nanoFarads){
      Serial.print((long)nanoFarads);
      Serial.println(F(" nF"));
      valorSerial = ((long)nanoFarads);
    }
    
  } //end else
  digitalWrite(carga, LOW);                //Pino de carga fica em nível baixo
  pinMode(descarga, OUTPUT);               //Pino de descarga configurado temporariamente como saída
  digitalWrite(descarga, LOW);             //Pino de descarga em nível baixo (descarrega o capacitor)
  while(analogRead(capLoad) > 0){ }         //Aguarda até que a tensão no capacitor chegue a zero
  pinMode(descarga, INPUT);                //Pino de descarga volta a ser entrada para maior impedancia 
  delay(200);                               //atualização das leituras
  
} //end loop


