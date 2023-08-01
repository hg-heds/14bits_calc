#define BLADE_COUNT 3
#define SAMPLE_SIZE 80
long count_rev = 0;
bool signal = false;
bool read = false;
long ms = millis();

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);
}

void loop() {
  read = digitalRead(9);
  if (read == true && signal == false){
    count_rev++;
  }
  signal = read;
  if (count_rev == SAMPLE_SIZE){
    float secs = ((float)(millis()-ms))/1000;
    Serial.print(millis());
    Serial.print("    ");
    Serial.print(secs);
    Serial.print("    ");
    Serial.println(60*(float)count_rev/secs/BLADE_COUNT,4);
    ms = millis();
    count_rev = 0;
  }
}