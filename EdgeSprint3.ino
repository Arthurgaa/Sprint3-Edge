#include <Wire.h>
#include <ESP32Servo.h>      // Biblioteca correta para o ESP32 Servo
#include <MPU6050.h>         // Biblioteca padrão do MPU6050

const int drsServoPin = 18;   // Pino para o servo DRS
const int curveServoPin = 19; // Pino para o servo de curvas
const int accelPotPin = 34;   // Pino analógico para o potenciômetro de aceleração
const int curvePotPin = 35;   // Pino analógico para o potenciômetro de curvas
const int buttonPin = 4;      // Pino do botão para controle manual do DRS
const int ledPin = 2;         // LED para indicar o estado do DRS

int buttonState = 0;          // Estado do botão manual
bool drsActivated = false;    // Estado atual do DRS
int drsThreshold = 2000;      // Limiar para ativar o DRS baseado na aceleração (ajustado para 12 bits do ADC do ESP32)

MPU6050 mpu;                  // Instância do sensor MPU6050
Servo drsServo;               // Instância do Servo 1 (DRS)
Servo curveServo;             // Instância do Servo 2 (Curvas)

// Função para mover o servo
void moveServo(Servo &servo, int angle) {
  servo.write(angle);  // Manda o servo para o ângulo correspondente
}

void setup() {
  // Configurações dos pinos
  pinMode(buttonPin, INPUT_PULLUP);  // Configura o botão com resistor pull-up interno
  pinMode(ledPin, OUTPUT);           // Configura o LED como saída

  // Inicializa os servos
  drsServo.attach(drsServoPin);      // Anexa o pino do DRS ao servo 1
  curveServo.attach(curveServoPin);  // Anexa o pino de curvas ao servo 2

  // Inicializa o MPU6050
  Wire.begin();
  mpu.initialize();                 // Inicializa o MPU6050
  if (mpu.testConnection()) {
    Serial.println("MPU6050 Conectado");
  } else {
    Serial.println("Falha ao conectar com o MPU6050");
  }

  Serial.begin(115200);
}

void loop() {
  // Lê o valor do potenciômetro de aceleração (simulando a aceleração)
  int accelValue = analogRead(accelPotPin);
  int accelAngle = map(accelValue, 0, 4095, 0, 180);  // Mapeia o valor para o ângulo do servo de 0 a 180
  moveServo(drsServo, accelAngle);  // Controla o servo DRS

  // Lê o valor do potenciômetro de curvas (simulando o movimento da asa nas curvas)
  int curveValue = analogRead(curvePotPin);
  int curveAngle = map(curveValue, 0, 4095, 0, 180);  // Mapeia o valor do potenciômetro para um ângulo de 0 a 180 graus
  moveServo(curveServo, curveAngle);  // Atualiza o segundo servo para simular as curvas

  // Leitura do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    drsActivated = !drsActivated;  // Alterna o estado do DRS ao pressionar o botão
    delay(500);  // Debouncing simples
  }

  // Atualiza o estado do DRS
  if (drsActivated) {
    digitalWrite(ledPin, HIGH);  // LED indica DRS ativo
  } else {
    digitalWrite(ledPin, LOW);   // LED indica DRS desativado
  }

  // Atualiza os dados do MPU6050
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);  // Obtém os dados de aceleração e giroscópio
  float roll = ax / 16384.0;  // Converte para a inclinação aproximada (g)

  // Controle do segundo servo baseado na inclinação do MPU6050
  if (drsActivated) {
    if (roll > 0.1) {
      moveServo(curveServo, 120);  // Asa vira para a esquerda
      Serial.println("Curva à Esquerda: Asa Ajustada.");
    } else if (roll < -0.1) {
      moveServo(curveServo, 60);   // Asa vira para a direita
      Serial.println("Curva à Direita: Asa Ajustada.");
    } else {
      moveServo(curveServo, 90);   // Asa centralizada
      Serial.println("Reta: Asa Central.");
    }
  }

  delay(100);  // Pequeno delay para estabilizar o loop
}
