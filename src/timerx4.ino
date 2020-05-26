//salidas
int RELE = 2;
int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;
int BUZZER = 7;
int TEST = 13;
//entradas
int BUT_ON = 10;
int BUT_OFF = 11;

#define START 1
#define STOP  2
#define TIMEOUT 3

#define STARTING 1
#define STOPED   2
#define RUNNING  3 

int index=LED1;
int state=STOPED;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(RELE, OUTPUT);
  pinMode(TEST, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUT_ON, INPUT);
  pinMode(BUT_OFF, INPUT);

  reset();
}

void loop() {
  //espera leer pulsadores:
  int but = readBut();
  
  if (but==START){
    
    //entro en otra etapa de espera y lectura de botones.
    //si no se pulsa nada por 5 segundos se activa el rele.
    state=STARTING;
    
    //voy cambiando de leds, para seleccionar el tiempo:
    digitalWrite(index, LOW);
    
    if (index==LED4) index=LED1;
    else index++;    
    
    digitalWrite(index, HIGH);
    
    delay(200);
    
  }
  else if (but==STOP){
    state=STOPED;
    buzzer(1000);
    reset();
  }
  else if (but==TIMEOUT){
    state=RUNNING;
    buzzer(2222); 
    digitalWrite(RELE, HIGH);
  }
}


//espera leer un boton y retorna START o STOP.
//suena el buzzer y hace de antirrebote.
int readBut(){
  int but;
  
  //antes de arrancar espero soltar el boton:
  while(digitalRead(BUT_ON) ==1 || digitalRead(BUT_OFF)==1) ;
  
  if (state==STARTING) but = waitButtonsOrStart();
  else if(state==STOPED) but = waitButtonsAndKitt();
  else if(state==RUNNING) but = waitStopOrFinish();
  
  buzzer(66);
  return but;
}

//solo espero pulsar el STOP o el tiempo de finalizacion.
int waitStopOrFinish(){
  int timeout;
  unsigned long m = micros();
  
  //base de tiempo: 240*N donde N son minutos.
  if (index==LED1) timeout=240*5;       // 5 min
  else if(index==LED2) timeout=240*10;  // 10 min
  else if(index==LED3) timeout=240*15;  // 15 min
  else  timeout=240*20;                 // 20 min
  
  while(digitalRead(BUT_OFF)==0) {
    if(--timeout  250ms * 1200 = 300000ms => 300segs => 5 min
  }
  return STOP;
}

//solo espera pulsar algun boton, y a los 5 segundos ABORT!
int waitButtonsOrStart(){
   for (int ms = 0; ms < 5000; ms++) {
      if (digitalRead(BUT_ON) == 1) return START;
      if (digitalRead(BUT_OFF) == 1) return STOP;
      delay(1);
    }
    return TIMEOUT;
}

//ayuda a la rutina de leer botones.
//mientras espera leer un boton, hace un juego de luces.
int waitButtonsAndKitt() {
  while (1) {
    
    //espera 4 segs, si se pulsa algo sale.
    for (int ms = 0; ms < 100; ms++) {
      if (digitalRead(BUT_ON) == 1) return START;
      if (digitalRead(BUT_OFF) == 1) return STOP;
      pulseLed(TEST);
    }
    
    // hace la rafaga de leds tipo KITT:
  
    pulseLed(LED1);
    pulseLed(LED2);
    pulseLed(LED3);
    pulseLed(LED4);

    for (int ms = 0; ms < 100; ms++) {
      if (digitalRead(BUT_ON) == 1) return START;
      if (digitalRead(BUT_OFF) == 1) return STOP;
      delay(1);
    }

    pulseLed(LED4);
    pulseLed(LED3);
    pulseLed(LED2);
    pulseLed(LED1);
  }
}

void pulseLed(int led) {
  digitalWrite(led, HIGH);
  delay(25);
  digitalWrite(led, LOW);
  delay(20);
}

void buzzer(int time) {
  digitalWrite(BUZZER, HIGH);
  delay(time);
  digitalWrite(BUZZER, LOW);
}

//apaga todo.
void reset() {
  state=STOPED;
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(RELE, LOW);

  for (int i = 0; i < 3; i++) {
    delay(50);
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, LOW);
  }
}
