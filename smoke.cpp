#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

/* ---------- PIN MAPPING ---------- */

// Ultrasonic Sensor
#define TRIG_PIN A3
#define ECHO_PIN A2

// Smoke Sensor
#define SMOKE_PIN A0

// Flame Sensors
#define FLAME_LEFT 4
#define FLAME_FRONT 11
#define FLAME_RIGHT 13

// Pump & Buzzer
#define PUMP_PIN A1
#define BUZZER_PIN 3

// L298N Motor Driver
#define enA 5
#define LM1 6
#define LM2 7
#define RM1 8
#define RM2 9
#define enB 10

// Bluetooth
#define BT_RX 12
#define BT_TX 2

/* ---------- SETTINGS ---------- */

#define DISTANCE_THRESHOLD 20
#define SMOKE_THRESHOLD 450
#define FIRE_TEMP_THRESHOLD 40

/* ---------- OBJECTS ---------- */

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial bluetooth(BT_TX, BT_RX);

/* ---------- SETUP ---------- */

void setup() {

  Serial.begin(9600);
  bluetooth.begin(9600);

  // Motor Pins
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Flame Sensors
  pinMode(FLAME_LEFT, INPUT);
  pinMode(FLAME_FRONT, INPUT);
  pinMode(FLAME_RIGHT, INPUT);

  // Smoke Sensor
  pinMode(SMOKE_PIN, INPUT);

  // Pump & Buzzer
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initial States
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Start Temperature Sensor
  mlx.begin();

  Serial.println("FIRE FIGHTING ROBOT STARTED");
}

/* ---------- MAIN LOOP ---------- */

void loop() {

  // Read Sensors
  int smokeLevel = analogRead(SMOKE_PIN);

  bool leftFlame = digitalRead(FLAME_LEFT);
  bool frontFlame = digitalRead(FLAME_FRONT);
  bool rightFlame = digitalRead(FLAME_RIGHT);

  float temperature = mlx.readObjectTempC();

  long distance = getDistance();

  /* ---------- SERIAL MONITOR ---------- */

  Serial.print("Smoke: ");
  Serial.print(smokeLevel);

  Serial.print(" | Temp: ");
  Serial.print(temperature);

  Serial.print(" | Distance: ");
  Serial.println(distance);

  /* ---------- PRIORITY 1 : SMOKE ---------- */

  if (smokeLevel > SMOKE_THRESHOLD) {

    stopRobot();

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(PUMP_PIN, HIGH);

    Serial.println("SMOKE DETECTED!");

    delay(500);

    return;
  }

  /* ---------- PRIORITY 2 : HIGH TEMPERATURE ---------- */

  if (temperature > FIRE_TEMP_THRESHOLD) {

    stopRobot();

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(PUMP_PIN, HIGH);

    Serial.println("HIGH TEMPERATURE DETECTED!");

    delay(500);

    return;
  }

  /* ---------- PRIORITY 3 : FLAME DETECTION ---------- */

  // Flame sensors are ACTIVE LOW
  if (!frontFlame) {

    Serial.println("FRONT FIRE DETECTED");

    extinguishFire();
  }

  else if (!leftFlame) {

    Serial.println("LEFT FIRE DETECTED");

    moveLeft();
  }

  else if (!rightFlame) {

    Serial.println("RIGHT FIRE DETECTED");

    moveRight();
  }

  /* ---------- PRIORITY 4 : OBSTACLE ---------- */

  else if (distance <= DISTANCE_THRESHOLD) {

    Serial.println("OBSTACLE DETECTED");

    stopRobot();
  }

  /* ---------- NORMAL MODE ---------- */

  else {

    moveForward();

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
  }

  /* ---------- BLUETOOTH CONTROL ---------- */

  if (bluetooth.available()) {

    char command = bluetooth.read();

    handleBluetooth(command);
  }

  delay(100);
}

/* ---------- ULTRASONIC FUNCTION ---------- */

long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  long distance = duration * 0.034 / 2;

  return distance;
}

/* ---------- MOTOR FUNCTIONS ---------- */

void moveForward() {

  analogWrite(enA, 170);
  analogWrite(enB, 170);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void moveBackward() {

  analogWrite(enA, 170);
  analogWrite(enB, 170);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void moveLeft() {

  analogWrite(enA, 180);
  analogWrite(enB, 180);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void moveRight() {

  analogWrite(enA, 180);
  analogWrite(enB, 180);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void stopRobot() {

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

/* ---------- FIRE EXTINGUISH ---------- */

void extinguishFire() {

  stopRobot();

  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(PUMP_PIN, HIGH);

  Serial.println("EXTINGUISHING FIRE...");
}

/* ---------- BLUETOOTH CONTROL ---------- */

void handleBluetooth(char cmd) {

  switch (cmd) {

    case 'F':
      moveForward();
      break;

    case 'B':
      moveBackward();
      break;

    case 'L':
      moveLeft();
      break;

    case 'R':
      moveRight();
      break;

    case 'S':
      stopRobot();
      break;

    case 'P':
      digitalWrite(PUMP_PIN, HIGH);
      break;

    case 'p':
      digitalWrite(PUMP_PIN, LOW);
      break;

    case 'Z':
      digitalWrite(BUZZER_PIN, HIGH);
      break;

    case 'z':
      digitalWrite(BUZZER_PIN, LOW);
      break;
  }
}