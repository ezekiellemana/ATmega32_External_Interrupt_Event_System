# ATmega32 External Interrupt Event Counter System

## CT 321 PBL 07 — External Interrupt-Based Emergency Stop and Event Counter System

## Description

This system demonstrates the use of three hardware external interrupts on the ATmega32 to implement a real-time emergency stop and event counting mechanism. A green LED indicates normal operation. An emergency stop button immediately activates a red LED and buzzer via INT0, and locks out event counting until recovery is triggered. A recovery/reset button (INT2) restores the system or resets the event counter. All button inputs use active-LOW logic with internal pull-up resistors and are debounced in firmware using a Timer0 1 ms tick and a 200 ms window.

---

## Hardware List

| Component | Quantity | Notes |
| --- | --- | --- |
| ATmega32 / ATmega32A microcontroller | 1 | 8 MHz crystal or resonator |
| Crystal oscillator, 8 MHz | 1 | With 22 pF load capacitors |
| Push button, normally open | 3 | Active LOW to GND |
| Green LED | 1 | For normal mode (PB0) |
| Red LED | 1 | For emergency stop (PB1) |
| Buzzer (5 V active) | 1 | Connected to PB3 |
| Resistor, 330 Ω | 2 | LED current limiting |
| Resistor, 10 kΩ | 1 | RESET pull-up |
| Decoupling capacitor, 100 nF | 2 | VCC and AVCC bypass |
| USB-to-TTL serial adapter | 1 | For UART monitoring at 9600 baud |
| Breadboard or PCB | 1 | Prototype or KiCad PCB |

---

## Pin Mapping Table

| ATmega32 Pin | Direction | Function | Connected Device |
| --- | --- | --- | --- |
| PD2 / INT0 | Input (pull-up) | Emergency stop interrupt | Push button → GND |
| PD3 / INT1 | Input (pull-up) | Event pulse interrupt | Push button / sensor → GND |
| PB2 / INT2 | Input (pull-up) | Recovery / reset interrupt | Push button → GND |
| PB0 | Output | Normal mode indicator | Green LED + 330 Ω → GND |
| PB1 | Output | Emergency stop indicator | Red LED + 330 Ω → GND |
| PB3 | Output | Buzzer driver | Active buzzer to GND |
| PD1 / TXD | Output | UART serial transmit | USB-TTL RX pin |
| RESET | Input | Hardware reset | 10 kΩ to VCC, button to GND |
| VCC / AVCC | Power | 3.3–5 V supply | Regulated supply |
| GND | Power | Ground | Common ground |

---

## Build Instructions

### Option A — MPLAB X IDE for VS Code (recommended)

1. Install MPLAB X IDE and the XC8 compiler (v3.10 or later).
2. Install the ATmega DFP device pack: **Tools → Packs → ATmega_DFP**.
3. Create a new standalone project: device = **ATmega32** or **ATmega32A**, compiler = **XC8**.
4. Add `firmware/src/main.c` as the project source file.
5. Build the project (**Ctrl+F11** or **Project → Build**).
6. Copy the generated `.hex` from the MPLAB build output to `firmware/hex/emergency_event_counter.hex`.

### Option B — Command line with avr-gcc (ATmega DFP required)

```bash
# Set these paths to match your installation
AVR_GCC="C:/Program Files/Microchip/xc8/v3.10/avr/bin/avr-gcc.exe"
AVR_OBJCOPY="C:/Program Files/Microchip/xc8/v3.10/bin/avr-objcopy.exe"
DFP_INCLUDE="C:/Users/<user>/.mchp_packs/Microchip/ATmega_DFP/3.6.299/include"
DFP_LIB="C:/Users/<user>/.mchp_packs/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega32/avr5"

"$AVR_GCC" -mmcu=atmega32 -DF_CPU=8000000UL -O1 -Wall -std=c99 \
  -isystem "$DFP_INCLUDE" -B "$DFP_LIB" \
  -o firmware/hex/main.elf firmware/src/main.c

"$AVR_OBJCOPY" -O ihex -R .eeprom \
  firmware/hex/main.elf firmware/hex/emergency_event_counter.hex
```

**Build result (verified):** Program = 1307 bytes (4.0% of 32 KB), Data = 114 bytes (5.6% of 2 KB).

---

## SimulIDE Loading Instructions

1. Open **SimulIDE**.
2. From the component panel, drag an **ATmega32** onto the canvas.
3. Right-click the ATmega32 → **Load firmware** → select `firmware/hex/emergency_event_counter.hex`.
4. Set the CPU frequency to **8000000** Hz in the component properties.
5. Connect components as described in `simulide/circuit/README.md`.
6. Press **Run** to start the simulation.
7. Open the serial monitor (right-click ATmega32 → **Open Serial Monitor**) set to **9600 baud**.

---

## Test Procedure

| Step | Action | Expected UART output | Expected LEDs / Buzzer |
| --- | --- | --- | --- |
| 1 | Power on / start simulation | `Mode: NORMAL \| Count: 0` | Green ON, Red OFF, Buzzer OFF |
| 2 | Press event button once | `Mode: NORMAL \| Count: 1` | Green ON |
| 3 | Press event button several more times | Count increases with each press | Green ON |
| 4 | Press emergency stop button | `Mode: EMERGENCY STOP \| Count: N` | Green OFF, Red ON, Buzzer ON |
| 5 | Press event button during emergency | No change to count | Red ON, Buzzer ON (no count change) |
| 6 | Press recovery button | `Mode: NORMAL \| Count: N` | Green ON, Red OFF, Buzzer OFF |
| 7 | Press recovery/reset in normal mode | `Mode: NORMAL \| Count: 0` | Green ON, count resets |

---

## Repository Folder Structure

```text
ATmega32_External_Interrupt_Event_System/
├── .gitignore                          ← Excludes *.elf, *.o, build/, etc.
├── README.md                           ← This file
├── firmware/
│   ├── src/
│   │   └── main.c                      ← Complete ATmega32 C firmware source
│   ├── include/                        ← Reserved for future header files
│   └── hex/
│       ├── emergency_event_counter.hex ← Compiled HEX — required for SimulIDE
│       └── README_generate_hex.md      ← Build instructions and size report
├── documentation/
│   ├── block_diagram.png               ← System block diagram
│   ├── firmware_flowchart.png          ← Firmware flowchart
│   ├── pcb_layout_plan.png             ← PCB layout planning diagram
│   ├── schematic_connection_plan.png   ← Schematic connection plan
│   ├── interrupt_configuration.md      ← Interrupt setup and debounce details
│   ├── pin_mapping_table.md            ← Full pin assignment table
│   └── test_results.md                ← Test cases (pending SimulIDE capture)
├── simulide/
│   ├── circuit/
│   │   ├── README.md                   ← Step-by-step SimulIDE wiring guide
│   │   └── (emergency_event_counter.sim1 — add after wiring)
│   └── screenshots/
│       ├── README.md                   ← Required screenshot names and guide
│       └── (01_–06_*.png — add after simulation run)
├── kicad/
│   ├── README.md                       ← KiCad schematic, PCB, Gerber checklist
│   ├── schematic/                      ← Add .kicad_sch after drawing
│   ├── pcb/                            ← Add .kicad_pcb after routing
│   └── gerber/                         ← Add Gerber + drill files after export
└── media/
    └── demonstration_video_link.txt    ← Paste demo video link after recording
```

---

## Repository Submission Status

**GitHub repository:** [ezekiellemana/ATmega32_External_Interrupt_Event_System](https://github.com/ezekiellemana/ATmega32_External_Interrupt_Event_System)

| Deliverable | File / Location | Status |
| --- | --- | --- |
| Firmware source code | `firmware/src/main.c` | **Complete** |
| Compiled HEX file | `firmware/hex/emergency_event_counter.hex` | **Complete** — 1307 bytes, 4.0% of 32 KB flash |
| GitHub repository | [ezekiellemana/ATmega32_External_Interrupt_Event_System](https://github.com/ezekiellemana/ATmega32_External_Interrupt_Event_System) | **Published** |
| SimulIDE circuit file | `simulide/circuit/emergency_event_counter.sim1` | Pending — wire and save manually in SimulIDE |
| SimulIDE screenshots (×6) | `simulide/screenshots/01_–06_*.png` | Pending — capture manually after simulation |
| KiCad schematic | `kicad/schematic/*.kicad_sch` | Pending — draw manually in KiCad |
| KiCad PCB layout | `kicad/pcb/*.kicad_pcb` | Pending — route manually in KiCad |
| Gerber + drill files | `kicad/gerber/` | Pending — export from KiCad after PCB is complete |
| Demonstration video link | `media/demonstration_video_link.txt` | Pending — paste link after recording |

---

## Uploading to GitHub

### Option A — GitHub Desktop (recommended if GitHub CLI is not installed)

1. Open **GitHub Desktop**.
2. **File → Add Local Repository** → select this project folder.
3. GitHub Desktop will detect the local git repository.
4. Click **Publish repository**.
5. Set the name to: `ATmega32_External_Interrupt_Event_System`
6. Set visibility to **Public** (or Private if your instructor requires it).
7. Click **Publish Repository**.
8. After publishing, copy the repository URL and update this README if needed.

### Option B — Command line (if GitHub CLI is installed)

```bash
gh repo create ATmega32_External_Interrupt_Event_System \
  --public --source=. --remote=origin --push
```

### Option C — GitHub web + git push

1. Go to github.com → **New repository**.
2. Name: `ATmega32_External_Interrupt_Event_System`, Public, no README (we have one).
3. Copy the remote URL.
4. In a terminal inside this folder:

```bash
git remote add origin https://github.com/<your-username>/ATmega32_External_Interrupt_Event_System.git
git branch -M main
git push -u origin main
```

---

## Authors

CT 321 Group 07 — BSc Computer Engineering, Semester 2
