<div align="center">

# 🚰 IoT Water Tank Monitoring System with Triple Modular Redundancy (TMR)

### Fault Tolerant System Final Project

Implementation of Triple Modular Redundancy (TMR) using ESP32 and three HC-SR04 ultrasonic sensors for reliable water level monitoring with real-time web dashboard visualization.

<img src="assets/banner.png" width="800">

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![TMR](https://img.shields.io/badge/Fault%20Tolerance-TMR-green)
![HC-SR04](https://img.shields.io/badge/Sensor-HC--SR04-orange)
![License](https://img.shields.io/badge/License-MIT-red)

</div>

---

# 📖 Project Overview

Traditional water tank monitoring systems generally rely on a single sensor. While inexpensive and simple to implement, this approach introduces a **Single Point of Failure (SPOF)**. When the sensor experiences malfunction, power disturbance, or environmental interference, the entire monitoring system may produce incorrect measurements and trigger wrong control decisions.

This project proposes a **Fault-Tolerant Water Tank Monitoring System** based on **Triple Modular Redundancy (TMR)**. Three HC-SR04 ultrasonic sensors are deployed redundantly and managed by an ESP32 microcontroller.

The system performs:

* Sequential sensor triggering
* Majority voting mechanism
* Fault detection
* Fault masking
* Graceful degradation
* Fail-safe operation

allowing the monitoring process to continue even when one sensor becomes faulty.

---

# 🎯 Objectives

The primary objectives of this project are:

* Implement Triple Modular Redundancy (TMR) on ultrasonic sensors.
* Increase reliability and dependability of water level monitoring.
* Detect transient and permanent sensor failures.
* Prevent incorrect control decisions caused by faulty sensor readings.
* Demonstrate practical fault tolerance concepts in embedded IoT systems.

---

# 🏗️ System Architecture

```text
            ┌──────────────┐
            │ HC-SR04 #1   │
            └──────┬───────┘
                   │
            ┌──────▼───────┐
            │ HC-SR04 #2   │
            └──────┬───────┘
                   │
            ┌──────▼───────┐
            │ HC-SR04 #3   │
            └──────┬───────┘
                   │
                   ▼

        ┌─────────────────────┐
        │      ESP32 MCU      │
        │                     │
        │ Sequential Trigger  │
        │ Fault Detection     │
        │ Majority Voting     │
        │ Fault Masking       │
        └─────────┬───────────┘
                  │
        ┌─────────▼───────────┐
        │ Web Dashboard       │
        │ Real-Time Monitor   │
        └─────────────────────┘
```

---

# ✨ Key Features

## Triple Modular Redundancy (TMR)

Three ultrasonic sensors simultaneously monitor the same water surface.

Benefits:

* Eliminates single point of failure
* Increases measurement reliability
* Allows fault masking

---

## Sequential Triggering

To avoid ultrasonic wave interference (crosstalk), sensors are triggered one at a time.

```text
Sensor 1 → Delay → Sensor 2 → Delay → Sensor 3
```

Advantages:

* Stable measurements
* Reduced noise
* Improved accuracy

---

## Fault Detection

The system computes:

1. Median value
2. Sensor deviation

Fault condition:

```text
|Sensor Reading - Median| > Threshold
```

Threshold:

```cpp
#define THRESHOLD 5.0
```

---

## Fault Masking

If one sensor fails:

```text
Sensor 1 = 20 cm
Sensor 2 = 21 cm
Sensor 3 = 85 cm (Fault)

Output = Average(S1,S2)
```

Faulty sensor is automatically ignored.

---

## Graceful Degradation

System remains operational with:

* 3/3 Sensors Active
* 2/3 Sensors Active

---

## Fail-Safe Mode

If two sensors fail:

```text
Active Sensors < 2
```

System enters:

```text
HALTED MODE
```

to prevent incorrect operation.

---

# 🌐 Web Dashboard Features

The dashboard provides real-time visualization of:

### Sensor Monitoring

* Sensor 1 Distance
* Sensor 2 Distance
* Sensor 3 Distance

### Voting Result

* Voted Median
* Final TMR Output

### System Health

* Active Sensors Counter
* System Reliability Status

### Fault Visualization

* Healthy Sensor
* Transient Fault
* Permanent Fault

### Fault History

Displays the latest detected fault events.

---

# 🛠 Hardware Requirements

| Component                 | Quantity |
| ------------------------- | -------- |
| ESP32                     | 1        |
| HC-SR04 Ultrasonic Sensor | 3        |
| Breadboard                | 1        |
| Jumper Wires              | Several  |
| Water Tank Prototype      | 1        |

---

# 🔌 Pin Configuration

| Sensor   | Trigger Pin | Echo Pin |
| -------- | ----------- | -------- |
| Sensor 1 | GPIO 5      | GPIO 18  |
| Sensor 2 | GPIO 19     | GPIO 21  |
| Sensor 3 | GPIO 22     | GPIO 23  |

---

# 📂 Repository Structure

```text
.
├── ESP32/
│   └── TMRHCSR04.ino
│
├── WebDashboard/
│   ├── index.html
│   ├── css/
│   └── js/
│
├── assets/
│   ├── architecture.png
│   ├── dashboard.png
│   └── wiring.png
│
└── README.md
```

---

# 🚀 Installation Guide

## Step 1 – Clone Repository

```bash
git clone https://github.com/USERNAME/REPOSITORY.git
```

---

## Step 2 – Install Arduino IDE

Download:

https://www.arduino.cc/en/software

---

## Step 3 – Install ESP32 Board

Arduino IDE:

```text
Tools
→ Board Manager
→ Search "ESP32"
→ Install
```

---

## Step 4 – Install Required Libraries

```cpp
WiFi.h
WebServer.h
```

---

## Step 5 – Configure WiFi

Open:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

Replace with your network credentials.

---

## Step 6 – Upload Firmware

Select:

```text
Board : ESP32 Dev Module
Port  : COMx
```

Upload:

```text
TMRHCSR04.ino
```

---

# 📱 Access Dashboard

After successful upload:

Open Serial Monitor.

Example output:

```text
Connected to WiFi
IP Address:
192.168.1.100
```

Open browser:

```text
http://192.168.1.100
```

Dashboard will appear automatically.

---

# 🧪 Fault Injection Testing

## Scenario 1 — Normal Operation

Expected:

```text
3/3 Active Sensors
System Normal
```

---

## Scenario 2 — Permanent Fault

Disconnect Echo pin of one sensor.

Expected:

```text
2/3 Active Sensors
Masking Active
System Operational
```

---

## Scenario 3 — Transient Fault

Place an obstacle briefly in front of one sensor.

Expected:

```text
Transient Fault Detected
Ignored by Voter
```

---

## Scenario 4 — Multiple Faults

Disconnect two sensors.

Expected:

```text
CRITICAL
FAIL-SAFE MODE
HALTED
```

---

# 📈 Fault Tolerance Mechanism

```text
Sensor Reading
      │
      ▼
 Median Calculation
      │
      ▼
 Fault Detection
      │
      ▼
 Fault Isolation
      │
      ▼
 Majority Voting
      │
      ▼
 Final Output
```

---

# 📚 Concepts Implemented

* Fault Tolerance
* Hardware Redundancy
* Triple Modular Redundancy (TMR)
* Majority Voting
* Fault Detection
* Fault Masking
* Graceful Degradation
* Fail-Safe System
* Dependability
* Reliability Engineering
* Embedded IoT Systems

---

# 👨‍💻 Team Members

| Name                    | NIM             |
| ----------------------- | --------------- |
| Faris Arinanta          | 235150300111045 |
| Bakhitah Cinta Syahirah | 235150301111037 |
| Phylicia Ilunary Nyo    | 235150301111012 |
| Adhitya Noer Effendi    | 235150307111024 |

---

# 🎓 Course Information

Fault Tolerant System (CCE60309)

Computer Engineering

Faculty of Computer Science

Universitas Brawijaya

2026

---

# 📄 License

This project is developed for academic and educational purposes as part of the Fault Tolerant System Final Project.
