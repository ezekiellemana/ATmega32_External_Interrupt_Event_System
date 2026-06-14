# ATmega32 Pin Mapping Table

## Signal Assignments

| ATmega32 Pin | DIP-40 Pin # | Direction | Net Label | Connected Device | Notes |
| --- | --- | --- | --- | --- | --- |
| PD2 / INT0 | 16 | Input | EMERGENCY_INT0 | Push button → GND | Internal pull-up enabled |
| PD3 / INT1 | 17 | Input | EVENT_INT1 | Push button / sensor → GND | Internal pull-up enabled |
| PB2 / INT2 | 3 | Input | RECOVERY_INT2 | Push button → GND | Internal pull-up enabled |
| PB0 | 1 | Output | LED_NORMAL | Green LED + 330 Ω → GND | HIGH = LED ON |
| PB1 | 2 | Output | LED_STOP | Red LED + 330 Ω → GND | HIGH = LED ON |
| PB3 | 4 | Output | BUZZER | Active buzzer → GND | HIGH = buzzer ON |
| PD1 / TXD | 15 | Output | SERIAL_TX | USB-TTL adapter RX | 9600 baud, 8N1 |
| RESET | 9 | Input | RESET | 10 kΩ to VCC; button to GND | Active LOW reset |
| XTAL1 | 13 | Input | XTAL1 | 8 MHz crystal / resonator | |
| XTAL2 | 14 | Output | XTAL2 | 8 MHz crystal / resonator | |
| VCC | 10 | Power | +5V | Regulated 5 V supply | |
| AVCC | 30 | Power | +5V | Regulated 5 V supply | Tie to VCC with 100 nF bypass |
| GND | 11, 31 | Power | GND | Common ground | Both GND pins must be connected |

## Unused Pins

All other ATmega32 pins (PA0–PA7, PC0–PC7, PD0, PD4–PD7, PB4–PB7) are unconnected in this design. In a production PCB, floating inputs should be pulled to a defined state to prevent spurious current draw.

## Power Bypass

Place a 100 nF ceramic capacitor between VCC and GND as close to pin 10 as possible, and another 100 nF between AVCC (pin 30) and GND. These decouple high-frequency noise from the supply rails.
