// Elora Rev2 — Denis's custom config (matches elora.vil)
#pragma once

// --- Mod-tap tuning ---
// elora.vil uses a uniform 175ms tapping term.

#define TAPPING_TERM 175
#define QUICK_TAP_TERM 120

// Bilateral combinations: mod-tap is always a tap
// when both keys are on the same hand.
#define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// --- Split transport sync ---
#define SPLIT_LAYER_STATE_ENABLE                   // sync layer state to slave (for right-half RGB)
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_RGB   // custom RPC to sync rgb_user_enabled
