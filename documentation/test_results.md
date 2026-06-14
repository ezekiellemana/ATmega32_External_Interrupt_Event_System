# Test Results

> **Status: Pending.**
> All test cases below state the **expected** behaviour derived from the firmware source code.
> The **Observed output** column for every case is marked "To be captured in SimulIDE" because no simulation has been run yet.
> After completing the SimulIDE session, replace each placeholder with the actual serial output and the filename of the screenshot you saved to `simulide/screenshots/`.
> Do NOT mark any test PASS until the real screenshot exists.

---

## Test Case 1 — Normal Startup

**Action:** Start the simulation in SimulIDE (press the Play button). Do not click any button yet.

**Expected UART output:**

```text
ATmega32 External Interrupt Event Counter System
Mode: NORMAL | Count: 0
```

**Expected hardware state:**

- Green LED (PB0): ON
- Red LED (PB1): OFF
- Buzzer (PB3): OFF
- event_count = 0

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/01_normal_startup.png` — to be captured

---

## Test Case 2 — Single Event Pulse

**Action:** Click SW_EVENT once (PD3 falling edge). Wait at least 1 second before the next action.

**Expected UART output:**

```text
Mode: NORMAL | Count: 1
```

**Expected hardware state:** Green LED ON, red LED OFF, buzzer OFF. Count increases from 0 to 1.

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/02_single_event_count.png` — to be captured

---

## Test Case 3 — Multiple Event Pulses

**Action:** Click SW_EVENT three or more additional times, waiting at least 1 second between each click.

**Expected UART output:** One new line per accepted click:

```text
Mode: NORMAL | Count: 2
Mode: NORMAL | Count: 3
Mode: NORMAL | Count: 4
```

**Expected hardware state:** Green LED ON throughout. Count increments correctly with each press.

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/03_multiple_event_count.png` — to be captured

---

## Test Case 4 — Emergency Stop

**Action:** Click SW_EMERGENCY (PD2 falling edge).

**Expected UART output:**

```text
Mode: EMERGENCY STOP | Count: 4
```

**Expected hardware state:**

- Green LED (PB0): OFF
- Red LED (PB1): ON
- Buzzer (PB3): ON
- event_count does not change

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/04_emergency_stop.png` — to be captured

---

## Test Case 5 — Event Pulse During Emergency Mode (Counting Lockout)

**Action:** While still in emergency mode, click SW_EVENT one or more times.

**Expected UART output:** No new line is printed. The count remains at 4.

**Expected hardware state:** Red LED ON, buzzer ON, green LED OFF — unchanged. The count does not increase.

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/05_counting_lockout.png` — to be captured

---

## Test Case 6 — Recovery from Emergency Mode

**Action:** Click SW_RECOVERY (PB2 falling edge) while still in emergency mode.

**Expected UART output:**

```text
Mode: NORMAL | Count: 4
```

**Expected hardware state:**

- Green LED (PB0): ON
- Red LED (PB1): OFF
- Buzzer (PB3): OFF
- event_count preserved from before the emergency (still 4)

**Observed output:** To be captured in SimulIDE

**Screenshot:** `simulide/screenshots/06_recovery_mode.png` — to be captured

---

## Test Case 7 — Count Reset in Normal Mode

**Action:** Click SW_RECOVERY again, now while already in normal mode.

**Expected UART output:**

```text
Mode: NORMAL | Count: 0
```

**Expected hardware state:** Green LED ON, red LED OFF, buzzer OFF. event_count reset to 0.

**Observed output:** To be captured in SimulIDE

**Screenshot:** Extend `06_recovery_mode.png` or capture separately — to be captured

---

## Summary Table

| # | Test Case | Expected Result | Screenshot | Status |
| --- | --- | --- | --- | --- |
| 1 | Normal startup | Green LED ON, count = 0 | 01_normal_startup.png | Pending |
| 2 | Single event pulse | Count = 1 | 02_single_event_count.png | Pending |
| 3 | Multiple event pulses | Count increments correctly | 03_multiple_event_count.png | Pending |
| 4 | Emergency stop | Red ON, buzzer ON, counting locked | 04_emergency_stop.png | Pending |
| 5 | Counting lockout | Count unchanged during emergency | 05_counting_lockout.png | Pending |
| 6 | Recovery from emergency | Normal mode restored, count preserved | 06_recovery_mode.png | Pending |
| 7 | Reset in normal mode | Count resets to 0 | (same session as TC6) | Pending |
