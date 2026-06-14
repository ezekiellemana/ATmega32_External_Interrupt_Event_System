# HEX File

## Status

`emergency_event_counter.hex` has been generated and is present in this folder.

**Build verified on 2026-06-14:**

```text
Device:  ATmega32
Program: 1307 bytes (4.0% of 32 KB flash)
Data:    114 bytes (5.6% of 2 KB SRAM)
```

Load this file into SimulIDE or flash it to hardware using AVRDude or MPLAB IPE.

---

## Regenerating the HEX File

If you modify `firmware/src/main.c`, rebuild using one of these methods.

### Option A — MPLAB X IDE

Build the project (**Ctrl+F11**) and copy the new `.hex` from the MPLAB build output folder to this directory, renaming it `emergency_event_counter.hex`.

### Option B — Command line (Git Bash / PowerShell)

```bash
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

Replace `<user>` with your Windows username. The `main.elf` intermediate file can be deleted after the `.hex` is confirmed correct.
