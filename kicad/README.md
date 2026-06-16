# KiCad Schematic, PCB Layout, and Gerber Files

## Status

The KiCad part of this project is complete.

```text
ERC: Passed with zero errors
DRC: Passed with zero violations and zero unconnected items
Gerber files: Exported
Drill files: Exported
```

---

## KiCad Source Files

Open this project in KiCad:

```text
kicad/ATmega32_External_Interrupt_Event_System/ATmega32_External_Interrupt_Event_System.kicad_pro
```

Main design files:

```text
kicad/ATmega32_External_Interrupt_Event_System/ATmega32_External_Interrupt_Event_System.kicad_sch
kicad/ATmega32_External_Interrupt_Event_System/ATmega32_External_Interrupt_Event_System.kicad_pcb
```

---

## Schematic Evidence

The schematic export is saved here:

```text
kicad/schematic/kicad_schematic.png
kicad/schematic/kicad_schematic.pdf
```

The schematic includes:

- ATmega32A-P microcontroller
- INT0 emergency stop button
- INT1 event pulse button
- INT2 recovery/reset button
- MCU reset button
- Green and red LEDs
- Buzzer driver using NPN transistor
- 8 MHz crystal with two 22 pF capacitors
- VCC, AVCC, GND, reset circuit, and decoupling capacitors
- External 10 kΩ pull-up resistors for the three interrupt inputs
- Serial header for UART TX

---

## PCB Evidence

The PCB screenshot and DRC evidence are saved here:

```text
kicad/pcb/kicad_pcb.png
kicad/pcb/drc_zero_errors.png
```

The PCB uses:

- F.Cu copper zone for +5V
- B.Cu copper zone for GND
- Through-hole components
- Clear silkscreen labels for buttons, LEDs, buzzer, and header
- Fully routed nets with no unconnected items

---

## Gerber Files

Gerber and drill files are saved here:

```text
kicad/gerber/
```

Required fabrication outputs included:

```text
ATmega32_External_Interrupt_Event_System-F_Cu.gbr
ATmega32_External_Interrupt_Event_System-B_Cu.gbr
ATmega32_External_Interrupt_Event_System-F_Silkscreen.gbr
ATmega32_External_Interrupt_Event_System-B_Silkscreen.gbr
ATmega32_External_Interrupt_Event_System-F_Mask.gbr
ATmega32_External_Interrupt_Event_System-B_Mask.gbr
ATmega32_External_Interrupt_Event_System-Edge_Cuts.gbr
ATmega32_External_Interrupt_Event_System-PTH.drl
ATmega32_External_Interrupt_Event_System-NPTH.drl
ATmega32_External_Interrupt_Event_System-job.gbrjob
ATmega32_Gerber_Files.zip
```

---

## Final KiCad Checklist

- [x] ATmega32 schematic created
- [x] External interrupt buttons connected
- [x] Output LEDs and buzzer connected
- [x] Reset, crystal, power, and decoupling included
- [x] Footprints assigned
- [x] PCB routed
- [x] GND and +5V zones added
- [x] DRC passed with zero errors
- [x] Gerber files exported
- [x] Drill files exported
