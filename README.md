# Projeto de Irrigação Automática com ESP32

Este repositório contém o código para o hardware do sistema de irrigação automática baseado no ESP32. O dispositivo se comunica com um aplicativo móvel via WebSocket, permitindo o monitoramento e controle remoto da umidade do solo e do sistema de irrigação.

## Funcionalidades

- **Leitura de Umidade do Solo**: O sensor de umidade conectado ao ESP32 faz a leitura do solo e envia os dados para o aplicativo móvel.
- **Controle de Irrigação**: O sistema liga ou desliga o motor de irrigação com base no nível de umidade do solo e nos limites definidos pelo usuário.
- **Comunicação via WebSocket**: O ESP32 atua como um servidor WebSocket, enviando dados em tempo real para o aplicativo móvel e recebendo comandos para ajustar os parâmetros de irrigação.
- **Configuração Remota**: O aplicativo móvel pode definir o nível de umidade desejado e o ID da planta, que são enviados ao ESP32 via WebSocket.

## Hardware Necessário

- **ESP32**
- **Sensor de Umidade do Solo**
- **Módulo Relé + Bomba d'água**
- **Bibliotecas Arduino**

## Conexões

| Componente       | Pino no ESP32 |
|------------------|---------------|
| Sensor de Umidade | 7             |
| Motor de Irrigação| 3             |

## Configuração

1. **Conexão Wi-Fi**:
   - Substitua `"Nome rede"` e `"Senha da rede"` no código pelas credenciais da sua rede Wi-Fi.
   ```cpp
   const char* ssid = "Nome rede";
   const char* password = "Senha da rede";
   ```

2. **Upload do Código**:
   - Use o Arduino IDE ou PlatformIO para compilar e enviar o código para o ESP32.

3. **Endereço IP**:
   - Após a conexão Wi-Fi, o endereço IP do ESP32 será exibido no monitor serial. Use esse IP para conectar o aplicativo móvel ao dispositivo.

## Funcionamento do Código

### Setup
- Inicializa a comunicação serial.
- Conecta-se à rede Wi-Fi.
- Inicia o servidor WebSocket na porta `81`.
- Configura os pinos do sensor e do motor.

### Loop
- Faz a leitura do sensor de umidade.
- Calcula a umidade atual com base na leitura do sensor.
- Liga ou desliga o motor de irrigação com base no limite de umidade definido.
- Cria um JSON com os dados de umidade, limite de umidade, ID da planta e mensagem de status.
- Envia o JSON para todos os clientes conectados via WebSocket.

### WebSocket Event
- **Conexão de Cliente**: Quando um cliente (aplicativo móvel) se conecta, uma mensagem de boas-vindas é enviada.
- **Desconexão de Cliente**: Quando um cliente se desconecta, uma mensagem é exibida no monitor serial.
- **Recebimento de Mensagem**: O ESP32 recebe mensagens do aplicativo móvel, que podem conter o novo limite de umidade ou o ID da planta. Esses valores são atualizados no sistema.

## Estrutura do JSON

### Enviado pelo ESP32
```json
{
  "id_plant": 1.0,
  "humidity_level": 60.0,
  "humidity": 55.0,
  "message": "Irrigação Ligada"
}
```

### Recebido pelo ESP32
```json
{
  "humidity_level": 65.0,
  "id_plant": 2.0
}
```

## Dependências

- **Biblioteca WiFi**: Para conexão Wi-Fi.
- **Biblioteca WebSocketsServer**: Para comunicação WebSocket.
- **Biblioteca ArduinoJson**: Para manipulação de JSON.

## Exemplo de Uso

1. Conecte o ESP32 à rede Wi-Fi.
2. Abra o aplicativo móvel e conecte-se ao endereço IP do ESP32.
3. Defina o nível de umidade desejado e o ID da planta no aplicativo.
4. O ESP32 ajustará o sistema de irrigação com base nos parâmetros definidos e enviará dados em tempo real para o aplicativo.

## Monitoramento Serial

O monitor serial exibe informações sobre o status da conexão Wi-Fi, eventos do WebSocket e dados enviados/recebidos. Use-o para depuração e verificação do funcionamento do sistema.


Aqui está a seção que você pode adicionar ao `README.md` para linkar o repositório do aplicativo web:


## Aplicativo Mobile

O aplicativo mobile que se comunica com este hardware está disponível em um repositório separado. Ele foi desenvolvido para monitorar e controlar o sistema de irrigação automática em tempo real, permitindo que os usuários visualizem a umidade do solo, ajustem os limites de irrigação e selecionem diferentes plantas.

### Repositório do Aplicativo Web

Você pode acessar o código-fonte do aplicativo web no seguinte repositório:

🔗 **[Repositório do Aplicativo Web](https://github.com/diegoCBorba/irriga-mais-mobile)**
