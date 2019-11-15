
/* Codice per allarme tensione scambi bloccata attivata
 *  e conseguente frittura dell'elettrocalamita
 * Utilizza sensore assorbimento corrente xxxx
 * 
 */
 
int timer; // definisco variabile per contatore per ritardo allarme
int ciclo; // definisco variabile per ciclo test iniziale buzzer

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  timer = 0; // azzero variabile
  ciclo = 0; // azzero variabile
  
  // prova allarme e relè
  
  delay(3000);
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(500);
  
  for (ciclo = 0 ; ciclo < 3 ; ciclo++) {
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    delay(200);
  }
  
  // fine prova allarme e relè
}

void loop() {
  int v = analogRead(A1);
  delay(100);
  if ( v > 200 ) {
    timer++; // aumento conteggio di 1 ad ogni ciclo finchè c'è lettura maggiore di 200
    delay(200);
    Serial.println(timer);
    Serial.print(v);
  }
    else {
    timer = 0; // resetto timer per resettare il ciclo di ritardo se non c'è più lettura di valore maggiore di 200
  }    
    if (timer == 10) {
      digitalWrite(6, HIGH); // stacco relè di tensione scambi se conteggio timer raggiunge 10
      digitalWrite(7, HIGH); // attivo buzzer
      delay(5000);
      digitalWrite(7, LOW); // disattivo buzzer
  }
}
