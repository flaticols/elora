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

// --- Mouse keys tuning (software emulation, kept as fallback) ---
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

// --- Cirque trackpad tuning (right half module) ---
// The Halcyon cirque module (HLC_CIRQUE_TRACKPAD) handles driver init,
// POINTING_DEVICE_ENABLE, pin config, tap detection, and absolute mode.
// Only override values you explicitly want to change from module defaults.
#define AUTO_MOUSE_DEFAULT_LAYER 4       // _MOUSE layer
#define AUTO_MOUSE_TIME 650              // ms before returning to previous layer

// --- Leader key ---
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING  // restart timeout after each key press
#define LEADER_NO_TIMEOUT 0

// --- Per-key tapping term ---
#define TAPPING_TERM_PER_KEY
