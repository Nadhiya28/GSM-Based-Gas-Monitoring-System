# GSM-Based Gas Level Monitoring System

This Arduino project monitors the weight of an LPG gas cylinder using a load cell (HX711 module). When the gas level drops below a set threshold, it sends an SMS alert via a GSM module to notify the user for a refill.

## Components Used

- Arduino UNO / Nano
- HX711 Load Cell Amplifier
- Load Cell (0–5 kg or more, based on requirement)
- GSM Module (SIM800L / SIM900)
- Resistors, Jumper wires, Breadboard
- 12V Power Supply (if using SIM800L)

## Features

- Real-time gas weight monitoring
- Low gas level detection
- Automatic SMS alert to registered mobile number
- Simple serial output for debugging
- Prevents repeated SMS with alert flag logic

## How It Works

1. The load cell reads the weight of the gas cylinder.
2. If the weight drops below the defined threshold (e.g., 2000g), the system:
   - Sends an SMS alert via GSM.
   - Avoids repeated alerts using a flag.
3. Once the gas is refilled and the weight goes above the threshold, the flag resets.

## Circuit Connections

| Component        | Arduino Pin |
|------------------|-------------|
| HX711 DT         | D3          |
| HX711 SCK        | D2          |
| GSM Module TX    | D8          |
| GSM Module RX    | D7          |
| Load Cell Power  | VCC / GND   |
| GSM Module Power | External 12V (if needed) |

**Note**: Use a voltage divider or logic level converter for GSM RX if needed.

## Code Overview

- Initializes HX711 and GSM.
- Calibrates the scale using `scale.set_scale()`.
- Reads weight every 5 seconds.
- Sends SMS if weight < 2000g.
- Resets alert flag when weight is back to normal.

## SMS Format

> “Low gas alert: Please book a refill.”

Change the phone number in the code:
```cpp
gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");

## license
This project is open-source and free to use under the MIT License.
