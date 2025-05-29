# Sistema de Monitoramento da Qualidade da Água com IoT

Codigos e documentação do projeto de Sistema de Monitoramento da Qualidade da Água com IoT
![image](https://github.com/user-attachments/assets/431bbea4-0ee0-4ef1-9991-1b5eecd75972)
![image](https://github.com/user-attachments/assets/f119d0c4-b25c-445d-a72f-5e69a913756e)

## Descrição do Funcionamento e Uso para Reprodutibilidade
O sistema consiste em um dispositivo IoT capaz de monitorar, em tempo real, a temperatura, umidade do ar, qualidade do ar (via MQ-135) e a quantidade de sólidos dissolvidos (TDS) na água. O dispositivo coleta dados a cada 5 segundos e exibe localmente em um display LCD 20x4 com I2C e remotamente por uma interface web via protocolo MQTT utilizando o broker HiveMQ.

Para reproduzir:

Monte o hardware conforme o esquema apresentado (NodeMCU, sensores, ADS1115, display).

Suba o código via Arduino IDE.

Acesse a interface web HTML com Live Server no VS Code ou navegador local.

Visualize os dados recebidos em tempo real.

Opcionalmente, utilize um shield de expansão para facilitar conexões.

## Documentação do Código
O código principal está dividido em três partes:

### Configuração Wi-Fi e MQTT:

Conexão à rede local.

Conexão ao broker MQTT.

Publicação em tópicos como casa/sensores/temperatura, .../umidade, .../tds, .../ar.

### Leitura dos Sensores:

DHT22: dht.readTemperature(), dht.readHumidity().

ADS1115: leitura analógica dos canais A0 (MQ-135) e A1 (TDS).

Cálculo de níveis categorizados (Bom, Ruim etc.).

### Exibição:

LCD: mostra os dados em tempo real formatados.

HTML via MQTT.js: apresenta as leituras de forma visual.

Todas as bibliotecas usadas estão listadas no artigo, incluindo PubSubClient, Adafruit_ADS1X15, DHT, LiquidCrystal_I2C.


## Descrição do Hardware Utilizado
### Componente	| Descrição
NodeMCU ESP8266	Placa com Wi-Fi integrado, utilizada como controlador principal do sistema.
Shield de Expansão	Facilita conexões dos sensores e alimentação elétrica.
Sensor DHT22	Mede temperatura e umidade com boa precisão.
Sensor MQ-135	Detecta gases como CO2, amônia e benzeno para avaliar a qualidade do ar.
Sensor TDS	Mede o nível de sólidos dissolvidos na água (pureza da água).
ADS1115	Expansor analógico via I2C, necessário para o uso simultâneo de sensores analógicos.
Display LCD 20x4 com I2C	Mostra os dados diretamente no dispositivo, com backlight azul.
Protoboard + Jumpers	Para prototipagem.
Fonte 5V/12V	Fonte de alimentação via shield (opcional) ou micro-USB.
Caixa de Projeto (opcional)	Pode ser substituída por base plástica + fita dupla face.

![image](https://github.com/user-attachments/assets/cc330bed-8209-4998-ae8e-5f83aedd2399)

## Documentação das Interfaces, Protocolos e Módulos de Comunicação

### Protocolo MQTT:

Utilizado para comunicação entre o dispositivo e a interface web.

Cliente: PubSubClient na ESP8266.

Broker: HiveMQ (gratuito e público).

Tópicos: casa/sensores/temperatura, .../umidade, .../tds, .../ar.

### Protocolo I2C:

Usado para comunicação entre:

NodeMCU ↔ ADS1115

NodeMCU ↔ Display LCD

Pinos utilizados: D1 (SCL), D2 (SDA)

### Protocolo Digital:

DHT22 conectado ao pino D5 usando protocolo digital de um fio (one-wire).

### Plataforma Web (Interface):

Desenvolvida em HTML + JS.

Conexão via MQTT WebSocket: wss://broker.hivemq.com:8884/mqtt

Apresenta dados ao vivo com atualização dinâmica.

![image](https://github.com/user-attachments/assets/c57fa197-c23e-4432-89c4-61e02811f26e)
