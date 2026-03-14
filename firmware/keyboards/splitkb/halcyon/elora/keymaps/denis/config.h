// Elora Rev2 — Denis's custom config
#pragma once

// --- Mod-tap tuning ---

#define TAPPING_TERM 175
#define QUICK_TAP_TERM 120

// Bilateral combinations: mod-tap is always a tap
// when both keys are on the same hand.
#define CHORDAL_HOLD
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
#define POINTING_DEVICE_RIGHT            // trackpad is on the right half
#define AUTO_MOUSE_DEFAULT_LAYER 4       // _MOUSE layer
#define AUTO_MOUSE_TIME 650              // ms before returning to previous layer

// --- Leader key ---
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING  // restart timeout after each key press
#define LEADER_NO_TIMEOUT 0

// --- Per-key tapping term ---
#define TAPPING_TERM_PER_KEY

// --- Split transport sync ---
#define SPLIT_LAYER_STATE_ENABLE                   // sync layer state to slave (for right-half RGB)
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_RGB   // custom RPC to sync rgb_user_enabled
