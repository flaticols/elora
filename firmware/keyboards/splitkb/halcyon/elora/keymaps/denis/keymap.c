/**
 * Elora Rev2 — Denis's keymap (compiled from elora-optimized.vil)
 *
 * Features:
 *   - TFT display (left half): layer name at top + LOCK/HYPER/CAPS/RGB status
 *   - Cirque trackpad (right half): cursor + tap/scroll gestures
 *   - RGB: optional per-key backlight (toggle via RM_TOGG), off by default
 *   - Per-key tapping term for HRM
 *   - Chordal hold (bilateral combos)
 *   - Leader key: lock layers via Leader→Space/Bksp/Tab = TG(Nav/Sym/Sys)
 */

#include QMK_KEYBOARD_H

#ifdef HLC_TFT_DISPLAY
#include "hlc_tft_display/hlc_tft_display.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#endif

// ── Aliases ──

#define _BASE  0
#define _NAV   1
#define _SYM   2
#define _FN    3
#define _MOUSE 4
#define _SYS   5

#define HYPER OSM(MOD_HYPR)

// ── State tracking ──

static uint8_t locked_layers = 0;

#ifdef RGB_MATRIX_ENABLE
static bool rgb_user_enabled = false;  // RGB backlight off by default
#endif

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
     *                        |Leader| LGui |Tab/Sy|Spc/Nv| MO3  |  |Bsp/Sm| MO4  | RGUI | RCtl |  -   |
     *                        `----------------------------------'  `----------------------------------'
     * ,-----------------------------------.                                              ,-----------------------------------.
     * | LAlt |      |       |      |      |                                              |OSL(2)|      |       |      |      |
     * `-----------------------------------'                                              `-----------------------------------'
     *
     * Leader sequences: Leader→Space = TG(Nav), Leader→Bksp = TG(Sym), Leader→Tab = TG(Sys)
     */
    [_BASE] = LAYOUT_elora_hlc(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
        OSM(MOD_LSFT), KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,            KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), RCTL_T(KC_QUOT),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CW_TOGG, HYPER,   OSL(1),  KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   QK_LEAD, KC_LGUI, LT(_SYS, KC_TAB), LT(_NAV, KC_SPC), MO(3), LT(_SYM, KC_BSPC), MO(4), KC_RGUI, KC_RCTL, KC_MINS,
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

// ── Init RGB (kept enabled at driver level so indicators_advanced still runs) ──

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
    // rgb_user_enabled starts false — LEDs off until user presses RM_TOGG
#endif
}

// ── RGB toggle (RM_TOGG toggles per-key backlight; other RGB keys blocked) ──

#ifdef RGB_MATRIX_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_TOGG:
            if (record->event.pressed) {
                rgb_user_enabled = !rgb_user_enabled;
            }
            return false;  // don't pass to QMK's own toggle
        case RM_NEXT: case RM_PREV:
        case RM_HUEU: case RM_HUED: case RM_SATU:
        case RM_SATD: case RM_VALU: case RM_VALD:
        case RM_SPDU: case RM_SPDD:
            return false;
        default:
            return true;
    }
}

// ── Per-layer colors: per-key only (underglow replaced by TFT display) ──

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

    // If user disabled backlight, turn everything off
    if (!rgb_user_enabled) {
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    // Base layer: all LEDs off
    if (layer == 0) {
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
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

    // Turn off underglow LEDs (display handles layer indication now)
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    return false;
}
#endif

// ── Leader key: lock layers via TG ──

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_SPC)) {
        layer_invert(_NAV);
        locked_layers = IS_LAYER_ON(_NAV)
            ? (locked_layers | (1 << _NAV))
            : (locked_layers & ~(1 << _NAV));
    } else if (leader_sequence_one_key(KC_BSPC)) {
        layer_invert(_SYM);
        locked_layers = IS_LAYER_ON(_SYM)
            ? (locked_layers | (1 << _SYM))
            : (locked_layers & ~(1 << _SYM));
    } else if (leader_sequence_one_key(KC_TAB)) {
        layer_invert(_SYS);
        locked_layers = IS_LAYER_ON(_SYS)
            ? (locked_layers | (1 << _SYS))
            : (locked_layers & ~(1 << _SYS));
    }
}

// ── TFT Display: layer name + status (left half) ──

#ifdef HLC_TFT_DISPLAY

static painter_font_handle_t user_font;

static const char *layer_names[] = {
    [_BASE]  = "Base",
    [_NAV]   = "Nav",
    [_SYM]   = "Symbols",
    [_FN]    = "F-Keys",
    [_MOUSE] = "Mouse",
    [_SYS]   = "System",
};

// HSV colors for display text (matching hlc_tft_display HSV scale)
static const uint8_t layer_display_hsv[][3] = {
    [_BASE]  = { HSV_LAYER_0 },   // white-ish
    [_NAV]   = { HSV_LAYER_1 },   // orange
    [_SYM]   = { HSV_LAYER_2 },   // yellow
    [_FN]    = { HSV_LAYER_3 },   // red
    [_MOUSE] = { HSV_LAYER_4 },   // green
    [_SYS]   = { HSV_LAYER_5 },   // purple
};

// Build modifier names into buf (max 16 bytes: "GUI ALT CTL SFT\0")
static bool build_mod_str(uint8_t mods, char *buf) {
    char *p = buf;
    if (!mods) { *p = '\0'; return false; }
    if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT) &&
        (mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT)) {
        *p++='H'; *p++='Y'; *p++='P'; *p++='E'; *p++='R'; *p='\0';
        return true;
    }
    if (mods & MOD_MASK_GUI)   { if (p>buf) *p++=' '; *p++='G'; *p++='U'; *p++='I'; }
    if (mods & MOD_MASK_ALT)   { if (p>buf) *p++=' '; *p++='A'; *p++='L'; *p++='T'; }
    if (mods & MOD_MASK_CTRL)  { if (p>buf) *p++=' '; *p++='C'; *p++='T'; *p++='L'; }
    if (mods & MOD_MASK_SHIFT) { if (p>buf) *p++=' '; *p++='S'; *p++='F'; *p++='T'; }
    *p = '\0';
    return true;
}

bool module_post_init_user(void) {
    user_font = qp_load_font_mem(font_Retron2000_27);
    return true;
}

bool display_module_housekeeping_task_user(bool second_display) {
    if (second_display) {
        return true;  // no secondary display in our setup
    }

    static layer_state_t last_layer  = 0xFF;
    static uint8_t       last_mods   = 0xFF;
    static uint8_t       last_osm    = 0xFF;
    static bool          last_cw     = false;
    static bool          last_lock   = false;
    static bool          last_rgb    = false;

    uint8_t layer  = get_highest_layer(layer_state | default_layer_state);
    uint8_t mods   = get_mods();
    uint8_t osm    = get_oneshot_mods();
    bool    cw     = is_caps_word_on();
    bool    lock   = (locked_layers & (1 << layer)) != 0;
#ifdef RGB_MATRIX_ENABLE
    bool    rgb_on = rgb_user_enabled;
#else
    bool    rgb_on = false;
#endif

    if (layer != last_layer || mods != last_mods || osm != last_osm
        || cw != last_cw || lock != last_lock || rgb_on != last_rgb) {
        // Clear entire surface
        qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);

        uint8_t h = (layer < 6) ? layer_display_hsv[layer][0] : 0;
        uint8_t s = (layer < 6) ? layer_display_hsv[layer][1] : 255;
        uint8_t v = (layer < 6) ? layer_display_hsv[layer][2] : 255;

        // Draw layer name — centered horizontally, at the top
        const char *name = (layer < 6) ? layer_names[layer] : "???";
        int16_t tw = qp_textwidth(user_font, name);
        int16_t x  = (LCD_WIDTH - tw) / 2;
        int16_t y  = 8;

        qp_drawtext_recolor(lcd_surface, x, y, user_font, name, h, s, v, HSV_BLACK);

        // Stack indicators below layer name (only active ones take space)
        int16_t cur_y = y + user_font->line_height + 8;

        // Layer lock indicator (shown in layer color)
        if (lock) {
            static const char *ltxt = "LOCK";
            int16_t lw = qp_textwidth(user_font, ltxt);
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - lw) / 2,
                                cur_y, user_font, ltxt, h, s, v, HSV_BLACK);
            cur_y += user_font->line_height + 4;
        }

        // Held modifiers (from home row mods, etc.)
        char mod_buf[16];
        if (build_mod_str(mods, mod_buf)) {
            int16_t mw = qp_textwidth(user_font, mod_buf);
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - mw) / 2,
                                cur_y, user_font, mod_buf, HSV_WHITE, HSV_BLACK);
            cur_y += user_font->line_height + 4;
        }

        // One-shot modifiers (armed, waiting for next keypress)
        char osm_buf[16];
        if (build_mod_str(osm, osm_buf)) {
            int16_t ow = qp_textwidth(user_font, osm_buf);
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - ow) / 2,
                                cur_y, user_font, osm_buf, HSV_CAPS_ON, HSV_BLACK);
            cur_y += user_font->line_height + 4;
        }

        // Caps Word indicator
        if (cw) {
            static const char *ctxt = "CAPS";
            int16_t cww = qp_textwidth(user_font, ctxt);
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - cww) / 2,
                                cur_y, user_font, ctxt, HSV_CAPS_ON, HSV_BLACK);
            cur_y += user_font->line_height + 4;
        }

        // RGB backlight status indicator
        if (rgb_on) {
            static const char *rtxt = "RGB";
            int16_t rw = qp_textwidth(user_font, rtxt);
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - rw) / 2,
                                cur_y, user_font, rtxt, h, s, v, HSV_BLACK);
        }

        last_layer = layer;
        last_mods  = mods;
        last_osm   = osm;
        last_cw    = cw;
        last_lock  = lock;
        last_rgb   = rgb_on;
    }

    // Flush surface to physical LCD
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);

    return false;  // skip default hlc_tft_display rendering
}

#endif

// ── Manual auto-mouse: activate _MOUSE layer on trackpad movement ──

#ifdef POINTING_DEVICE_ENABLE
static uint32_t auto_mouse_timer  = 0;
static bool     auto_mouse_active = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.x != 0 || mouse_report.y != 0) {
        if (!auto_mouse_active && !layer_state_is(_MOUSE)) {
            layer_on(_MOUSE);
            auto_mouse_active = true;
        }
        auto_mouse_timer = timer_read32();
    }
    if (auto_mouse_active && timer_elapsed32(auto_mouse_timer) > AUTO_MOUSE_TIME) {
        layer_off(_MOUSE);
        auto_mouse_active = false;
    }
    return mouse_report;
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
