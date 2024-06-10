#define BLADE_COUNT 2
#define SAMPLE_SIZE 8
#include <Servo.h>//Using servo library to control ESC
Servo esc; //Creating a servo class with name as esc
long count_rev = 0;
bool leitura = false;
bool read = false;
long ms = millis();
int val; //Creating a variable val
long count = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  esc.attach(9,1000,2000); 
}

void loop() {
    
  val = analogRead(A0);
  val = map(val,0,1023,0,170);
  esc.write(val); 
  Serial.println(val);
  
  count++;
  if (count >= 10000){
    count = 0;
    Serial.println(val);   
  }

  delay(10);

}
