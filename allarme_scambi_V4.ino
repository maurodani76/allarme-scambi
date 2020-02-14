/* Codice per allarme tensione scambi bloccata attivata
 *  e conseguente frittura dell'elettrocalamita
 * Utilizza sensore assorbimento corrente ACS712 da 5 ampere
 * Utilizza un pezzo di codice trovato su youtube per eseguire un ciclo di misura della corrente in AC
 */
 
int timer; // definisco variabile per contatore per ritardo allarme
int ciclo; // definisco variabile per ciclo test iniziale buzzer

float current;
const int currentPin = A1;
const unsigned long sampleTime = 100000UL;
const unsigned long numSamples = 250UL;
const unsigned long sampleInterval = sampleTime/numSamples;
const int adc_zero = 516;

void setup() {
  // Serial.begin(9600);
  pinMode(6, OUTPUT); // uscita relè
  pinMode(7, OUTPUT); // uscita buzzer
  pinMode(LED_BUILTIN, OUTPUT);

  timer = 0; // azzero variabile
  ciclo = 0; // azzero variabile
  
  // prova relè e allarme
  
  delay(3000);
  digitalWrite(6, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
  for (ciclo = 0 ; ciclo < 3 ; ciclo++) {
    digitalWrite(7, HIGH);
    delay(50);
    digitalWrite(7, LOW);
    delay(250);
  }
  
  // fine prova allarme e relè
}

void loop() {
  CurrentSense(); // richiama il codice che misura la corrente
  // Serial.println(current);
  delay(300);
  if ( current > 0.5 ) {
    timer++; // aumento conteggio di 1 ad ogni ciclo finchè c'è lettura maggiore di 0.5
    delay(200);
    // Serial.println(timer);
  }
    else {
    timer = 0; // resetto timer per resettare il ciclo di ritardo se non c'è più lettura di valore maggiore di 0.5
  }    
    if (timer == 5) {
      digitalWrite(6, HIGH); // stacco relè di tensione scambi se conteggio timer raggiunge 5 (equivale a 2,5 secondi)
      digitalWrite(LED_BUILTIN, HIGH); // accendo led rosso built_in
      digitalWrite(7, HIGH); // attivo buzzer
      delay(5000);
      digitalWrite(7, LOW); // disattivo buzzer
  }
}

void CurrentSense()

{

 unsigned long currentAcc = 0;
 unsigned int count = 0;
 unsigned long prevMicros = micros() - sampleInterval;
 while (count < numSamples)
 {
   if (micros() - prevMicros >= sampleInterval)
   {
     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     ++count;
     prevMicros += sampleInterval;
   }
 }
 
 float rms = (sqrt((float)currentAcc/(float)numSamples) * (50 / 1024.0));
 rms=rms-0.10;
  if (rms<0.20)
  {
  rms=0;
  }

current=rms;

}
