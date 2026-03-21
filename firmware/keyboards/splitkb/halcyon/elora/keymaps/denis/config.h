// Elora Rev2 — Denis's custom config
#pragma once

// --- Mod-tap tuning ---

#define TAPPING_TERM 175
#define QUICK_TAP_TERM 120

// Bilateral combinations: mod-tap is always a tap
// when both keys are on the same hand.
#define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// --- Leader key ---
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING  // restart timeout after each key press
#define LEADER_NO_TIMEOUT 0

// --- Per-key tapping term ---
#define TAPPING_TERM_PER_KEY

// --- Split transport sync ---
#define SPLIT_LAYER_STATE_ENABLE                   // sync layer state to slave (for right-half RGB)
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_RGB   // custom RPC to sync rgb_user_enabled
