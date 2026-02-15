# Lock Mode Design

## Summary

Keyboard lock mode that auto-engages after 5 minutes of inactivity. Lock/unlock via holding all 4 corner keys simultaneously for 6 seconds, with a green progress bar on the number row. Denied keypresses while locked flash the pressed key red.

## Approach

State machine in `process_record_user` + `matrix_scan_user` (Approach 1). No extra layers consumed. All visuals handled in `rgb_matrix_indicators_advanced_user`.

## State Variables

- `static bool keyboard_locked` — master lock flag
- `static uint32_t lock_combo_start` — timestamp when all 4 corners were first held together (0 = not active)
- `static uint8_t denied_key_led` — LED index of last denied keypress (NO_LED = none)
- `static uint32_t denied_flash_start` — timestamp of denied keypress flash

## Idle Auto-Lock (5 minutes)

In `matrix_scan_user()`: check `last_input_activity_elapsed() > 300000`. If true and not locked, set `keyboard_locked = true`, force layer state to base, clear one-shot mods.

## 4-Corner Combo

Unlock/lock keys: `` ` `` (top-left), `=` (top-right), `Z` (bottom-left), `/` (bottom-right).

Detection in `matrix_scan_user()` using `matrix_is_on(row, col)` to check physical key state. Row/col positions must be verified from the Elora Rev2 matrix definition.

- All 4 held: start `lock_combo_start` timer
- Held for 6000ms: toggle `keyboard_locked`, reset timer, clear one-shot mods and force base layer on lock
- Any corner released before 6s: reset `lock_combo_start = 0`

Same combo works for both locking (when unlocked) and unlocking (when locked).

## Key Blocking

In `process_record_user()`: if `keyboard_locked`, record the denied key's LED index + flash timestamp, return `false`. The 4 corner keys are also blocked at the keycode level — the combo is detected via physical matrix state, not keycodes.

## RGB Indicators

All handled in `rgb_matrix_indicators_advanced_user()`:

### Locked idle state
All LEDs off. Keyboard looks dead.

### Denied keypress flash
The pressed key's LED blinks red for ~300ms, then off. Only the specific key, not all LEDs.

### Progress bar (lock or unlock)
Number row keys 1 through 0 light up green left-to-right. 10 keys over 6 seconds = one new key every 600ms. Already-lit keys stay solid green. Underglow pulses dim green during the sequence.

## Edge Cases

- Active layers forced to base on lock
- One-shot mods cleared on lock
- Denied keypresses while locked do NOT reset the idle timer (already locked)
- Progress bar shows during both lock and unlock sequences identically
