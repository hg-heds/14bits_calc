#define BLADE_COUNT 2
#define SAMPLE_SIZE 80
#include <Servo.h>

long count_rev = 0;
bool history = false;
bool read = false;
long ms,tm;
int val;
float secs;
Servo esc;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  esc.attach(9,1000,2000); 
  ms = millis();
  tm = millis();
}

void loop() {
  read = digitalRead(5);
  if (read == true && history == false){
    count_rev++;
  }
  history = read;
  if (count_rev == SAMPLE_SIZE){
    secs = ((float)(millis()-ms))/1000;
    Serial.print(val);
    Serial.print("    ");
    Serial.println(60*(float)count_rev/secs/BLADE_COUNT,4);
    ms = millis();
    count_rev = 0;
  }
  if (millis()-tm > 100){
    val = analogRead(A0);
    val = map(val,0,1023,0,160);
    esc.write(val); 
    tm = millis();
  }
}
