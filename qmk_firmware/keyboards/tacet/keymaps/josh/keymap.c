#include "kb.h"

// Tacet Rev. 1

enum custom_keycodes {
  SEARCH = SAFE_RANGE,
  MAKE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEARCH:
      if (record->event.pressed) {
        // when keycode SEARCH is pressed
        SEND_STRING(SS_LCTL("c"));
	_delay_ms(100);
        SEND_STRING(SS_LCTL("t"));
	_delay_ms(250);
        SEND_STRING(SS_LCTL("v"));
	SEND_STRING(SS_TAP(X_ENTER));
      } else {
      }
      break;
    case MAKE:
      if (record->event.pressed) {
        SEND_STRING(SS_RGUI("q"));
	_delay_ms(250);
	SEND_STRING("msys2 mingw 64-bit");
	_delay_ms(500);
	tap_code(KC_ENTER);
	_delay_ms(1500);
	SEND_STRING("cd c:/users/joshr/documents/kb/qmk_firmware");
	tap_code(KC_ENTER);
	_delay_ms(100);
	SEND_STRING("make tacet:josh:dfu");
	tap_code(KC_ENTER);
	_delay_ms(100);
	reset_keyboard();
      } else {
      }
      break;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
};

// Enums defined for all examples:
enum {
    TD_COL,
    TD_QUO,
    TD_MUN,
    TD_PLE,
    TD_LSPB,
    TD_RSPB,
    TD_LBRC,
    TD_RBRC,
    TD_QUE
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SCLN);
    } else {
        register_code16(S(KC_SCLN));
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code16(S(KC_COLN));
    }
}

void dance_quo_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_QUOT);
    } else {
        register_code16(S(KC_QUOT));
    }
}

void dance_quo_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_QUOT);
    } else {
        unregister_code16(S(KC_QUOT));
    }
}

void dance_mun_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_MINS);
    } else {
        register_code16(S(KC_MINS));
    }
}

void dance_mun_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_MINS);
    } else {
        unregister_code16(S(KC_MINS));
    }
}

void dance_ple_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_EQL);
    } else {
        register_code16(S(KC_EQL));
    }
}

void dance_ple_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_EQL);
    } else {
        unregister_code16(S(KC_EQL));
    }
}

void dance_lbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LBRC);
    } else {
        register_code16(S(KC_LBRC));
    }
}

void dance_lbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LBRC);
    } else {
        unregister_code16(S(KC_LBRC));
    }
}

void dance_rbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_RBRC);
    } else {
        register_code16(S(KC_RBRC));
    }
}

void dance_rbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_RBRC);
    } else {
        unregister_code16(S(KC_RBRC));
    }
}

void dance_que_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SLSH);
    } else {
        register_code16(S(KC_SLSH));
    }
}

void dance_que_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SLSH);
    } else {
        unregister_code16(S(KC_SLSH));
    }
}

// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) return DOUBLE_TAP;
    else return 8;
}

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};


// Functions that control what our tap dance key does
void ls_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            tap_code16(S(KC_9));
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
	    tap_code16(S(KC_LBRC));
            break;
    }
}

void ls_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    ql_tap_state.state = 0;
}

// Functions that control what our tap dance key does
void rs_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            tap_code16(S(KC_0));
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT));
            break;
        case DOUBLE_TAP:
	    tap_code16(S(KC_RBRC));
            break;
    }
}

void rs_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_RSFT));
    }
    ql_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_COL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, dance_cln_reset, 155),
    [TD_QUO] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_quo_finished, dance_quo_reset, 155),
    [TD_MUN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mun_finished, dance_mun_reset),
    [TD_PLE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_ple_finished, dance_ple_reset, 155),
    [TD_LSPB] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ls_finished, ls_reset, 155),
    [TD_RSPB] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, rs_finished, rs_reset, 155),
    [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_lbrc_finished, dance_lbrc_reset, 155),
    [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_rbrc_finished, dance_rbrc_reset, 155),
    [TD_QUE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_que_finished, dance_que_reset, 155)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    TD(TD_MUN), TD(TD_PLE),  KC_BSLS, KC_GRV, \
 		LT(2,KC_TAB),  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   TD(TD_LBRC), TD(TD_RBRC), KC_BSPC, KC_DEL, \
  		KC_LCTL, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    TD(TD_COL), TD(TD_QUO),          KC_ENT, KC_PGUP,  \
  		TD(TD_LSPB), KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  TD(TD_QUE), TD(TD_RSPB), KC_UP,   KC_PGDN,           \
  		KC_CLCK, KC_LGUI, KC_LALT,                KC_SPC,                          TT(1),KC_LEFT,KC_DOWN,KC_RIGHT),

	KEYMAP(
		KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,      _______,_______, \
   		KC_TAB,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BRID,KC_BRIU,     LSFT(LCTL(KC_T)),KC_MUTE,   \
   		KC_CLCK,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,            MAKE,KC_HOME, \
           	_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,       _______,KC_VOLU,KC_END, \
    		RESET,  EEP_RST,_______,                     _______,                     _______,KC_MPRV,KC_VOLD,KC_MNXT),


	KEYMAP(
		KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,          _______,_______, \
   		KC_TAB,_______,_______,_______,_______,_______,_______,_______,_______,_______,SGUI(KC_S),KC_BRID,KC_BRIU,     LSFT(LCTL(KC_T)),KC_MUTE,   \
   		_______,_______,LGUI(KC_Q),LCTL(KC_J),LGUI(KC_E),_______,_______,_______,_______,_______,_______,_______,            MAKE,LALT(KC_PGUP), \
           	_______,_______,_______,SEARCH,_______,LCTL(KC_DOT),_______,_______,_______,_______,_______,       _______,KC_VOLU,LALT(KC_PGDN), \
    		RESET,  EEP_RST,_______,                     SGUI(KC_S),                     _______,LGUI(KC_LEFT),KC_VOLD, LGUI(KC_RIGHT)),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {

}