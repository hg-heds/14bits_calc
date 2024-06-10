long int rotacoes = 0;
bool leitura = false;
bool leitura_anterior = false;
long int instante;
float tempo_decorrido;

void setup() {
    Serial.begin(9600);
    pinMode(9,INPUT);
    instante = millis();
    Serial.println("Starting...");
}

void loop() {
    leitura = digitalRead(9);
    if (leitura == true && leitura_anterior == false){
        rotacoes++;
    }
    leitura_anterior = leitura;
    if (rotacoes == 10){
        tempo_decorrido = (millis() - instante)/1000.0;
        Serial.println(60.0*rotacoes/tempo_decorrido/2,4);
        rotacoes = 0;
        instante = millis();
    }
}