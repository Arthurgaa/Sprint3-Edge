# Projeto de Controle Automático de Asa Traseira (DRS) com ESP32

## Descrição

Este projeto implementa um sistema de controle automático para a asa traseira (DRS) de um veículo de corrida, utilizando o microcontrolador ESP32. Ele simula a dinâmica de aceleração e curvas, controlando dois servos motores para ajustar a asa traseira. O sistema também utiliza o sensor MPU6050 para detecção de movimento, como aceleração e giroscópio, oferecendo controle dinâmico baseado na inclinação do veículo.

## Integrantes

- **Arthur Galvão Alves** - RM554462
- **Felipe Braunstein e Silva** - RM554483
- **Jefferson Junior Alvarez Urbina** - RM558497
- **Eduardo da Silva Lima** - RM554804

## Funcionalidades

- **Controle Automático do DRS:** A posição da asa traseira é ajustada automaticamente com base na aceleração medida pelo potenciômetro ou pelo sensor MPU6050.
- **Simulação de Curvas:** O sistema simula a movimentação da asa em curvas, ajustando-a dinamicamente de acordo com o valor lido do segundo potenciômetro.
- **Controle Manual do DRS:** Um botão permite ativar/desativar manualmente o DRS, indicando seu status através de um LED.
- **Integração com MPU6050:** A inclinação do veículo nas curvas é detectada, ajustando automaticamente a asa para melhorar o desempenho aerodinâmico.

## Componentes Utilizados

- **ESP32:** Controlador principal.
- **MPU6050:** Sensor de movimento e giroscópio para detectar a inclinação.
- **Servos Motores:** Dois servos para controlar o ângulo da asa traseira em aceleração e curvas.
- **Potenciômetros:** Dois potenciômetros para simular a aceleração e o movimento em curvas.
- **Botão e LED:** Para controle manual do DRS e indicação do estado.

## Esquemático

- **Servo DRS** conectado ao pino GPIO 18.
- **Servo de Curvas** conectado ao pino GPIO 19.
- **Potenciômetro de Aceleração** no pino ADC 34.
- **Potenciômetro de Curvas** no pino ADC 35.
- **Botão de Controle Manual** no pino GPIO 4.
- **LED Indicador** no pino GPIO 2.

### Bibliotecas Utilizadas

- `ESP32Servo.h`: Para o controle dos servos no ESP32.
- `MPU6050.h`: Para a leitura dos dados do sensor MPU6050.
- `Wire.h`: Para comunicação I2C com o MPU6050.

### Instruções de Instalação

1. Clone este repositório.
2. Instale as bibliotecas necessárias na IDE Arduino.
3. Faça o upload do código para o ESP32.
4. Conecte os componentes conforme o esquemático e execute o projeto.

