# Final Submission Checklist

Use this checklist before submitting or presenting the CT 321 PBL 07 project.

## Completed Evidence

- [x] System block diagram: `documentation/block_diagram.png`
- [x] ATmega32 pin mapping table: `documentation/pin_mapping_table.md`
- [x] Firmware flowchart: `documentation/firmware_flowchart.png`
- [x] Interrupt configuration explanation: `documentation/interrupt_configuration.md`
- [x] Firmware source code: `firmware/src/main.c`
- [x] Compiled HEX file: `firmware/hex/emergency_event_counter.hex`
- [x] KiCad schematic source and screenshot
- [x] KiCad PCB source and screenshot
- [x] KiCad DRC result: 0 violations, 0 unconnected items, 0 errors, 0 warnings
- [x] Gerber and drill files in `kicad/gerber/`
- [x] SimulIDE circuit file: `simulide/circuit/emergency_event_counter.sim1`
- [x] SimulIDE screenshots for all required tests
- [x] Demonstration video: `media/demo_video.mp4`
- [x] Final report DOCX and PDF in `documentation/final_report/`

## Presentation Flow

1. Open README and show the folder structure.
2. Explain the problem: polling can miss important events, so external interrupts are used.
3. Show the block diagram and pin mapping table.
4. Explain INT0 for emergency, INT1 for event counting, and INT2 for recovery/reset.
5. Open the firmware source and explain the three ISR functions.
6. Show the KiCad schematic and PCB layout.
7. Show the DRC screenshot with 0 errors and Gerber folder.
8. Open SimulIDE, load `emergency_event_counter.hex`, and run the circuit.
9. Demonstrate normal mode, counting, emergency, lockout, recovery, and reset.
10. Show the seven screenshots and the final demonstration video.

## Notes

- During emergency mode, INT1 event pulses do not increase the count.
- The recovery/reset button has two actions: first press during emergency returns to normal mode; pressing again in normal mode resets the count to zero.
- The reset pin in SimulIDE must be held HIGH during normal running.
