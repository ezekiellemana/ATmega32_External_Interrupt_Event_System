# SimulIDE Screenshots Required for Final Submission

Save all screenshots in this folder:

```text
simulide/screenshots/
```

Use real screenshots only. Do not use placeholder images. Each screenshot should show the SimulIDE circuit and the serial monitor/output clearly.

---

## Required Screenshots

### 01_normal_startup.png

Capture immediately after pressing Run.

Must show:

- Green LED ON
- Red LED OFF
- Buzzer OFF
- Serial output shows startup and count 0

Expected serial:

```text
ATmega32 External Interrupt Event Counter System
Mode: NORMAL | Count: 0
```

---

### 02_single_event_count.png

Capture after pressing the event button once.

Must show:

- Green LED ON
- Count = 1 in serial output

Expected serial:

```text
Mode: NORMAL | Count: 1
```

---

### 03_multiple_event_count.png

Capture after pressing the event button several times.

Must show count increasing, for example:

```text
Mode: NORMAL | Count: 2
Mode: NORMAL | Count: 3
Mode: NORMAL | Count: 4
```

---

### 04_emergency_stop.png

Capture immediately after pressing emergency stop.

Must show:

- Red LED ON
- Buzzer ON
- Green LED OFF
- Serial output shows emergency mode

Expected serial:

```text
Mode: EMERGENCY STOP | Count: 4
```

The count value can be different if your count before emergency is different.

---

### 05_counting_lockout.png

Capture after pressing event while emergency mode is still active.

Must prove:

- Red LED and buzzer remain ON
- Count does not increase
- No new count line appears after pressing event during emergency

---

### 06_recovery_mode.png

Capture after pressing recovery while still in emergency mode.

Must show:

- Green LED ON again
- Red LED OFF
- Buzzer OFF
- Count preserved from before emergency

Expected serial:

```text
Mode: NORMAL | Count: 4
```

---

### 07_reset_normal_mode.png

Capture after pressing recovery/reset again while already in normal mode.

Must show:

- Green LED ON
- Red LED OFF
- Buzzer OFF
- Count reset to 0

Expected serial:

```text
Mode: NORMAL | Count: 0
```

---

## Screenshot Quality Checklist

Before final submission, confirm:

- [ ] File names match exactly
- [ ] Serial output is readable
- [ ] LED states are visible
- [ ] Buzzer state is visible for emergency tests
- [ ] No personal/private desktop information is visible
- [ ] Screenshots are real captures from your final SimulIDE circuit
