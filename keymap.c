#include QMK_KEYBOARD_H

// Custom keycodes for theme switching, hue, brightness, and saturation adjustment
enum custom_keycodes {
    THEME_OUTRUN = SAFE_RANGE,
    THEME_PHOSPHOR,
    HUE_INC,
    HUE_DEC,
    BRIGHT_INC,
    BRIGHT_DEC,
    SAT_INC,
    SAT_DEC
};

keymap_config_t keymap_config;

// Global variables for adjustable hue, brightness, and saturation
uint8_t custom_hue = 30;        // Default orange hue
uint8_t custom_brightness = 230; // Default brightness
uint8_t custom_saturation = 255; // Default full saturation

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        MO(2), KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),
    
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_MUTE,
        _______, _______, _______, _______, _______, HUE_INC, SAT_INC, BRIGHT_INC, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_END,
        KC_CAPS, RGB_RMOD, THEME_OUTRUN, RGB_MOD, THEME_PHOSPHOR, HUE_DEC, SAT_DEC, BRIGHT_DEC, _______, _______, _______, _______, _______, KC_VOLU,
        _______, _______, _______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, _______, _______, KC_PGUP, KC_VOLD,
        _______, AG_LNRM, AG_LSWP, KC_MPLY, _______, _______, KC_HOME, KC_PGDN, KC_END),
    
    
    [2] = LAYOUT_65_ansi_blocker(
      _______, _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, KC_UP  , _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
      _______, _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP, _______, \
      _______, _______, _______,                             _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END  \
    ),
    
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void){
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_outrun_sunset);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void){};

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case THEME_OUTRUN:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_outrun_sunset);
            }
            return false;
        case THEME_PHOSPHOR:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_orange_phosphor);
            }
            return false;
        case HUE_INC:
            if (record->event.pressed) {
                custom_hue = (custom_hue + 5) % 255;  // Increase hue by 5, wrap at 255
            }
            return false;
        case HUE_DEC:
            if (record->event.pressed) {
                custom_hue = (custom_hue - 5 + 255) % 255;  // Decrease hue by 5, wrap at 0
            }
            return false;
        case BRIGHT_INC:
            if (record->event.pressed) {
                if (custom_brightness <= 240) {
                    custom_brightness += 15;  // Increase brightness by 15
                } else {
                    custom_brightness = 255;  // Cap at maximum
                }
            }
            return false;
        case BRIGHT_DEC:
            if (record->event.pressed) {
                if (custom_brightness >= 25) {
                    custom_brightness -= 15;  // Decrease brightness by 15
                } else {
                    custom_brightness = 10;   // Minimum usable brightness
                }
            }
            return false;
        case SAT_INC:
            if (record->event.pressed) {
                if (custom_saturation <= 240) {
                    custom_saturation += 15;  // Increase saturation by 15
                } else {
                    custom_saturation = 255;  // Cap at maximum
                }
            }
            return false;
        case SAT_DEC:
            if (record->event.pressed) {
                if (custom_saturation >= 25) {
                    custom_saturation -= 15;  // Decrease saturation by 15
                } else {
                    custom_saturation = 10;   // Minimum usable saturation
                }
            }
            return false;
    }
    return true; // Process all other keycodes normally
}
