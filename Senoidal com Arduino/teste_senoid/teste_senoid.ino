unsigned long t0;
int entrada;
void setup() {
pinMode(9, OUTPUT); 
pinMode(A0, INPUT); 
t0 = millis();

TCCR1B = 0x01;
}

void loop() {
entrada = analogRead(A0);
analogWrite(9, (int) (255.0 * 0.5 *(1.0 + sin( (float) ((millis()-t0) % 1000) * 2.0 * 3.14 * 5.0 / entrada)))); 
}
