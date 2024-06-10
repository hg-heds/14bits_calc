#define BLADE_COUNT 3
#define SAMPLE_SIZE 80
long int rotacoes = 0;
bool leitura = false;
bool leitura_anterior = false;
long int instante;

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);
  instante = millis();
}

void loop() {
  leitura = digitalRead(9);
  if (leitura == true && leitura_anterior == false){
    rotacoes++;
  }
  leitura_anterior = leitura;
  if (rotacoes == SAMPLE_SIZE){
    float secs = ((float)(millis()-instante))/1000;
    Serial.print(millis());
    Serial.print("    ");
    Serial.print(secs);
    Serial.print("    ");
    Serial.println(60*(float)rotacoes/secs/BLADE_COUNT,4);
    rotacoes = 0;
    instante = millis();
  }
}

1 - Thais Xavier de Souza (thais.8783858@aluno.mg.gov.br)
2 - Gabriel Soares Santos (gabrielssants.gss@gmail.com)
3 - Gabriel Brito Alkmim (bielbritto160@gmail.com)
4 - Leandro Castilho Feitosa Callado (leandrocallado2@gmail.com)
5 - Hugo Edmar Dias Santos (hugo.hedsts.u@gmail.com)