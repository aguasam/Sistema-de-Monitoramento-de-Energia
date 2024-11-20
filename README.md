# Sistema de Monitoramento de Energia IoT

Este projeto utiliza um **Arduino** e um módulo **ESP8266** para monitorar tensão, corrente, potência e energia consumida (kWh) de forma remota através da plataforma **Blynk**. Os dados são enviados para um painel de controle (dashboard) acessível via dispositivos móveis ou web, permitindo o monitoramento em tempo real.

## 📋 Funcionalidades

- **Medição de Tensão (Vrms)**: Leituras em tempo real da tensão da rede elétrica.
- **Medição de Corrente (Irms)**: Leituras em tempo real da corrente consumida pela carga.
- **Cálculo de Potência (W)**: Potência consumida com base na tensão e corrente medidas.
- **Cálculo de Energia (kWh)**: Energia total consumida acumulada.
- **Monitoramento IoT via Blynk**: Dados acessíveis em um painel remoto através do aplicativo ou navegador.

---

## 🛠 Componentes Necessários

- **Arduino Uno/Nano**: 1 unidade  
- **Módulo Wi-Fi ESP8266**: 1 unidade  
- **Sensor de Corrente SCT-013**: 1 unidade  
- **Sensor de Tensão ZMPT101B**: 1 unidade  
- **Resistores**: 2x 10kΩ e 1x 300Ω  
- **Capacitor**: 10µF  
- **Cabo Micro-USB**: 1 unidade  

---

## 📐 Esquema de Conexão

1. **Arduino com ESP8266**:  
   - RX do ESP8266 → Pino 10 do Arduino  
   - TX do ESP8266 → Pino 11 do Arduino  
   - VCC e GND do ESP8266 → VCC e GND do Arduino  

2. **Sensores com Arduino**:  
   - Saída do ZMPT101B → Pino A0 do Arduino  
   - Saída do SCT-013 → Pino A1 do Arduino  

3. **Alimentação**:  
   - Todo o circuito é alimentado pelo Arduino (via cabo Micro-USB).  

---

## 🧩 Configuração do Blynk

1. **Crie um projeto no aplicativo Blynk**:
   - Acesse [Blynk](https://blynk.io) e crie uma conta.
   - Configure o projeto selecionando o dispositivo **Arduino** e conectividade via **ESP8266**.
   - Copie o **Auth Token** gerado pelo Blynk.

2. **Configuração dos Widgets**:
   - **Gauge** para **Tensão** (V) → Virtual Pin V0  
   - **Gauge** para **Corrente** (A) → Virtual Pin V1  
   - **Gauge** para **Potência** (W) → Virtual Pin V2  
   - **Label** para **Energia Consumida** (kWh) → Virtual Pin V3  

---

## ⚙ Configuração do Código

1. **Bibliotecas Necessárias**:
   - **EmonLib**: Para medições de tensão e corrente.  
   - **Blynk Library**: Para comunicação com o aplicativo Blynk.  

   Instale as bibliotecas via Gerenciador de Bibliotecas do Arduino IDE.

2. **Edite as Credenciais Wi-Fi** no código:
   ```cpp
   char ssid[] = "NOME_DA_REDE";  // Insira o nome da sua rede Wi-Fi
   char pass[] = "SENHA_DA_REDE"; // Insira a senha da sua rede Wi-Fi
   ```

3. **Insira o Auth Token do Blynk**:
   ```cpp
   char auth[] = "SEU_AUTH_TOKEN"; // Insira o token gerado pelo Blynk
   ```

---

## ▶ Como Executar

1. **Carregue o Código no Arduino**:
   - Conecte o Arduino ao computador e use a IDE do Arduino para fazer o upload do código.

2. **Abra o Monitor Serial**:
   - Configure o monitor serial para 9600 baud para verificar os dados enviados pelo Arduino.

3. **Verifique o Dashboard do Blynk**:
   - Acesse o aplicativo Blynk no celular ou o painel web para visualizar as leituras.

---

## 📊 Monitoramento no Blynk

Os dados medidos pelo sistema serão atualizados automaticamente no painel do Blynk a cada 5 segundos:

- **V0**: Tensão (Vrms)  
- **V1**: Corrente (Irms)  
- **V2**: Potência (W)  
- **V3**: Energia Consumida (kWh)  

---

**Desenvolvido por**: Carlos Vinicius Ferri Pereira  
**Última Atualização**: Novembro de 2024  
