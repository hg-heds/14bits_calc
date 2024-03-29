#define BLADE_COUNT 3
#define SAMPLE_SIZE 80
long count_semirev = 0;
bool history = false;
bool signal = false;
long ms;

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);
  ms = millis();
}

void loop() {
  signal = digitalRead(9);
  if (signal == true && history == false){
    count_semirev++;
  }
  history = signal;
  if (count_semirev == SAMPLE_SIZE){
    float secs = ((float)(millis()-ms))/1000;
    Serial.print(millis());
    Serial.print("    ");
    Serial.print(secs);
    Serial.print("    ");
    Serial.println(60*(float)count_semirev/secs/BLADE_COUNT,4);
    count_semirev = 0;
    ms = millis();
  }
}