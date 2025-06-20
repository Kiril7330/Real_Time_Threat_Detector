# Real-Time Threat Scanner with Arduino + HC-SR04 + Servo

This project implements a real-time threat detection system using an Arduino Uno, an ultrasonic sensor (HC-SR04), and a servo motor. It continuously sweeps its surroundings and halts scanning when a nearby object is detected, using LEDs to indicate the threat state.

# Features

- Servo sweeps from 0° to 180° and back
- HC-SR04 measures distance at each angle
- Red LED blinks and scanning halts if object detected within danger range
- Green LED blinks when area is clear
- Serial monitor logs angle and distance in real-time

# Hardware Used

- Arduino Uno
- HC-SR04 Ultrasonic Distance Sensor
- SG90 Servo Motor
- Red LED + Green LED
- 2 × 220Ω resistors
- Breadboard & male-to-male jumper wires

# How It Works

1. The servo rotates in a sweeping motion (0° -> 180° -> 0°).
2. At each position, the HC-SR04 sensor checks the distance to an object.
3. If an object is detected within the defined `minThreatDistance` (e.g., 30 cm):
   - Red LED blinks
   - Servo pauses
   - System resumes scanning only after the object moves away
4. If no threat is detected:
   - Green LED blinks to indicate “clear”


