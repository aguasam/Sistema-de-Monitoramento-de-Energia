#define BLYNK_TEMPLATE_NAME "Medidor de energia" // Nome do projeto no Blynk
#define BLYNK_TEMPLATE_ID "TMPL2pa5SSsfdUSPT" // ID do template criado no Blynk
#define BLYNK_DEVICE_NAME "Arduino" // Nome do dispositivo configurado
#define BLYNK_AUTH_TOKEN "Zr7MEGtsfdJVvaz__lu8yt-ZSbpgZgAWYngJ" // Token de autenticação fornecido pelo Blynk
#define BLYNK_PRINT Serial // Configuração para exibir logs do Blynk no monitor serial

#define NUM_SAMPLES 10 // Número de amostras para cálculo da média da corrente

// Inclusão das bibliotecas necessárias para o projeto
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include "EmonLib.h"

// Credenciais para conexão com o Blynk e a rede Wi-Fi
char auth[] = BLYNK_AUTH_TOKEN; // Token de autenticação
char ssid[] = "NOME_DA_REDE";  // Insira o nome da sua rede Wi-Fi
char pass[] = "SENHA_DA_REDE"; // Insira a senha da sua rede Wi-Fi

// Configuração da comunicação com o módulo ESP8266
SoftwareSerial EspSerial(10, 11); // Pinos RX e TX usados pelo ESP8266
const int ESP8266_BAUD = 9600; // Velocidade da comunicação serial
ESP8266 wifi(&EspSerial); // Objeto que gerencia a comunicação com o ESP8266

// Buffer de leituras de corrente para cálculo da média
float currentReadings[NUM_SAMPLES];
int currentIndex = 0;

// Função para calcular a média das leituras de corrente
float getAverageCurrent() {
    float sum = 0.0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += currentReadings[i];
    }
    return sum / NUM_SAMPLES;
}

// Constantes de calibração dos sensores
const float vCalibration = 226; // Fator de calibração da tensão
const float currCalibration = 6; // Fator de calibração da corrente

// Objeto para monitoramento de energia
EnergyMonitor emon;

// Timer para executar medições periodicamente
BlynkTimer timer;

// Variáveis para cálculo de energia consumida
float kWh = 0.0; // Total de energia consumida em kWh
unsigned long lastMillis = millis(); // Marca temporal da última medição

void medidor(); // Declaração da função que realiza as medições

// Configuração inicial do sistema
void setup() {
    Serial.begin(9600); // Inicializa o monitor serial
    EspSerial.begin(ESP8266_BAUD); // Configura a comunicação com o ESP8266
    delay(10); // Pequeno atraso para estabilizar o sistema

    Blynk.begin(auth, wifi, ssid, pass); // Conecta o dispositivo ao Blynk

    // Configura os sensores de tensão e corrente
    emon.voltage(A0, vCalibration, 1.7); // Tensão: pino analógico, fator de calibração, deslocamento de fase
    emon.current(A1, currCalibration); // Corrente: pino analógico, fator de calibração

    // Configura o timer para executar medições a cada 5 segundos
    timer.setInterval(5000L, medidor);

    delay(1000); // Atraso adicional para estabilizar o sistema
}

// Loop principal do programa
void loop() {
    Blynk.run(); // Mantém a conexão com o aplicativo Blynk
    timer.run(); // Executa o timer configurado
}

// Função responsável por realizar medições e enviar dados ao Blynk
void medidor() {
    emon.calcVI(20, 2000); // Calcula valores de tensão e corrente (20 semi-ciclos, timeout de 2000ms)

    // Calcula energia consumida em kWh desde a última medição
    unsigned long currentMillis = millis();
    kWh += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
    lastMillis = currentMillis;

    // Atualiza o buffer de leituras de corrente
    currentReadings[currentIndex] = emon.Irms;
    currentIndex = (currentIndex + 1) % NUM_SAMPLES;

    // Calcula a média das leituras de corrente
    float averageIrms = getAverageCurrent();

    // Ajusta leituras muito baixas para zero
    if (averageIrms < 0.05) { 
        averageIrms = 0.0;
    } else {
        averageIrms -= 0.025; // Compensação de ruído
    }

    // Exibe dados no monitor serial
    Serial.print("Vrms: ");
    Serial.print(emon.Vrms);
    Serial.print("V\tIrms: ");
    Serial.print(averageIrms);
    Serial.print("A\tPower: ");
    Serial.print(averageIrms * emon.Vrms);
    Serial.print("W\tkWh: ");
    Serial.println(kWh);

    // Envia dados ao Blynk
    Blynk.virtualWrite(V0, emon.Vrms); // Tensão
    Blynk.virtualWrite(V1, averageIrms); // Corrente
    Blynk.virtualWrite(V2, averageIrms * emon.Vrms); // Potência
    Blynk.virtualWrite(V3, kWh); // Energia consumida
}
