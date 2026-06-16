# HEX File

## Status

The final compiled HEX file is present in this folder:

```text
firmware/hex/emergency_event_counter.hex
```

Use this HEX file in SimulIDE:

```text
ATmega32 → Load Firmware → emergency_event_counter.hex
```

Verified build summary:

```text
Device:  ATmega32 / ATmega32A
Clock:   8 MHz
Flash:   approximately 1403 bytes, about 4.3% of 32 KB
SRAM:    approximately 80 bytes, about 3.9% of 2 KB
Warnings: 0
Errors:   0
```

Only the final `.hex` file is kept in this cleaned submission folder. Intermediate `.elf` files and diagnostic firmware have been removed because they are not required for final submission.

---

## Regenerating the HEX File

If `firmware/src/main.c` is modified, rebuild using MPLAB for VS Code or AVR-GCC, then replace:

```text
firmware/hex/emergency_event_counter.hex
```

with the new generated HEX file.

### Example AVR-GCC Build Command

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

After confirming the HEX works, delete the intermediate `main.elf` file.
