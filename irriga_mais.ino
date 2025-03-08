#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

int SENSOR = 7;
int MOTOR = 3;

float limiteHumidade = 60.0;
float idPlanta = -1.0;

const char* ssid = "Nome rede";
const char* password = "Senha da rede";
char* mensagem = "Irrigação Desligada";

// Criando um servidor WebSocket na porta 81
WebSocketsServer webSocket(81);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Aguarda conexão Wi-Fi
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP do ESP32-S3: ");
    Serial.println(WiFi.localIP());

    // Inicia o WebSocket
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    pinMode(MOTOR, OUTPUT);
    digitalWrite(MOTOR, HIGH);
}

void loop() {
    webSocket.loop();

    // Faz a leitura do Sensor
    int umidade_atual = analogRead(SENSOR);
    float umidade = (((4095.0 - umidade_atual)*100) /3000.0);

    if (umidade < limiteHumidade){
      mensagem = "Irrigação Ligada";
      digitalWrite(MOTOR, LOW);
    }else{
      mensagem = "Irrigação Desligada";
      digitalWrite(MOTOR, HIGH);
    }

    // Criando JSON
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["id_plant"] = idPlanta;
    jsonDoc["humidity_level"] = limiteHumidade;
    jsonDoc["humidity"] = umidade;
    jsonDoc["message"] = mensagem;

    // Convertendo JSON para string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Enviando para todos os clientes conectados
    webSocket.broadcastTXT(jsonString);

    Serial.println("Enviado: " + jsonString);

    delay(500); // Enviar a cada 5 segundos
}

// Manipula eventos do WebSocket
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    if (type == WStype_CONNECTED) { 
        Serial.printf("Cliente [%u] conectado!\n", num);

        StaticJsonDocument<200> jsonMessage;
        jsonMessage["message"] = "Cliente conectado";

        String jsonString;
        serializeJson(jsonMessage, jsonString);
        webSocket.broadcastTXT(jsonString);

    } else if (type == WStype_DISCONNECTED) {
        Serial.printf("Cliente [%u] desconectado!\n", num);

    } else if (type == WStype_TEXT) {
        // Mensagem recebida do cliente
        String message = String((char*)payload).substring(0, length);
        Serial.printf("Mensagem recebida de [%u]: %s\n", num, message.c_str());

        StaticJsonDocument<200> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, message);

        if (error) {
            Serial.println("Erro ao parsear JSON!");
            return;
        }

        if (jsonDoc.containsKey("humidity_level")) {
            limiteHumidade = jsonDoc["humidity_level"].as<float>();
            Serial.printf("Novo limite de humidade: %.2f\n", limiteHumidade);
        }

        if (jsonDoc.containsKey("id_plant")) {
            idPlanta = jsonDoc["id_plant"].as<float>();
            Serial.printf("Novo id de planta: %.2f\n", idPlanta);
        }

        StaticJsonDocument<200> jsonMessage;
        jsonMessage["message"] = "Nova planta setada";

        String jsonString;
        serializeJson(jsonMessage, jsonString);
        webSocket.broadcastTXT(jsonString);
    }
}