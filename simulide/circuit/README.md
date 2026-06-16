# SimulIDE Circuit Wiring Guide

## Before You Start

This guide tells you exactly how to wire the ATmega32 Emergency Stop and Event Counter circuit in SimulIDE. Read every step before clicking anything.

> **Important — Active-LOW buttons:**
> All three push buttons in this design connect the MCU pin to GND when pressed.
> The firmware enables internal pull-up resistors on those pins, so they sit at 5 V (logic HIGH) when the button is open.
> Pressing the button pulls the pin to GND (logic LOW) — this falling edge fires the interrupt.
> **Do NOT wire any button to 5 V. Always wire the second button terminal to GND.**

---

## Step 1 — Open SimulIDE and Place the ATmega32

1. Launch **SimulIDE**.
2. In the left panel, expand **Micro** → **AVR** → **Atmega** and find **ATmega32** (or search "ATmega32" in the search bar).
3. Drag the **ATmega32** onto the canvas.
4. Right-click the chip → **Properties** (or double-click).
5. Set **Frequency** to `8000000` (8 MHz).
6. Right-click the chip → **Load Firmware** → browse to:

   ```text
   firmware/hex/emergency_event_counter.hex
   ```

   Click **Open**. The firmware path will appear in the component properties.

---

## Step 2 — Power and Ground Connections

Connect power rails first so nothing floats.

| ATmega32 pin label | DIP-40 pin # | Connect to |
| --- | --- | --- |
| VCC | 10 | 5 V supply node (SimulIDE VCC component, or power rail) |
| AVCC | 30 | 5 V supply node (same rail as VCC) |
| GND | 11 | GND node |
| GND | 31 | GND node (both GND pins must be wired) |

In SimulIDE, drag a **VCC** power node and a **GND** power node from the **Sources** panel, then wire them to the pins listed above.

---

## Step 3 — Emergency Stop Button (INT0 on PD2)

This button triggers the emergency stop the moment it is pressed.

1. From the panel, drag a **Push Button** (or **Button**) onto the canvas.
2. Wire **one terminal** of the button to **PD2** on the ATmega32 (DIP-40 pin 16).
3. Wire the **other terminal** to **GND**.
4. Label the button component `SW_EMERGENCY` using the component properties.

When you click this button in the simulation, PD2 is pulled from 5 V to GND — a falling edge that fires INT0.

---

## Step 4 — Event Pulse Button (INT1 on PD3)

This button counts events during normal mode.

1. Drag a second **Push Button** onto the canvas.
2. Wire **one terminal** to **PD3** (DIP-40 pin 17).
3. Wire the **other terminal** to **GND**.
4. Label it `SW_EVENT`.

---

## Step 5 — Recovery / Reset Button (INT2 on PB2)

This button recovers from emergency mode, or resets the count during normal mode.

1. Drag a third **Push Button** onto the canvas.
2. Wire **one terminal** to **PB2** (DIP-40 pin 3).
3. Wire the **other terminal** to **GND**.
4. Label it `SW_RECOVERY`.

---

## Step 6 — Green LED — Normal Mode Indicator (PB0)

1. From the panel, drag a **Resistor** component, set its value to **330 Ω**.
2. Drag an **LED** component; set colour to green if the option exists.
3. Wire:
   - **PB0** (DIP-40 pin 1) → **one end of the 330 Ω resistor**
   - **Other end of the resistor** → **LED anode** (positive / longer leg)
   - **LED cathode** (negative / shorter leg / flat side) → **GND**
4. Label: `LED_NORMAL`.

The green LED will be ON whenever the system is in normal mode.

---

## Step 7 — Red LED — Emergency Stop Indicator (PB1)

1. Drag another **Resistor**, set to **330 Ω**.
2. Drag another **LED**; set colour to red.
3. Wire:
   - **PB1** (DIP-40 pin 2) → **resistor** → **LED anode** → **LED cathode** → **GND**
4. Label: `LED_STOP`.

The red LED will be ON whenever the system is in emergency mode.

---

## Step 8 — Buzzer (PB3)

1. From the panel, drag a **Buzzer** component (or a **Piezo** if Buzzer is not available in your version).
2. Wire:
   - **PB3** (DIP-40 pin 4) → **buzzer positive terminal**
   - **Buzzer negative terminal** → **GND**
3. Label: `BUZZER`.

The buzzer activates at the same time as the red LED during emergency mode.

---

## Step 9 — UART Serial Terminal (PD1 / TXD)

The firmware sends status messages at 9600 baud on PD1.

**Option A — Built-in serial monitor (simplest):**

1. Right-click the ATmega32 → **Open Serial Monitor**.
2. In the serial monitor window, set baud rate to **9600**.
3. The monitor connects automatically to the UART peripheral inside the chip — no extra wire needed.

**Option B — SerialTerm component (visible on canvas):**

1. From the panel, drag a **SerialTerm** onto the canvas.
2. Wire:
   - **SerialTerm RX** → **PD1 / TXD** (DIP-40 pin 15)
   - **SerialTerm GND** → **GND node**
3. Double-click the SerialTerm → set baud to **9600**, format **8N1**.

---

## Step 10 — Run the Simulation

1. Press the **Play** button (▶) at the top of the SimulIDE window.
2. The green LED should turn ON within a moment (normal mode startup).
3. The serial monitor should show:

   ```text
   ATmega32 External Interrupt Event Counter System
   Mode: NORMAL | Count: 0
   ```

4. Proceed with the test procedure in the next section.

---

## Test Procedure

Follow this order. Wait at least **1 second** between button clicks to clear the 200 ms software debounce window.

| Step | Button to click | What should happen |
| --- | --- | --- |
| 1 | — (just started) | Green LED ON, red OFF, buzzer OFF, serial: `Mode: NORMAL \| Count: 0` |
| 2 | SW_EVENT (once) | Serial: `Mode: NORMAL \| Count: 1`, green LED still ON |
| 3 | SW_EVENT (3 more times) | Count increases to 4, one new serial line per click |
| 4 | SW_EMERGENCY | Red LED ON, buzzer ON, green LED OFF. Serial: `Mode: EMERGENCY STOP \| Count: 4` |
| 5 | SW_EVENT (during emergency) | Count must NOT increase. No new serial line. Red LED and buzzer stay ON. |
| 6 | SW_RECOVERY (during emergency) | Green LED ON, red OFF, buzzer OFF. Serial: `Mode: NORMAL \| Count: 4` |
| 7 | SW_RECOVERY (in normal mode) | Count resets. Serial: `Mode: NORMAL \| Count: 0` |

**After each step:** take a screenshot and save it to `simulide/screenshots/` with the filename listed in `simulide/screenshots/README.md`.

---

## Saving the Circuit File

After wiring everything and confirming the simulation runs correctly, save the circuit:

**File → Save** → save into this folder as:

```text
simulide/circuit/emergency_event_counter.sim1
```

Commit this `.sim1` file to the repository so the circuit can be reopened without rewiring.

---

## Quick Connection Checklist

Use this before pressing Run to catch missing wires:

- [ ] VCC (pin 10) → 5 V
- [ ] AVCC (pin 30) → 5 V
- [ ] GND (pin 11) → GND
- [ ] GND (pin 31) → GND
- [ ] PD2 (pin 16) → SW_EMERGENCY → GND
- [ ] PD3 (pin 17) → SW_EVENT → GND
- [ ] PB2 (pin 3) → SW_RECOVERY → GND
- [ ] PB0 (pin 1) → 330 Ω → Green LED anode → cathode → GND
- [ ] PB1 (pin 2) → 330 Ω → Red LED anode → cathode → GND
- [ ] PB3 (pin 4) → Buzzer (+) → Buzzer (−) → GND
- [ ] PD1 (pin 15) → SerialTerm RX (or use built-in serial monitor)
- [ ] Firmware loaded: `firmware/hex/emergency_event_counter.hex`
- [ ] Frequency set to 8000000 Hz

---

## Important SimulIDE Reset Fix

If the firmware does not run, check the RESET pin first. In SimulIDE the ATmega32 RESET pin must be held HIGH during normal operation.

Working method:

```text
+5V source → RESET pin
GND of the source → circuit GND
```

A reset button can still pull RESET to GND when pressed, but during normal running RESET must not float.
