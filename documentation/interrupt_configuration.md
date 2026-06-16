# Interrupt Configuration

## Button Wiring — Active-LOW Inputs

The emergency, event, and recovery/reset buttons are wired as active-LOW inputs. Each button connects the microcontroller input pin to GND when pressed.

When the button is not pressed, the input pin is held HIGH. When the button is pressed, the input pin goes LOW. This HIGH-to-LOW transition creates the falling edge used to trigger the external interrupt.

The firmware enables the ATmega32 internal pull-up resistors. The KiCad schematic and PCB also include external 10 kΩ pull-up resistors for the interrupt inputs. This is acceptable because the external pull-ups reinforce the HIGH level and make the schematic clear for the assignment.

---

## Interrupt Inputs

| Interrupt | MCU Pin | Net Label | Button | Pull-up |
| --- | --- | --- | --- | --- |
| INT0 | PD2 / DIP pin 16 | `EMERGENCY_INT0` | Emergency stop | 10 kΩ to +5V plus internal pull-up |
| INT1 | PD3 / DIP pin 17 | `EVENT_INT1` | Event pulse | 10 kΩ to +5V plus internal pull-up |
| INT2 | PB2 / DIP pin 3 | `RECOVERY_INT2` | Recovery/reset | 10 kΩ to +5V plus internal pull-up |

---

## Falling-Edge Trigger Configuration

### INT0 — Emergency Stop

INT0 uses PD2 and is configured for falling edge triggering.

```c
MCUCR |=  (1 << ISC01);
MCUCR &= ~(1 << ISC00);
```

### INT1 — Event Pulse

INT1 uses PD3 and is also configured for falling edge triggering.

```c
MCUCR |=  (1 << ISC11);
MCUCR &= ~(1 << ISC10);
```

### INT2 — Recovery / Reset

INT2 uses PB2. On ATmega32, INT2 uses the ISC2 bit in MCUCSR. Clearing ISC2 selects falling edge triggering.

```c
MCUCSR &= ~(1 << ISC2);
```

All interrupts are enabled through GICR:

```c
GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);
```

---

## ISR Behaviour

| Interrupt | Trigger | Firmware action |
| --- | --- | --- |
| INT0 emergency | Emergency button pressed | Sets `emergency_mode = 1`; red LED and buzzer turn ON; counting is locked |
| INT1 event | Event button/sensor pulse | Increments `event_count` only if `emergency_mode == 0` |
| INT2 recovery/reset | Recovery button pressed | If in emergency mode, returns to normal; if already normal, resets count to 0 |

---

## Debounce Logic

Mechanical push buttons can bounce and create several fast transitions during one press. The firmware prevents false multiple counts using a Timer0 millisecond tick and a 200 ms debounce window.

Timer0 creates a 1 ms system tick:

```text
Clock: 8 MHz
Prescaler: 64
OCR0: 124
Tick: 1 ms
```

Each external interrupt has its own last-accepted timestamp. An interrupt is accepted only when at least 200 ms has passed since the previous accepted interrupt on the same line.

```c
if ((now - last_int0_ms) >= DEBOUNCE_MS) {
    last_int0_ms = now;
    emergency_mode = 1;
}
```

This prevents button bounce from producing multiple counts or repeated emergency/recovery actions.
