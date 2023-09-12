#define BLADE_COUNT 2
#define SAMPLE_SIZE 80
int count_semirev = 0;
bool history = false;
bool signal = false;
long ms;
long reads_in_semirev = 0;
long reads_in_semirev_history = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);
  ms = millis();
}

void loop() {
  signal = digitalRead(9);
  reads_in_semirev++;
  if (signal == true && history == false){
    reads_in_semirev_history = (reads_in_semirev_history*count_semirev+reads_in_semirev)/(count_semirev+1);
    count_semirev++;
    reads_in_semirev = 0;
  }
  history = signal;
  if (count_semirev == SAMPLE_SIZE){
    float secs = ((float)(millis()-ms))/1000;
    Serial.print(millis());
    Serial.print(F("    "));
    Serial.print(reads_in_semirev_history);
    Serial.print(F("    "));
    Serial.println(60*(float)count_semirev/secs/BLADE_COUNT,4);
    count_semirev = 0;
    ms = millis();
  }
}