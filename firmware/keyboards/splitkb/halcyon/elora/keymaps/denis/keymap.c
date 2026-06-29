/**
 * Elora Rev2 — Denis's keymap (faithful translation of elora.vil)
 *
 * Layers (matching elora.vil exactly):
 *   0 QWERTY   — base
 *   1 Dvorak   — alternate base (defined; bind a DF() key to reach it)
 *   2 Colemak  — alternate base (defined; bind a DF() key to reach it)
 *   3 Nav      — arrows / nav / media (LT3 on Space)
 *   4 Sym      — numbers + symbols (LT4 on Backspace)
 *   5 Function — F-keys + mods (LT5/TT5 on Tab)
 *   6 / 7      — reserved (transparent)
 *
 * Hardware features kept from the previous build:
 *   - TFT display (left half): current layer name + status indicators
 *   - Per-key RGB backlight, off by default (toggle via RM_TOGG)
 *   - Encoder map (volume / page / arrows per elora.vil)
 */

#include QMK_KEYBOARD_H
#include "transactions.h"

#ifdef HLC_TFT_DISPLAY
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#include "hlc_tft_display/hlc_tft_display.h"
#endif

// ── Layers ──

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK,
    _NAV,
    _SYM,
    _FN,
    _L6,
    _L7,
};

// ── Custom keycodes ──
// macOS Globe/Fn key + one-press window-management chords (macOS 26 tiling).
// All tiling actions are Control + Globe + <key>; the WM_* keys inject the
// whole chord themselves, so a single tap triggers the action.

enum custom_keycodes {
    AP_GLOB = SAFE_RANGE, // raw Globe (Fn) — emoji/dictation/manual chords
    WM_FILL,              // Ctrl+Globe+F  — fill desktop (native)
    WM_CNTR,              // Ctrl+Globe+C  — center (native)
    WM_RTRN,              // Ctrl+Globe+R  — return to previous size (native)
    // Halves: emulated Globe can't drive Fn+Ctrl+arrow tiling, so these send
    // Hyper+arrow — bind them to the Move & Resize menu items in
    // System Settings > Keyboard > Keyboard Shortcuts > App Shortcuts.
    WM_LEFT,              // Hyper+←  — left half
    WM_RGHT,              // Hyper+→  — right half
    WM_TOP,               // Hyper+↑  — top half
    WM_BOTM,              // Hyper+↓  — bottom half
};

// ── State tracking ──

#ifdef RGB_MATRIX_ENABLE
static bool rgb_user_enabled = false; // RGB backlight off by default
#endif

// clang-format off

// ── Keymaps (generated from elora.vil) ──

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_elora_hlc(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        LT(5, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
        LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_MINS, LSFT(KC_MINS), KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        TT(5), KC_LALT, KC_ENT, KC_LGUI, OSM(MOD_HYPR), LT(4, KC_BSPC), LT(3, KC_SPC), KC_RGUI, KC_LCTL, QK_CAPS_WORD_TOGGLE,
        KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [_DVORAK] = LAYOUT_elora_hlc(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_ESC,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC,
        LCTL_T(KC_ESC), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, RCTL_T(KC_MINS),
        KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_LBRC, KC_CAPS, MO(5), KC_RBRC, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT,
        MO(6), KC_LGUI, LALT_T(KC_ENT), KC_SPC, MO(3), MO(4), KC_SPC, KC_RALT, KC_RGUI, KC_APP,
        KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [_COLEMAK] = LAYOUT_elora_hlc(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_ESC,
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        LCTL_T(KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, RCTL_T(KC_QUOT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LBRC, KC_CAPS, MO(5), KC_RBRC, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        MO(6), KC_LGUI, LALT_T(KC_ENT), KC_SPC, MO(3), MO(4), KC_SPC, KC_RALT, KC_RGUI, KC_APP,
        KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [_NAV] = LAYOUT_elora_hlc(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_VOLU, KC_DEL,
        KC_TRNS, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_VOLD, KC_INS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCRL, KC_TRNS, KC_TRNS, KC_PAUS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_SYM] = LAYOUT_elora_hlc(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        LSFT(KC_GRV), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), LSFT(KC_EQL),
        LSFT(KC_BSLS), KC_BSLS, LSFT(KC_SCLN), KC_SCLN, KC_MINS, KC_LBRC, LSFT(KC_LBRC), KC_TRNS, KC_TRNS, LSFT(KC_RBRC), KC_RBRC, LSFT(KC_MINS), KC_COMM, KC_DOT, KC_SLSH, LSFT(KC_SLSH),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /* Layer 5 — Function + macOS window management
     * Right hand keeps F1-F24. Left hand (home-row mods dropped):
     *   F = Fill, R = Return, C = Center    (Ctrl+Globe+{F,R,C}) — work as-is
     *   WASD arrow cross: W=↑ A=← S=↓ D=→   (Hyper+arrow, halves)
     *   Globe = raw Fn on bottom-row outer pinky (emoji/dictation/manual)
     *   NOTE: the halves send Hyper+arrow (not Globe — macOS remaps
     *   Globe+arrow to Home/End). Bind Hyper+arrow to the Move & Resize
     *   menu items in System Settings > Keyboard Shortcuts > App Shortcuts.
     */
    [_FN] = LAYOUT_elora_hlc(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, WM_TOP, KC_NO, WM_RTRN, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO,
        KC_NO, WM_LEFT, WM_BOTM, WM_RGHT, WM_FILL, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO,
        AP_GLOB, KC_NO, KC_NO, WM_CNTR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_CAPS, KC_F24, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_L6] = LAYOUT_elora_hlc(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_L7] = LAYOUT_elora_hlc(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

// ── Encoder map (4 encoders: L soldered, L module, R soldered, R module) ──

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_DVORAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_COLEMAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_NAV] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_SYM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_L6] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_L7] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

// clang-format on

// ── Split sync: rgb_user_enabled from master → slave ──

#ifdef RGB_MATRIX_ENABLE
static void rgb_sync_slave_handler(uint8_t in_buflen, const void *in_data,
                                   uint8_t out_buflen, void *out_data) {
  if (in_buflen == sizeof(bool)) {
    rgb_user_enabled = *(const bool *)in_data;
  }
}
#endif

// ── Init RGB (kept enabled at driver level so indicators_advanced still runs)
// ──

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  transaction_register_rpc(USER_SYNC_RGB, rgb_sync_slave_handler);
  rgb_matrix_enable_noeeprom();
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv_noeeprom(0, 0, 0);
  // rgb_user_enabled starts false — LEDs off until user presses RM_TOGG
#endif
}

// ── macOS Globe chord: hold Ctrl + Globe (consumer 0x29D), tap a key ──
// Requires KEYBOARD_SHARED_EP = yes so the consumer (Globe) and keyboard
// (Ctrl + key) reports coexist in one chord.

static void mac_globe_chord(uint16_t tapkey) {
  register_mods(MOD_BIT(KC_LCTL));
  host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT); // Globe down
  wait_ms(5);
  tap_code16(tapkey);
  host_consumer_send(0); // Globe up
  unregister_mods(MOD_BIT(KC_LCTL));
}

// ── Hyper chord for window halves ──
// The emulated Globe can't drive Fn+Ctrl+arrow tiling (macOS remaps Globe+
// arrow to Home/End first), so the halves send Hyper + arrow instead; bind
// these in System Settings > Keyboard > Keyboard Shortcuts > App Shortcuts.

static void hyper_chord(uint16_t tapkey) {
  const uint8_t hyper = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI) |
                        MOD_BIT(KC_LSFT);
  register_mods(hyper);
  tap_code16(tapkey);
  unregister_mods(hyper);
}

// ── Process keycodes: Globe + window management, plus RGB toggle ──

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case AP_GLOB:
    // Raw Globe/Fn: held while pressed (emoji picker, dictation, manual chords)
    host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT
                                             : 0);
    return false;
  case WM_FILL: if (record->event.pressed) mac_globe_chord(KC_F);     return false;
  case WM_CNTR: if (record->event.pressed) mac_globe_chord(KC_C);     return false;
  case WM_RTRN: if (record->event.pressed) mac_globe_chord(KC_R);     return false;
  case WM_LEFT: if (record->event.pressed) hyper_chord(KC_LEFT);  return false;
  case WM_RGHT: if (record->event.pressed) hyper_chord(KC_RIGHT); return false;
  case WM_TOP:  if (record->event.pressed) hyper_chord(KC_UP);    return false;
  case WM_BOTM: if (record->event.pressed) hyper_chord(KC_DOWN);  return false;
#ifdef RGB_MATRIX_ENABLE
  case RM_TOGG:
    if (record->event.pressed) {
      rgb_user_enabled = !rgb_user_enabled;
      transaction_rpc_send(USER_SYNC_RGB, sizeof(bool), &rgb_user_enabled);
    }
    return false; // don't pass to QMK's own toggle
  case RM_NEXT:
  case RM_PREV:
  case RM_HUEU:
  case RM_HUED:
  case RM_SATU:
  case RM_SATD:
  case RM_VALU:
  case RM_VALD:
  case RM_SPDU:
  case RM_SPDD:
    return false;
#endif
  default:
    return true;
  }
}

// ── Per-layer colors: per-key only (underglow replaced by TFT display) ──

#ifdef RGB_MATRIX_ENABLE
// Layers 0/1/2 are base alphas (LEDs off); 3+ are momentary layers.

static const uint8_t layer_colors[][3] = {
    [_QWERTY] = {0, 0, 0},    // off
    [_DVORAK] = {0, 0, 0},    // off
    [_COLEMAK] = {0, 0, 0},   // off
    [_NAV] = {0, 200, 200},   // cyan
    [_SYM] = {180, 0, 255},   // purple
    [_FN] = {255, 60, 0},     // red-orange
    [_L6] = {0, 0, 0},        // off
    [_L7] = {0, 0, 0},        // off
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (!rgb_matrix_is_enabled()) {
    rgb_matrix_enable_noeeprom();
  }

  // If user disabled backlight, turn everything off
  if (!rgb_user_enabled) {
    for (uint8_t i = led_min; i < led_max; i++) {
      rgb_matrix_set_color(i, 0, 0, 0);
    }
    return false;
  }

  uint8_t layer = get_highest_layer(layer_state | default_layer_state);

  // Base alpha layers (QWERTY/Dvorak/Colemak): all LEDs off
  if (layer <= _COLEMAK) {
    for (uint8_t i = led_min; i < led_max; i++) {
      rgb_matrix_set_color(i, 0, 0, 0);
    }
    return false;
  }

  uint8_t r_val = layer_colors[layer][0];
  uint8_t g_val = layer_colors[layer][1];
  uint8_t b_val = layer_colors[layer][2];

  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      uint8_t idx = g_led_config.matrix_co[r][c];
      if (idx == NO_LED || idx < led_min || idx >= led_max)
        continue;

      uint16_t kc =
          keymap_key_to_keycode(layer, (keypos_t){.row = r, .col = c});

      if (kc != KC_TRNS && kc != KC_NO) {
        rgb_matrix_set_color(idx, r_val, g_val, b_val);
      } else {
        rgb_matrix_set_color(idx, 0, 0, 0);
      }
    }
  }

  // Turn off underglow LEDs (display handles layer indication now)
  for (uint8_t i = led_min; i < led_max; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
      rgb_matrix_set_color(i, 0, 0, 0);
    }
  }

  return false;
}

// ── Sync rgb_user_enabled to slave half periodically ──

void housekeeping_task_user(void) {
  if (is_keyboard_master()) {
    static bool last_rgb = false;
    static uint32_t last_sync = 0;
    if (rgb_user_enabled != last_rgb || timer_elapsed32(last_sync) > 500) {
      if (transaction_rpc_send(USER_SYNC_RGB, sizeof(bool),
                               &rgb_user_enabled)) {
        last_rgb = rgb_user_enabled;
        last_sync = timer_read32();
      }
    }
  }
}
#endif

// ── TFT Display: layer name + status (left half) ──

#ifdef HLC_TFT_DISPLAY

static painter_font_handle_t user_font;

static const char *layer_names[] = {
    [_QWERTY] = "QWERTY", [_DVORAK] = "Dvorak", [_COLEMAK] = "Colemak",
    [_NAV] = "Nav",       [_SYM] = "Symbols",   [_FN] = "F-Keys",
    [_L6] = "Layer 6",    [_L7] = "Layer 7",
};

// HSV colors for display text (matching hlc_tft_display HSV scale)
static const uint8_t layer_display_hsv[][3] = {
    [_QWERTY] = {HSV_LAYER_0}, [_DVORAK] = {HSV_LAYER_0},
    [_COLEMAK] = {HSV_LAYER_0}, [_NAV] = {HSV_LAYER_1},
    [_SYM] = {HSV_LAYER_2}, [_FN] = {HSV_LAYER_3},
    [_L6] = {HSV_LAYER_4}, [_L7] = {HSV_LAYER_4},
};

// Build modifier names into buf (max 16 bytes: "GUI ALT CTL SFT\0")
static bool build_mod_str(uint8_t mods, char *buf) {
  char *p = buf;
  if (!mods) {
    *p = '\0';
    return false;
  }
  if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT) &&
      (mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT)) {
    *p++ = 'H';
    *p++ = 'Y';
    *p++ = 'P';
    *p++ = 'E';
    *p++ = 'R';
    *p = '\0';
    return true;
  }
  if (mods & MOD_MASK_GUI) {
    if (p > buf)
      *p++ = ' ';
    *p++ = 'G';
    *p++ = 'U';
    *p++ = 'I';
  }
  if (mods & MOD_MASK_ALT) {
    if (p > buf)
      *p++ = ' ';
    *p++ = 'A';
    *p++ = 'L';
    *p++ = 'T';
  }
  if (mods & MOD_MASK_CTRL) {
    if (p > buf)
      *p++ = ' ';
    *p++ = 'C';
    *p++ = 'T';
    *p++ = 'L';
  }
  if (mods & MOD_MASK_SHIFT) {
    if (p > buf)
      *p++ = ' ';
    *p++ = 'S';
    *p++ = 'F';
    *p++ = 'T';
  }
  *p = '\0';
  return true;
}

bool module_post_init_user(void) {
  user_font = qp_load_font_mem(font_Retron2000_27);
  return true;
}

bool display_module_housekeeping_task_user(bool second_display) {
  if (second_display) {
    return true; // no secondary display in our setup
  }

  static layer_state_t last_layer = 0xFF;
  static uint8_t last_mods = 0xFF;
  static uint8_t last_osm = 0xFF;
  static bool last_cw = false;
  static bool last_rgb = false;

  uint8_t layer = get_highest_layer(layer_state | default_layer_state);
  uint8_t mods = get_mods();
  uint8_t osm = get_oneshot_mods();
  bool cw = is_caps_word_on();
#ifdef RGB_MATRIX_ENABLE
  bool rgb_on = rgb_user_enabled;
#else
  bool rgb_on = false;
#endif

  if (layer != last_layer || mods != last_mods || osm != last_osm ||
      cw != last_cw || rgb_on != last_rgb) {
    // Clear entire surface
    qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);

    uint8_t h = layer_display_hsv[layer][0];
    uint8_t s = layer_display_hsv[layer][1];
    uint8_t v = layer_display_hsv[layer][2];

    // Draw layer name — centered horizontally, at the top
    const char *name = layer_names[layer];
    int16_t tw = qp_textwidth(user_font, name);
    int16_t x = (LCD_WIDTH - tw) / 2;
    int16_t y = 8;

    qp_drawtext_recolor(lcd_surface, x, y, user_font, name, h, s, v, HSV_BLACK);

    // Stack indicators below layer name (only active ones take space)
    int16_t cur_y = y + user_font->line_height + 8;

    // Held modifiers
    char mod_buf[16];
    if (build_mod_str(mods, mod_buf)) {
      int16_t mw = qp_textwidth(user_font, mod_buf);
      qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - mw) / 2, cur_y, user_font,
                          mod_buf, HSV_WHITE, HSV_BLACK);
      cur_y += user_font->line_height + 4;
    }

    // One-shot modifiers (armed, waiting for next keypress)
    char osm_buf[16];
    if (build_mod_str(osm, osm_buf)) {
      int16_t ow = qp_textwidth(user_font, osm_buf);
      qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - ow) / 2, cur_y, user_font,
                          osm_buf, HSV_CAPS_ON, HSV_BLACK);
      cur_y += user_font->line_height + 4;
    }

    // Caps Word indicator
    if (cw) {
      static const char *ctxt = "CAPS";
      int16_t cww = qp_textwidth(user_font, ctxt);
      qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - cww) / 2, cur_y, user_font,
                          ctxt, HSV_CAPS_ON, HSV_BLACK);
      cur_y += user_font->line_height + 4;
    }

    // RGB backlight status indicator
    if (rgb_on) {
      static const char *rtxt = "RGB";
      int16_t rw = qp_textwidth(user_font, rtxt);
      qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - rw) / 2, cur_y, user_font,
                          rtxt, h, s, v, HSV_BLACK);
    }

    last_layer = layer;
    last_mods = mods;
    last_osm = osm;
    last_cw = cw;
    last_rgb = rgb_on;
  }

  // Flush surface to physical LCD
  qp_surface_draw(lcd_surface, lcd, 0, 0, 0);

  return false; // skip default hlc_tft_display rendering
}

#endif

// ── Chordal hold: hand assignments ──

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_elora_hlc('L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
                     'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
                     'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
                     'L', 'L', 'L', 'L', 'L', 'L', '*', 'L', 'R', '*', 'R', 'R', 'R', 'R', 'R', 'R',
                     '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                     '*', '*', '*', '*', '*', '*', '*', '*', '*', '*');
#endif
