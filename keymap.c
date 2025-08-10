#include QMK_KEYBOARD_H

// Tap dance declarations
enum tap_dance_codes {
    CTRL_CAPS = 0
};

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
        TD(CTRL_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        MO(2), KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),
    
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_MUTE,
        _______, _______, _______, _______, _______, HUE_INC, SAT_INC, BRIGHT_INC, _______, _______, KC_PSCR, KC_SCRL, _______, _______, KC_END,
        KC_CAPS, _______, THEME_OUTRUN, RGB_MOD, THEME_PHOSPHOR, HUE_DEC, SAT_DEC, BRIGHT_DEC, _______, _______, _______, _______, _______, KC_VOLU,
        _______, _______, _______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, _______, _______, KC_PGUP, KC_VOLD,
        _______, AG_LNRM, AG_LSWP, KC_MPLY, _______, _______, KC_HOME, KC_PGDN, KC_END),
    
    
    [2] = LAYOUT_65_ansi_blocker(
      _______, _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, KC_HOME, KC_UP  , KC_END  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
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

// Tap dance functions
void dance_ctrl_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LCTL);
    } else if (state->count == 2) {
        tap_code(KC_CAPS);
    }
}

void dance_ctrl_caps_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LCTL);
    }
}

// Tap dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [CTRL_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ctrl_caps_finished, dance_ctrl_caps_reset)
};

// Helper function to get LED index from matrix position
uint8_t get_led_index(uint8_t row, uint8_t col) {
    if (row >= MATRIX_ROWS || col >= MATRIX_COLS) {
        return NO_LED;
    }
    return g_led_config.matrix_co[row][col];
}

// Function to check if a keycode is not KC_TRNS (transparent)
bool is_key_bound(uint16_t keycode) {
    return keycode != KC_TRNS && keycode != KC_NO;
}

// RGB Matrix indicators for layer highlighting
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);
    
    // Only highlight on layers 1 and 2
    if (current_layer == 1 || current_layer == 2) {
        // First dim all LEDs
        for (uint8_t i = led_min; i < led_max; i++) {
            // Only dim key LEDs, not underglow
            if (HAS_FLAGS(g_led_config.flags[i], (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER))) {
                rgb_matrix_set_color(i, 0, 0, 0);  // Turn off
            }
        }
        
        // Then light up bound keys
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});
                if (is_key_bound(keycode)) {
                    uint8_t led_index = get_led_index(row, col);
                    if (led_index != NO_LED && led_index >= led_min && led_index < led_max) {
                        // Light up bound keys with a bright color
                        if (current_layer == 1) {
                            rgb_matrix_set_color(led_index, 0, 255, 255);  // Cyan for layer 1
                        } else if (current_layer == 2) {
                            rgb_matrix_set_color(led_index, 255, 0, 255);  // Magenta for layer 2
                        }
                    }
                }
            }
        }
    }
    
    return true;
}
