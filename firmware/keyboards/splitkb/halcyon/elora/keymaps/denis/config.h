// Elora Rev2 — Denis's custom config
// Fixes HRM misfires (ghost Cmd+S etc.)
#pragma once

// --- Home Row Mods tuning ---

// Slightly longer tapping term helps with
// accidental mod activation during fast typing
#define TAPPING_TERM 175

// Disable quick-tap on mod-taps so fast
// same-key double-tap doesn't trigger hold
#define QUICK_TAP_TERM 120

// Bilateral combinations: if both keys are on
// the SAME hand, the mod-tap is always a tap.
// This is the #1 fix for ghost Cmd+S —
// A(GUI) + S are both left hand = always taps.
#define CHORDAL_HOLD

// With chordal hold, use permissive hold for
// opposite-hand cases (hold A, tap J = GUI+J)
#define PERMISSIVE_HOLD

// --- Mouse keys tuning ---
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_UNMOD   8
#define MK_C_INTERVAL_UNMOD 16
#define MK_C_OFFSET_0       2
#define MK_C_INTERVAL_0     16
#define MK_C_OFFSET_1       8
#define MK_C_INTERVAL_1     16
#define MK_C_OFFSET_2       24
#define MK_C_INTERVAL_2     16

// --- Tap dance ---
#define TAPPING_TERM_PER_KEY

// --- Lock mode ---
#define LOCK_IDLE_TIMEOUT   300000  // 5 minutes in ms
#define LOCK_COMBO_HOLD_MS  6000    // 6 seconds to lock/unlock
#define LOCK_PROGRESS_STEPS 10      // number row LEDs for progress bar
#define LOCK_DENIED_FLASH_MS 300    // red flash duration on denied key
