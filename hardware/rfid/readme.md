# RFID Hardware Setup (RC522 Example)

## Components
- RC522 RFID Reader Module
- RFID Tag/Card
- Arduino Uno / Mega / Raspberry Pi
- Jumper Wires

## Pin Connections (RC522 to Arduino UNO)
| RC522 Pin | Arduino UNO Pin |
|-----------|-----------------|
| SDA       | D10             |
| SCK       | D13             |
| MOSI      | D11             |
| MISO      | D12             |
| IRQ       | Not Connected   |
| GND       | GND             |
| RST       | D9              |
| 3.3V      | 3.3V            |

## Notes
- RC522 works on **3.3V** only.
- Use `MFRC522` library in Arduino for reading UID.
- UID will be sent via Serial to the C program for verification.
