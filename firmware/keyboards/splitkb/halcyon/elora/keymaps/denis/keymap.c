/**
 * Elora Rev2 — Denis's keymap (compiled from elora-optimized.vil)
 *
 * Features:
 *   - RGB: active keys lit per-layer color (cyan/purple/red/green/yellow)
 *   - Per-key tapping term for HRM
 *   - Chordal hold (bilateral combos)
 */

#include QMK_KEYBOARD_H

// ── Aliases ──

#define _BASE  0
#define _NAV   1
#define _SYM   2
#define _FN    3
#define _MOUSE 4
#define _SYS   5

#define HYPER OSM(MOD_HYPR)

// ── Lock mode state ──

static bool     keyboard_locked    = false;
static uint32_t lock_combo_start   = 0;    // 0 = combo not active
static uint8_t  denied_key_led     = NO_LED;
static uint32_t denied_flash_start = 0;

// Physical matrix positions of the 4 corner keys (discovered at boot)
static keypos_t corner_pos[4];
// LED indices for number row 1→0 in left-to-right order (discovered at boot)
static uint8_t  numrow_leds[LOCK_PROGRESS_STEPS];

// ── Tap dance state detection ──

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

static td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    }
    return TD_UNKNOWN;
}

// TD(0): tap=Space, hold=MO(_NAV), double-tap=TG(_NAV)
static td_state_t td0_state;
static void td0_finished(tap_dance_state_t *state, void *data) {
    td0_state = cur_dance(state);
    switch (td0_state) {
        case TD_SINGLE_TAP:  register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_NAV); break;
        case TD_DOUBLE_TAP:  layer_invert(_NAV); break;
        default: break;
    }
}
static void td0_reset(tap_dance_state_t *state, void *data) {
    if (td0_state == TD_SINGLE_TAP)  unregister_code(KC_SPC);
    if (td0_state == TD_SINGLE_HOLD) layer_off(_NAV);
    td0_state = TD_NONE;
}

// TD(1): tap=Backspace, hold=MO(_SYM), double-tap=TG(_SYM)
static td_state_t td1_state;
static void td1_finished(tap_dance_state_t *state, void *data) {
    td1_state = cur_dance(state);
    switch (td1_state) {
        case TD_SINGLE_TAP:  register_code(KC_BSPC); break;
        case TD_SINGLE_HOLD: layer_on(_SYM); break;
        case TD_DOUBLE_TAP:  layer_invert(_SYM); break;
        default: break;
    }
}
static void td1_reset(tap_dance_state_t *state, void *data) {
    if (td1_state == TD_SINGLE_TAP)  unregister_code(KC_BSPC);
    if (td1_state == TD_SINGLE_HOLD) layer_off(_SYM);
    td1_state = TD_NONE;
}

// TD(3): tap=Tab, hold=MO(_SYS)
static td_state_t td3_state;
static void td3_finished(tap_dance_state_t *state, void *data) {
    td3_state = cur_dance(state);
    switch (td3_state) {
        case TD_SINGLE_TAP:  register_code(KC_TAB); break;
        case TD_SINGLE_HOLD: layer_on(_SYS); break;
        default: break;
    }
}
static void td3_reset(tap_dance_state_t *state, void *data) {
    if (td3_state == TD_SINGLE_TAP)  unregister_code(KC_TAB);
    if (td3_state == TD_SINGLE_HOLD) layer_off(_SYS);
    td3_state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td0_finished, td0_reset),
    [1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td1_finished, td1_reset),
    [3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td3_finished, td3_reset),
};

// clang-format off

// ── Keymaps (translated from elora-optimized.vil) ──

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0 — Base (QWERTY + GACS home row mods)
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |   `    |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * | OS Sft |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Del   |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |Ctl/Esc |GUI/A |ALT/S |CTL/D |SFT/F |   G  |                              |   H  |SFT/J |CTL/K |ALT/L |GUI/; |Ctl/' "|
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |CapsWd|Hyper |  |OSL(1)| Enter|   N  |   M  |  , < |  . > |  / ? | RShift |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |⌘Space| LGui | TD3  | TD0  | MO3  |  | TD1  | MO4  | RGUI | RCtl |  -   |
     *                        `----------------------------------'  `----------------------------------'
     * ,-----------------------------------.                                              ,-----------------------------------.
     * | LAlt |      |       |      |      |                                              |OSL(2)|      |       |      |      |
     * `-----------------------------------'                                              `-----------------------------------'
     */
    [_BASE] = LAYOUT_elora_hlc(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
        OSM(MOD_LSFT), KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,            KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), RCTL_T(KC_QUOT),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CW_TOGG, HYPER,   OSL(1),  KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   G(KC_SPC), KC_LGUI, TD(3), TD(0),   MO(3),   TD(1),   MO(4),   KC_RGUI, KC_RCTL, KC_MINS,
        KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         OSL(2),  KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 1 — Navigation */
    [_NAV] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, G(KC_GRV), C(KC_LEFT), C(KC_RGHT), C(KC_UP), C(KC_DOWN),                         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_BSPC,
        _______, _______, _______, _______, _______, _______,                                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, G(KC_N), G(KC_T), G(KC_W), G(KC_LBRC), G(KC_RBRC), _______, _______, _______, _______, A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT), _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 2 — Symbols */
    [_SYM] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                                     S(KC_6), S(KC_7), S(KC_8), S(KC_EQL), KC_EQL, KC_BSPC,
        _______, KC_GRV,  S(KC_COMM), S(KC_LBRC), KC_LBRC, S(KC_9),                               S(KC_MINS), KC_MINS, KC_SLSH, KC_BSLS, S(KC_BSLS), S(KC_QUOT),
        _______, S(KC_GRV), S(KC_DOT), S(KC_RBRC), KC_RBRC, S(KC_0), _______, _______, _______, _______, S(KC_SCLN), KC_SCLN, S(KC_SLSH), _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 3 — F-Keys + Media */
    [_FN] = LAYOUT_elora_hlc(
        KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, _______, KC_BRIU, KC_BRID, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MNXT, KC_MPLY, KC_MPRV, _______,                                      _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 4 — Mouse */
    [_MOUSE] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______, _______,
        _______, _______, MS_BTN1, MS_BTN2, MS_BTN3, _______,                                      MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______, _______,
        _______, _______, MS_ACL0, MS_ACL1, MS_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 5 — System */
    [_SYS] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, SGUI(KC_3), SGUI(KC_4), SGUI(KC_5),                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      C(KC_LEFT), C(KC_DOWN), C(KC_UP), C(KC_RGHT), _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, G(KC_H), G(KC_M), G(KC_Q), _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 6 — Reserved (transparent) */
    [6] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    /* Layer 7 — Reserved (transparent) */
    [7] = LAYOUT_elora_hlc(
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         _______, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
};

// clang-format on

// ── Lock mode: discover matrix positions at boot ──

static void lock_find_positions(void) {
    const uint16_t corner_keys[4] = {KC_GRV, KC_EQL, KC_Z, KC_SLSH};
    const uint16_t numrow_keys[10] = {
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
    };

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            uint16_t kc = keymap_key_to_keycode(_BASE, (keypos_t){.row = r, .col = c});
            for (uint8_t i = 0; i < 4; i++) {
                if (kc == corner_keys[i]) {
                    corner_pos[i] = (keypos_t){.row = r, .col = c};
                }
            }
            for (uint8_t i = 0; i < 10; i++) {
                if (kc == numrow_keys[i]) {
                    numrow_leds[i] = g_led_config.matrix_co[r][c];
                }
            }
        }
    }
}

// ── Force RGB on at boot ──

void keyboard_post_init_user(void) {
    lock_find_positions();
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
#endif
}

// ── Lock mode helpers ──

static void lock_engage(void) {
    keyboard_locked = true;
    layer_state_set(1 << _BASE);
    clear_oneshot_mods();
    lock_combo_start = 0;
}

static void lock_disengage(void) {
    keyboard_locked = false;
    lock_combo_start = 0;
}

// ── Matrix scan: idle lock + combo detection ──

void matrix_scan_user(void) {
    if (!keyboard_locked && last_input_activity_elapsed() > LOCK_IDLE_TIMEOUT) {
        lock_engage();
    }

    bool all_corners = true;
    for (uint8_t i = 0; i < 4; i++) {
        if (!matrix_is_on(corner_pos[i].row, corner_pos[i].col)) {
            all_corners = false;
            break;
        }
    }

    if (all_corners) {
        if (lock_combo_start == 0) {
            lock_combo_start = timer_read32();
        } else if (timer_elapsed32(lock_combo_start) >= LOCK_COMBO_HOLD_MS) {
            if (keyboard_locked) {
                lock_disengage();
            } else {
                lock_engage();
            }
        }
    } else {
        lock_combo_start = 0;
    }
}

// ── Block user RGB control ──

#ifdef RGB_MATRIX_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Lock mode: block all keys and flash denied LED
    if (keyboard_locked && lock_combo_start == 0) {
        if (record->event.pressed) {
            uint8_t r = record->event.key.row;
            uint8_t c = record->event.key.col;
            uint8_t led = g_led_config.matrix_co[r][c];
            if (led != NO_LED) {
                denied_key_led     = led;
                denied_flash_start = timer_read32();
            }
        }
        return false;
    }

    switch (keycode) {
        case RM_TOGG: case RM_NEXT: case RM_PREV:
        case RM_HUEU: case RM_HUED: case RM_SATU:
        case RM_SATD: case RM_VALU: case RM_VALD:
        case RM_SPDU: case RM_SPDD:
            return false;
        default:
            return true;
    }
}

// ── Per-layer colors: active keys only ──

static const uint8_t layer_colors[][3] = {
    [_BASE]  = {  0,   0,   0},   // off
    [_NAV]   = {  0, 200, 200},   // cyan
    [_SYM]   = {180,   0, 255},   // purple
    [_FN]    = {255,  60,   0},   // red-orange
    [_MOUSE] = {  0, 200,   0},   // green
    [_SYS]   = {255, 200,   0},   // yellow
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable_noeeprom();
    }

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    // Blink underglow white when one-shot Hyper is armed
    bool osm_active = (get_oneshot_mods() & MOD_HYPR) == MOD_HYPR;

    if (layer == 0) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (osm_active && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                bool blink_on = (timer_read() % 500) < 250;
                rgb_matrix_set_color(i, blink_on ? 255 : 0, blink_on ? 255 : 0, blink_on ? 255 : 0);
            } else {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
        return false;
    }

    uint8_t r_val = layer < 6 ? layer_colors[layer][0] : 255;
    uint8_t g_val = layer < 6 ? layer_colors[layer][1] : 255;
    uint8_t b_val = layer < 6 ? layer_colors[layer][2] : 255;

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            uint8_t idx = g_led_config.matrix_co[r][c];
            if (idx == NO_LED || idx < led_min || idx >= led_max) continue;

            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){.row = r, .col = c});

            if (kc != KC_TRNS && kc != KC_NO) {
                rgb_matrix_set_color(idx, r_val, g_val, b_val);
            } else {
                rgb_matrix_set_color(idx, 0, 0, 0);
            }
        }
    }

    // Underglow LEDs: layer color, or blink white if one-shot Hyper armed
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            if (osm_active) {
                bool blink_on = (timer_read() % 500) < 250;
                rgb_matrix_set_color(i, blink_on ? 255 : 0, blink_on ? 255 : 0, blink_on ? 255 : 0);
            } else {
                rgb_matrix_set_color(i, r_val, g_val, b_val);
            }
        }
    }

    return false;
}
#endif

// ── Per-key tapping term ──

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LALT_T(KC_S):
        case LCTL_T(KC_D):
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case RCTL_T(KC_K):
        case RALT_T(KC_L):
        case RGUI_T(KC_SCLN):
            return 190;
        case LCTL_T(KC_ESC):
        case RCTL_T(KC_QUOT):
            return 200;
        default:
            return TAPPING_TERM;
    }
}

// ── Chordal hold: hand assignments ──

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_elora_hlc(
    'L', 'L', 'L', 'L', 'L', 'L',                                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', '*', '*',            '*', '*',     'R', 'R', 'R', 'R', 'R', 'R',
                        '*', '*', '*', '*', '*',    '*', '*', '*', '*', '*',
    '*', '*', '*', '*', '*',                                           '*', '*', '*', '*', '*'
);
#endif
