# HOME-AUTOMATION-USING-LPC2129

A microcontroller-based home automation system using **LPC2129** with Bluetooth control for appliances via relays and motor. Developed using Keil MDK-ARM.

## Features
- 📶 Bluetooth control via UART (HC-05/HC-06 module)
- 🔌 Control 2 relays (lights/fans)
- 🚪 DC motor control (for gates/curtains)
- 📟 16x2 LCD for status display
- 📲 Smartphone command interface
- ❌ Invalid command detection

## Hardware Components
- LPC2129 ARM7 Microcontroller
- Bluetooth Module (HC-05/HC-06)
- 16x2 LCD Display
- 5V Relays (x2)
- DC Motor with Driver
- Power Supply (5V/3.3V)
- Push Buttons (for reset)

## Software
- Keil MDK-ARM IDE
- Serial Terminal App (TeraTerm/Arduino)
- Flash Magic (for programming)

## Setup
1. **Hardware Connection**
   - Connect Bluetooth TX->P0.9, RX->P0.8
   - Wire LCD to PORT0 (Data: P0.0-P0.7, RS-P0.16, EN-P0.17)
   - Connect Relays to P0.10 & P0.11
   - Motor Driver to P0.12 & P0.13

2. **Software Setup**
   ```bash
   git clone https://github.com/yourusername/lpc2129-home-automation.git
   Open project in Keil uVision
   Build project (Project -> Build Target)
   Flash using Flash Magic
