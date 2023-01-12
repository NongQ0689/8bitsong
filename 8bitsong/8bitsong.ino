#define BUZZER 21
#define But 23
hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.

int durations = 350 ;
int current_note = 0;

String song1 = {"deFsFddsdeFedeFdssdeFsFddsdeFedeFdssdddaaaaeeeaaadddsdeFsFdddeFedeFdssss"};

void IRAM_ATTR IO_INT_ISR()
{
  if(durations < 700) durations += 70;
  else durations = 350;
  Serial.println(durations);
}


void IRAM_ATTR onTimer()
{
  digitalWrite( BUZZER , !digitalRead(BUZZER)) ;
}

int NotetoHz (char note)
{
       if (note == 'c') return 1047;
  else if (note == 'd') return 1175;
  else if (note == 'e') return 1319;
  else if (note == 'f') return 1397;
  else if (note == 'F') return 1480;
  else if (note == 'g') return 1568;
  else if (note == 'a') return 1760;
  else if (note == 'b') return 1976;
  else if (note == 's') return 0; 
  else return 0;
}

void playsong(String songInput){

  char note = songInput[current_note];
  int frequency = NotetoHz( note );

  if(frequency != 0){
    My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
    timerAttachInterrupt(My_timer , &onTimer , true); // point to the ISR
    timerAlarmWrite(My_timer, 1000000/frequency/2 , true);  // set alarm every 1 sec
    timerAlarmEnable(My_timer);  // enable the alarm
  }else timerAlarmDisable(My_timer) ;
  /*
  Serial.print("playing : ");
  Serial.print(current_note);
  Serial.print(" : ");
  Serial.print(song[current_note]);
  Serial.print(" : ");
  Serial.println( frequency );
  */
  
  long start = millis(); 
  while(millis()<start+durations) {}     //delay = durations ms
  current_note = (current_note + 1) % songInput.length();
}


void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(But, INPUT_PULLUP);
  attachInterrupt(But, IO_INT_ISR, RISING); // interrupt on rising edge
}

void loop() {
  playsong(song1);
}




