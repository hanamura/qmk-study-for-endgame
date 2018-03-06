#include "planck.h"
#include "action_layer.h"

void dance_l_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LSFT);
    register_code(KC_9);
  } else if (state->count == 2) {
    register_code(KC_LBRC);
  } else {
    register_code(KC_LSFT);
    register_code(KC_LBRC);
  }
}

void dance_l_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_LSFT);
    unregister_code(KC_9);
  } else if (state->count == 2) {
    unregister_code(KC_LBRC);
  } else {
    unregister_code(KC_LSFT);
    unregister_code(KC_LBRC);
  }
}

void dance_r_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LSFT);
    register_code(KC_0);
  } else if (state->count == 2) {
    register_code(KC_RBRC);
  } else {
    register_code(KC_LSFT);
    register_code(KC_RBRC);
  }
}

void dance_r_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_LSFT);
    unregister_code(KC_0);
  } else if (state->count == 2) {
    unregister_code(KC_RBRC);
  } else {
    unregister_code(KC_LSFT);
    unregister_code(KC_RBRC);
  }
}

enum {
  TD_L = 0,
  TD_R
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_l_finished, dance_l_reset),
  [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_r_finished, dance_r_reset),
};

// shortcuts
#define CAPTURE LGUI(LSFT(LCTL(KC_4)))

// prev / next actions
#define TAB_PREV LGUI(LSFT(KC_LBRC))
#define TAB_NEXT LGUI(LSFT(KC_RBRC))
#define PANE_PREV LGUI(KC_LBRC)
#define PANE_NEXT LGUI(KC_RBRC)

// mod taps
#define CMD_EISU MT(MOD_LGUI,KC_LANG2)
#define CMD_KANA MT(MOD_RGUI,KC_LANG1)
#define CTL_ESC MT(MOD_LCTL,KC_ESC)
#define SFT_TAB MT(MOD_LSFT,KC_TAB)

// mod
#define M_CAG LCTL(LALT(KC_LGUI))

// characters
#define C_ELPS LALT(KC_SCLN)
#define C_TRUDQ LALT(KC_LBRC)
#define C_TRUSQ LALT(KC_RBRC)

// tap dances
#define TDL TD(TD_L)
#define TDR TD(TD_R)

// layers
#define NUMPAD_Z LT(_NUMPAD,KC_Z)

// macos focuses
#define FO_MENU LCTL(KC_F2)
#define FO_TOOL LCTL(KC_F5)

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUMPAD,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NUMPAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_TAB,  KC_Q,     KC_W,    KC_E,     KC_R,  KC_T,    KC_Y,   KC_U,  KC_I,     KC_O,    KC_P,    KC_BSPC},
  {CTL_ESC, KC_A,     KC_S,    KC_D,     KC_F,  KC_G,    KC_H,   KC_J,  KC_K,     KC_L,    KC_SCLN, KC_ENT},
  {SFT_TAB, NUMPAD_Z, KC_X,    KC_C,     KC_V,  KC_B,    KC_N,   KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT},
  {M_CAG,   KC_LCTL,  KC_LALT, CMD_EISU, LOWER, KC_LSFT, KC_SPC, RAISE, CMD_KANA, KC_RALT, KC_RCTL, M_CAG}
},

[_LOWER] = {
  {KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS},
  {_______, KC_TILD, KC_GRV,  KC_DQT,  KC_QUOT, KC_UNDS, KC_MINS, TDL,     TDR,     KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, C_TRUDQ, C_TRUSQ, KC_PLUS, KC_EQL,  C_ELPS,  KC_PIPE, KC_LCBR, KC_RCBR, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_RAISE] = {
  {KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS},
  {_______, KC_TILD, KC_GRV,  KC_DQT,  KC_QUOT, KC_UNDS, KC_MINS, TDL,     TDR,     KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, C_TRUDQ, C_TRUSQ, KC_PLUS, KC_EQL,  C_ELPS,  KC_PIPE, KC_LCBR, KC_RCBR, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_NUMPAD] = {
  {_______, _______, _______, KC_UP,   _______, _______, KC_PPLS, KC_P7,   KC_P8, KC_P9,   KC_P0,   _______},
  {_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PMNS, KC_P4,   KC_P5, KC_P6,   KC_PAST, _______},
  {_______, _______, _______, _______, _______, _______, KC_PEQL, KC_P1,   KC_P2, KC_P3,   KC_PSLS, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_P0, KC_PDOT, KC_PCMM, _______}
},

[_ADJUST] = {
  {_______, _______, _______, KC_PGUP, KC_VOLU, FO_MENU,   FO_TOOL,   KC_BTN1, KC_MS_U,  KC_BTN2, _______, _______},
  {_______, _______, _______, KC_PGDN, KC_VOLD, TAB_PREV,  TAB_NEXT,  KC_MS_L, KC_MS_D,  KC_MS_R, _______, _______},
  {_______, RESET,   _______, _______, _______, PANE_PREV, PANE_NEXT, RGB_M_P, RGB_M_SW, RGB_M_X, _______, _______},
  {_______, _______, _______, _______, _______, CAPTURE,   _______,   _______, _______,  _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
