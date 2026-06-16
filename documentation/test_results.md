# Test Results

The tests below were captured from the SimulIDE simulation using the final firmware HEX file `firmware/hex/emergency_event_counter.hex`. The screenshots are stored in `simulide/screenshots/`.

| No. | Test case | Expected output | Observed output | Evidence file | Result |
|---:|---|---|---|---|---|
| 1 | Normal startup | Green LED ON, red LED OFF, buzzer OFF, serial shows NORMAL mode with count 0. | The system starts in NORMAL mode and the serial terminal shows count 0. | `01_normal_startup.png` | PASS |
| 2 | Single event pulse | Pressing Event button once increments the event count to 1. | The serial terminal shows NORMAL mode with count 1. | `02_single_event_count.png` | PASS |
| 3 | Multiple event pulses | Repeated event pulses increase the count step by step. | The serial terminal shows the count increasing after multiple event button presses. | `03_multiple_event_count.png` | PASS |
| 4 | Emergency stop | Emergency button activates emergency mode; red LED and buzzer turn ON, normal counting stops. | The serial terminal shows EMERGENCY STOP mode while the red LED/buzzer state is visible. | `04_emergency_stop.png` | PASS |
| 5 | Event during emergency | Pressing Event during emergency must not increase the count. | The count remains unchanged while the system stays in EMERGENCY STOP mode. | `05_counting_lockout.png` | PASS |
| 6 | Recovery mode | Pressing Recovery while in emergency returns system to NORMAL mode and preserves the current count. | The serial terminal returns to NORMAL mode and keeps the previous count. | `06_recovery_mode.png` | PASS |
| 7 | Reset in normal mode | Pressing Recovery/Reset again in normal mode resets the event count to 0. | The serial terminal shows NORMAL mode with count 0. | `07_reset_normal_mode.png` | PASS |

## Simulation evidence

- Screenshots folder: `simulide/screenshots/`
- Contact sheet: `documentation/evidence/simulide_screenshots_contact_sheet.jpg`
- HEX file used: `firmware/hex/emergency_event_counter.hex`
- MCU frequency used in SimulIDE: 8 MHz
- Serial terminal setting: 9600 baud, 8 data bits, 1 stop bit
