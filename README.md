# Fire Fighting Robot using Arduino UNO 🚒🔥

## Overview
This project is an Arduino-based Fire Fighting Robot capable of:

- Detecting fire using flame sensors
- Detecting smoke using MQ smoke sensor
- Measuring temperature using MLX90614 IR temperature sensor
- Avoiding obstacles using ultrasonic sensor
- Extinguishing fire using water pump
- Giving alerts using buzzer
- Manual Bluetooth control using smartphone

The robot automatically detects and moves toward fire and activates the water pump to extinguish it.

---

# Features 

- 🔥 Flame Detection
- 🌫 Smoke Detection
- 🌡 Temperature Monitoring
- 🚧 Obstacle Avoidance
- 💧 Automatic Water Pump Activation
- 📱 Bluetooth Manual Control
- 🚨 Emergency Buzzer Alert
- 🤖 Autonomous Navigation

---

# Components Required 🛠

| Component | Quantity |
|---|---|
| Arduino UNO | 1 |
| L298N Motor Driver | 1 |
| DC Motors | 2 |
| Robot Chassis | 1 |
| Flame Sensors | 3 |
| MQ Smoke Sensor | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| MLX90614 Temperature Sensor | 1 |
| Water Pump | 1 |
| Relay Module / Transistor | 1 |
| Buzzer | 1 |
| Bluetooth Module HC-05 | 1 |
| Battery Pack | 1 |
| Jumper Wires | Multiple |

---

# Pin Configuration 🔌

## Ultrasonic Sensor

| Sensor Pin | Arduino Pin |
|---|---|
| TRIG | A3 |
| ECHO | A2 |

---

## Flame Sensors

| Sensor | Arduino Pin |
|---|---|
| Left Flame | 4 |
| Front Flame | 11 |
| Right Flame | 13 |

---

## Smoke Sensor

| Sensor | Arduino Pin |
|---|---|
| MQ Sensor | A0 |

---

## Motor Driver (L298N)

| Driver Pin | Arduino Pin |
|---|---|
| ENA | 5 |
| IN1 | 6 |
| IN2 | 7 |
| IN3 | 8 |
| IN4 | 9 |
| ENB | 10 |

---

## Bluetooth Module

| Module Pin | Arduino Pin |
|---|---|
| RX | 12 |
| TX | 2 |

---

## Other Components

| Component | Arduino Pin |
|---|---|
| Pump | A1 |
| Buzzer | 3 |

---

# Working Principle ⚙️

## 1. Smoke Detection
The MQ smoke sensor continuously checks smoke levels.

If smoke exceeds threshold:
- Robot stops
- Buzzer turns ON
- Water pump activates

---

## 2. Temperature Monitoring
MLX90614 sensor monitors temperature.

If temperature exceeds safe limit:
- Robot activates emergency response
- Pump and buzzer turn ON

---

## 3. Fire Detection
Three flame sensors detect flame direction:
- Left
- Front
- Right

Robot movement:
- Front flame → Extinguish directly
- Left flame → Turn left
- Right flame → Turn right

---

## 4. Obstacle Avoidance
HC-SR04 ultrasonic sensor checks distance.

If obstacle detected within threshold:
- Robot stops automatically

---

## 5. Bluetooth Control
User can manually control robot using smartphone.

### Bluetooth Commands

| Command | Action |
|---|---|
| F | Move Forward |
| B | Move Backward |
| L | Move Left |
| R | Move Right |
| S | Stop |
| P | Pump ON |
| p | Pump OFF |
| Z | Buzzer ON |
| z | Buzzer OFF |

---

# Software Required 💻

- Arduino IDE
- Arduino UNO Board Package

---

# Required Libraries 📚

Install these libraries from Arduino Library Manager:

## 1. Adafruit MLX90614
Used for IR temperature sensor.

## 2. Adafruit BusIO
Dependency library.

## 3. Wire Library
Pre-installed with Arduino IDE.

## 4. SoftwareSerial
Pre-installed with Arduino IDE.

---

# Installation Steps 🚀

## Step 1
Install Arduino IDE.

Official Website:
https://www.arduino.cc/en/software

---

## Step 2
Install required libraries.

Go to:

```cpp
Sketch → Include Library → Manage Libraries
```

Search and install:
- Adafruit MLX90614
- Adafruit BusIO

---

## Step 3
Connect all hardware according to pin diagram.

---

## Step 4
Upload the code to Arduino UNO.

---

## Step 5
Power the robot using battery pack.

---

# File Structure 📂

```bash
FireFightingRobot/
│
├── FireFightingRobot.ino
├── README.md
└── circuit_diagram.png
```

---

# Important Notes ⚠️

- Flame sensors are ACTIVE LOW.
- Disconnect Bluetooth module during code upload if upload fails.
- Use external power supply for motors and pump.
- Do not power motors directly from Arduino.

---

# Future Improvements 🚀

- WiFi Monitoring
- Camera Integration
- GSM Alerts
- AI Fire Detection
- Automatic Mapping
- Voice Control

---

# Applications 🌍

- Industrial Fire Safety
- Home Automation
- Fire Detection Systems
- Smart Rescue Robotics
- Science Fair Projects
- Engineering Mini Projects

---

# Troubleshooting 🧰

## Error: `Wire.h not found`

### Solution:
- Use Arduino IDE
- Rename file to `.ino`

---

## Robot not moving

Check:
- Motor driver wiring
- Battery voltage
- PWM pins

---

## Bluetooth not working

Check:
- Baud rate = 9600
- Correct RX/TX connections

---

# Author 👨‍💻

**Krit Giri**

Arduino Fire Fighting Robot Project

---

# License 📄

This project is open-source and free to use for educational purposes.
