# KiCad Schematic and PCB

## Status

> The KiCad schematic and PCB have **not been created yet**.
> This file is a step-by-step checklist. Work through it in order: schematic first, then PCB, then Gerber export.

---

## Part 1 — Create the Schematic (`kicad/schematic/`)

### 1.1 — Start a New KiCad Project

1. Open **KiCad** (version 7 or 8 recommended).
2. **File → New Project** → browse to `kicad/` and name the project `emergency_event_counter`.
3. KiCad will create `emergency_event_counter.kicad_pro` and `emergency_event_counter.kicad_sch` inside `kicad/`.
4. Move or keep those files — place the `.kicad_sch` in `kicad/schematic/` and the `.kicad_pcb` in `kicad/pcb/`.

### 1.2 — Place and Configure the ATmega32

1. Open the **Schematic Editor** (KiCad main window → Schematic Editor).
2. Press **A** to add a symbol. Search for `ATmega32` or `ATmega32-16PU`.
3. Place it near the centre of the sheet.
4. Assign reference `U1`.

### 1.3 — Components to Place

| Reference | Symbol to search | Value | Notes |
| --- | --- | --- | --- |
| U1 | ATmega32-16PU | ATmega32 | Main microcontroller |
| SW1 | SW_Push | EMERGENCY | Emergency stop button (INT0 / PD2) |
| SW2 | SW_Push | EVENT | Event pulse button (INT1 / PD3) |
| SW3 | SW_Push | RECOVERY | Recovery / reset button (INT2 / PB2) |
| SW4 | SW_Push | RESET_BTN | Hardware reset button |
| LED1 | LED | GREEN | Normal mode indicator — PB0 |
| LED2 | LED | RED | Emergency stop indicator — PB1 |
| BZ1 | Buzzer | 5V | Emergency alarm — PB3 |
| R1 | R | 330R | Current limit for LED1 |
| R2 | R | 330R | Current limit for LED2 |
| R3 | R | 10k | RESET pin pull-up to VCC |
| C1 | C | 100n | VCC decoupling capacitor |
| C2 | C | 100n | AVCC decoupling capacitor |
| Y1 | Crystal | 8MHz | Clock source — XTAL1/XTAL2 |
| C3 | C | 22p | Crystal load cap — XTAL1 side |
| C4 | C | 22p | Crystal load cap — XTAL2 side |
| J1 | Conn_01x03 | SERIAL | UART header: pin 1 = GND, pin 2 = TX, pin 3 = VCC |
| J2 | Conn_01x02 | POWER_IN | Power input: pin 1 = +5V, pin 2 = GND |

### 1.4 — Required Net Labels

Add **net labels** (press **L** in the schematic editor) to the following wires. Use exactly these names so the PCB layout matches:

| Net label | Where to place it |
| --- | --- |
| `EMERGENCY_INT0` | Wire from U1 PD2 to SW1 |
| `EVENT_INT1` | Wire from U1 PD3 to SW2 |
| `RECOVERY_INT2` | Wire from U1 PB2 to SW3 |
| `LED_NORMAL` | Wire from U1 PB0 through R1 to LED1 anode |
| `LED_STOP` | Wire from U1 PB1 through R2 to LED2 anode |
| `BUZZER` | Wire from U1 PB3 to BZ1 positive |
| `SERIAL_TX` | Wire from U1 PD1/TXD to J1 pin 2 |
| `+5V` | Power rail (use Power symbol PWR_FLAG) |
| `GND` | Ground rail (use Power symbol GND) |
| `RESET` | Wire from U1 RESET pin through R3 to +5V, with SW4 to GND |

### 1.5 — Wiring Notes

- **Buttons SW1, SW2, SW3** — each has one pin wired to the MCU pin and the other pin wired to GND. **No external pull-up resistors.** The firmware enables internal pull-ups.
- **AVCC** — connect to +5V through C2 (100 nF) to GND. Do not leave AVCC floating.
- **Crystal** — Y1 between XTAL1 and XTAL2 pins, with C3 from XTAL1 to GND and C4 from XTAL2 to GND.
- **RESET** — R3 (10 kΩ) from RESET to +5V; SW4 from RESET to GND; optional 100 nF from RESET to GND.
- **LED polarity** — anode (+) connects toward the MCU through a resistor; cathode (−) connects to GND.
- **Power flags** — add a `PWR_FLAG` symbol to both the +5V and GND nets to silence ERC warnings about undriven power pins.

### 1.6 — Schematic Checklist (run before moving to PCB)

- [ ] All ATmega32 pins match `documentation/pin_mapping_table.md`
- [ ] U1 VCC (pin 10) and AVCC (pin 30) are both connected to +5V
- [ ] U1 GND pins (11 and 31) are both connected to GND
- [ ] C1 and C2 decoupling capacitors placed on VCC and AVCC respectively
- [ ] Crystal Y1 with load caps C3 and C4 on XTAL1/XTAL2
- [ ] RESET circuit: R3, SW4, optional 100 nF
- [ ] SW1, SW2, SW3 wired pin → MCU, other pin → GND (no pull-up resistors)
- [ ] LED1 and LED2 with series resistors R1 and R2
- [ ] Net labels match the list in section 1.4 exactly
- [ ] PWR_FLAG symbols added to +5V and GND nets
- [ ] **ERC (Tools → Electrical Rules Checker) passes with zero errors**

---

## Part 2 — PCB Layout (`kicad/pcb/`)

### 2.1 — Import Netlist

1. From the KiCad main window, open the **PCB Editor**.
2. **Tools → Update PCB from Schematic** (or press **F8**).
3. All footprints will appear in a cluster — spread them out before routing.

### 2.2 — Assign Footprints (if not already set in schematic)

| Reference | Recommended footprint |
| --- | --- |
| U1 | Package_DIP:DIP-40_W15.24mm |
| SW1–SW4 | Button_THT:SW_PUSH_6mm |
| LED1, LED2 | LED_THT:LED_D5.0mm |
| BZ1 | Buzzer_Beeper:Buzzer_12x9.5mm_P5mm |
| R1–R3 | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm |
| C1–C4 | Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm |
| Y1 | Crystal:Crystal_HC49-4H_Vertical |
| J1 | Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical |
| J2 | Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical |

### 2.3 — Board Size and Layer Setup

- Board outline: approximately **70 mm × 90 mm** (draw on the **Edge.Cuts** layer)
- Use at least **2 copper layers**: F.Cu (front) and B.Cu (back)
- Minimum trace width: **0.25 mm** for signals, **0.5 mm** for power and GND

### 2.4 — Placement Guidelines

- Place **U1** (ATmega32) near the centre of the board
- Place **C1** and **C2** decoupling caps immediately adjacent to U1 VCC (pin 10) and AVCC (pin 30) — keep traces shorter than 5 mm
- Group **SW1, SW2, SW3** along the top or left edge so they are easily accessible
- Place **SW4** (RESET) near the top edge
- Place **LED1** and **LED2** in a visible position — near the front edge
- Place **BZ1** away from LEDs to avoid obscuring them
- Place **J1** (serial header) and **J2** (power) on the board edge for easy connector access

### 2.5 — Routing

- Route signal traces first, then power
- Use the **interactive router** (press **X** to route)
- Pour a **GND fill zone** on B.Cu: **Place → Add Filled Zone**, set net to GND, layer B.Cu
- After placing the zone, press **B** to fill all zones

### 2.6 — Silkscreen Labels Required

Add the following text to the **F.SilkS** layer (use Add Text, press **T**):

- Near SW1: `EMERGENCY`
- Near SW2: `EVENT`
- Near SW3: `RECOVERY`
- Near SW4: `RESET`
- Near LED1: `NORMAL (GREEN)`
- Near LED2: `STOP (RED)`
- Near J1 pins: `GND`, `TX`, `VCC`
- Near J2 pins: `+5V`, `GND`
- Board title: `ATmega32 Event Counter - CT321 G07`

### 2.7 — PCB Checklist (run before Gerber export)

- [ ] All footprints placed on the board (none floating outside the outline)
- [ ] No airwires remaining (all nets fully routed)
- [ ] Decoupling caps C1 and C2 within 5 mm of U1 power pins
- [ ] GND fill zone poured on B.Cu
- [ ] Board outline closed on Edge.Cuts layer
- [ ] Silkscreen labels added for all connectors, buttons, LEDs, and board title
- [ ] **DRC (Inspect → Design Rules Checker) passes with zero errors**

---

## Part 3 — Gerber Export (`kicad/gerber/`)

### 3.1 — Plot Gerber Files

1. **File → Plot**.
2. Set **Plot format** to **Gerber**.
3. Set **Output directory** to `kicad/gerber/`.
4. Select these layers:

   | Layer | Include? |
   | --- | --- |
   | F.Cu | Yes |
   | B.Cu | Yes |
   | F.SilkS | Yes |
   | B.SilkS | Optional |
   | F.Mask | Yes |
   | B.Mask | Yes |
   | Edge.Cuts | Yes |

5. Click **Plot** to generate the `.gbr` files.

### 3.2 — Export Drill File

1. In the same Plot dialog, click **Generate Drill Files**.
2. Set format to **Excellon**, units to **mm**.
3. Click **Generate Drill File** — this creates a `.drl` file in `kicad/gerber/`.

### 3.3 — Zip for Submission

Zip all files in `kicad/gerber/` into `kicad/gerber/gerbers.zip` for submission or PCB fabrication upload.

### 3.4 — Gerber Checklist

- [ ] F.Cu Gerber file present
- [ ] B.Cu Gerber file present
- [ ] F.SilkS Gerber file present
- [ ] F.Mask and B.Mask Gerber files present
- [ ] Edge.Cuts Gerber file present
- [ ] Drill file (`.drl`) present
- [ ] `gerbers.zip` created and includes all of the above
