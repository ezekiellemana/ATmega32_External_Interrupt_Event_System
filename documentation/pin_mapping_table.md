# ATmega32 Pin Mapping Table

| ATmega32 Pin | DIP-40 Pin # | Direction | Net Label | Connected Device | Notes |
| --- | --- | --- | --- | --- | --- |
| PB0 | 1 | Output | `LED_NORMAL` | R2 330 Ω → Green LED → GND | HIGH = normal LED ON |
| PB1 | 2 | Output | `LED_STOP` | R3 330 Ω → Red LED → GND | HIGH = stop LED ON |
| PB2 / INT2 | 3 | Input | `RECOVERY_INT2` | SW3 → GND, R7 10 kΩ → +5V | Recovery/reset interrupt |
| PB3 | 4 | Output | `BUZZER` | R4 1 kΩ → Q1 base → BZ1 driver | HIGH = buzzer ON |
| RESET | 9 | Input | `RESET` | R1 10 kΩ → +5V, reset button → GND | Active-LOW MCU reset |
| VCC | 10 | Power | `+5V` | +5V zone, C1 100 nF to GND | Digital supply |
| GND | 11 | Power | `GND` | GND zone | Ground |
| XTAL1 | 13 | Input | `XTAL1` | Y1 8 MHz crystal, C3 22 pF to GND | Clock input |
| XTAL2 | 14 | Output | `XTAL2` | Y1 8 MHz crystal, C4 22 pF to GND | Clock output |
| PD1 / TXD | 15 | Output | `SERIAL_TX` | J1 pin 2 | UART transmit, 9600 baud |
| PD2 / INT0 | 16 | Input | `EMERGENCY_INT0` | SW1 → GND, R5 10 kΩ → +5V | Emergency stop interrupt |
| PD3 / INT1 | 17 | Input | `EVENT_INT1` | SW2 → GND, R6 10 kΩ → +5V | Event pulse interrupt |
| AVCC | 30 | Power | `+5V` | +5V zone, C2 100 nF to GND | Must be tied to VCC |
| GND | 31 | Power | `GND` | GND zone | Ground |

## Unused Pins

The remaining ATmega32 pins are not used in this project. They are marked as no-connect in the schematic where appropriate.

## Power Notes

- VCC and AVCC are both connected to +5V.
- Both GND pins are connected to the GND zone.
- C1 and C2 are 100 nF decoupling capacitors.
- A B.Cu copper zone is used for GND.
- An F.Cu copper zone is used for +5V.
