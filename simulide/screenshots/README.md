# SimulIDE Screenshots

## Status

> All screenshots listed below are **pending** — no simulation has been run yet.
> After running SimulIDE and completing each test step, save the screenshot here with the exact filename shown.
> Do not rename or abbreviate the filenames — they are referenced in the test results and README.

---

## Required Screenshots

Save all screenshots in this folder: `simulide/screenshots/`

### 01_normal_startup.png

**When to capture:** Immediately after pressing Run, before clicking any button.

**What must be visible:**

- Green LED is ON (lit)
- Red LED is OFF
- Buzzer is OFF (not activated)
- Serial monitor shows the startup banner and first status line

Expected serial output:

```text
ATmega32 External Interrupt Event Counter System
Mode: NORMAL | Count: 0
```

---

### 02_single_event_count.png

**When to capture:** After clicking SW_EVENT exactly once.

**What must be visible:**

- Green LED still ON
- Red LED OFF, buzzer OFF
- Serial monitor shows the updated count

Expected serial output:

```text
Mode: NORMAL | Count: 1
```

---

### 03_multiple_event_count.png

**When to capture:** After clicking SW_EVENT several more times (count should be 3 or higher).

**What must be visible:**

- Green LED still ON
- Serial monitor scrollback shows multiple count lines incrementing

Expected serial output:

```text
Mode: NORMAL | Count: 2
Mode: NORMAL | Count: 3
Mode: NORMAL | Count: 4
```

---

### 04_emergency_stop.png

**When to capture:** Immediately after clicking SW_EMERGENCY.

**What must be visible:**

- Red LED is ON (lit)
- Buzzer is activated
- Green LED is OFF
- Serial monitor shows the emergency stop line

Expected serial output:

```text
Mode: EMERGENCY STOP | Count: 4
```

(or whatever count was reached before the emergency)

---

### 05_counting_lockout.png

**When to capture:** After clicking SW_EVENT one or more times while still in emergency mode.

**What must be visible:**

- Red LED still ON, buzzer still ON, green LED still OFF
- Serial monitor shows **no new count line** after the emergency stop line
- Count has NOT increased — this proves the lockout works

> Tip: position the serial monitor so the last line is clearly the `EMERGENCY STOP` line with no additional line below it.

---

### 06_recovery_mode.png

**When to capture:** After clicking SW_RECOVERY while in emergency mode.

**What must be visible:**

- Green LED is ON again
- Red LED is OFF
- Buzzer is OFF
- Serial monitor shows the recovery line with count preserved

Expected serial output:

```text
Mode: NORMAL | Count: 4
```

(count is preserved from before the emergency — it did not reset)

---

## How to Take Screenshots on Windows

1. Press **Win + Shift + S** to open the snipping tool.
2. Drag a rectangle around the SimulIDE window, including both the circuit canvas and the serial monitor.
3. The image is copied to clipboard — paste it into Paint (or any image editor) and save it as `.png`.
4. Rename it to the exact filename listed above and move it into this folder.

**Alternative:** Press **PrtSc** to capture the full screen, paste into Paint, crop, and save.

---

## Screenshot Quality Checklist

Before submitting, confirm each screenshot:

- [ ] Filename matches exactly (lowercase, underscores, `.png`)
- [ ] Serial monitor output is readable (not cut off)
- [ ] LED state is visible (colour or glow indicates ON/OFF)
- [ ] Buzzer component state is visible where relevant
- [ ] No personal information visible in the background
