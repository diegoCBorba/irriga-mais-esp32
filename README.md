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

---
![Image](https://github.com/user-attachments/assets/7a3cd997-1b63-448f-b355-77a82241f723)

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

## Melhorias possíveis

- Adicionar Controle de Irrigação por Horário:
   - Além de controlar a irrigação com base na umidade do solo, você pode permitir que o usuário defina horários específicos para ativar a irrigação, independentemente da umidade. Isso pode ser útil em situações em que a irrigação é necessária em horários programados.     
- Notificações para o Usuário:
   - Integrar notificações no aplicativo móvel ou até mesmo alertas por e-mail/SMS quando a umidade estiver fora do intervalo ideal ou quando o sistema de irrigação estiver ativado/desativado.
- Aprimorar o Algoritmo de Leitura de Umidade:
   - Implementar uma média móvel ou um filtro de suavização nos dados de umidade do solo para evitar flutuações rápidas nas leituras e proporcionar um controle mais estável.
- Salvar relatórios via CSV:
   - Adição de um espaço que possibilite baixar um arquivo csv com as informações do relatório.
   - Melhorar a visualização do gráfico.
   - Adicionar novas formas de visualização dos dados do relatório.

## Ideias para expansão

- Adicionar Suporte para Múltiplos Sensores de Umidade:
   - Monitorar mais de uma planta ou área de irrigação, seria interessante adicionar suporte para múltiplos sensores de umidade. O ESP32 poderia gerenciar vários sensores e o aplicativo móvel permitiria a seleção de diferentes áreas de irrigação.
- Suporte a Conectividade de Nuvem:
  - Você poderia integrar o sistema com plataformas de nuvem como AWS IoT ou Google Cloud para armazenar dados históricos de umidade e irrigação. Isso permitiria monitorar e ajustar a irrigação remotamente, mesmo fora de sua rede local.
- Inteligência Artificial ou Algoritmos de Aprendizado de Máquina:
   - Em um estágio mais avançado, implementar algoritmos de aprendizado de máquina para prever quando as plantas precisam de irrigação com base em variáveis como clima (temperatura, umidade do ar) e o tipo de planta.
- Adicionar Suporte para Múltiplos Tipos de Sensores:
  - Sensor de Temperatura e Umidade do Ar (DHT11/DHT22):
      - A umidade e a temperatura do ar podem influenciar diretamente a evaporação da água do solo. Incorporar um sensor de temperatura e umidade do ar (como o DHT11 ou DHT22) ajudaria a entender melhor as condições climáticas que afetam a irrigação, ajustando os parâmetros de irrigação com base na previsão do tempo local.
   - Sensor de Luz (LDR - Light Dependent Resistor):
      - A intensidade da luz pode impactar a evaporação e a fotossíntese das plantas. Um sensor LDR poderia ser utilizado para medir a intensidade da luz no ambiente e ajustar o sistema de irrigação com base na quantidade de luz que as plantas estão recebendo, ajudando a otimizar o consumo de água.
   - Sensor de Temperatura do Solo (NTC ou termistor):
      - Sensores de temperatura do solo podem ser utilizados para monitorar as condições térmicas do solo. A temperatura do solo pode influenciar a taxa de absorção de água pelas raízes das plantas, e essa informação pode ser usada para melhorar o momento da irrigação, já que o solo quente pode precisar de mais irrigação.
   - Sensor de pH do Solo:
      - O pH do solo também afeta a absorção de nutrientes pelas plantas. Embora não seja um indicador direto da necessidade de irrigação, saber o pH do solo pode ajudar a otimizar as condições gerais para o crescimento das plantas, ajustando o regime de irrigação com base em um pH mais ideal.
   - Sensor de Condutividade Elétrica (EC):
     - Esse sensor mede a salinidade do solo. Em solos salinos, a capacidade de retenção de água é afetada, e as plantas podem não absorver água corretamente. O sensor EC pode ser útil para ajustar a irrigação com base na salinidade do solo.
- Adicionar suporte a múltiplos dispositivos de irrigação.

## Aplicativo Mobile

O aplicativo mobile que se comunica com este hardware está disponível em um repositório separado. Ele foi desenvolvido para monitorar e controlar o sistema de irrigação automática em tempo real, permitindo que os usuários visualizem a umidade do solo, ajustem os limites de irrigação e selecionem diferentes plantas.

### Repositório do Aplicativo Mobile

Você pode acessar o código-fonte do aplicativo web no seguinte repositório:

🔗 **[Repositório do Aplicativo Web](https://github.com/diegoCBorba/irriga-mais-mobile)**
