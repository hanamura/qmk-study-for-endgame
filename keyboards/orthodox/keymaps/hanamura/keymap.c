#include "orthodox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

void dance_left_finished(qk_tap_dance_state_t *state, void *user_data) {
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

void dance_left_reset(qk_tap_dance_state_t *state, void *user_data) {
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

void dance_right_finished(qk_tap_dance_state_t *state, void *user_data) {
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

void dance_right_reset(qk_tap_dance_state_t *state, void *user_data) {
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

void dance_both_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LSFT);
    register_code(KC_9);
    register_code(KC_0);
  } else if (state->count == 2) {
    register_code(KC_LBRC);
    register_code(KC_RBRC);
  } else {
    register_code(KC_LSFT);
    register_code(KC_LBRC);
    register_code(KC_RBRC);
  }
}

void dance_both_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_LSFT);
    unregister_code(KC_9);
    unregister_code(KC_0);
  } else if (state->count == 2) {
    unregister_code(KC_LBRC);
    unregister_code(KC_RBRC);
  } else {
    unregister_code(KC_LSFT);
    unregister_code(KC_LBRC);
    unregister_code(KC_RBRC);
  }
}

enum {
  TD_LEFT = 0,
  TD_RIGHT,
  TD_BOTH
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_finished, dance_left_reset),
  [TD_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_finished, dance_right_reset),
  [TD_BOTH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_both_finished, dance_both_reset),
};

#define _QWERTY 0
#define _WALK 1
#define _SELECT 2
#define _NUM 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = KEYMAP( \
      KC_TAB,              KC_Q,                   KC_W,           KC_E,          KC_R, KC_T,                                                                                   KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,            \
      MT(MOD_LCTL,KC_ESC), KC_A, LT(_SELECT,KC_S), LT(_WALK,KC_D), LT(_NUM,KC_F), KC_G,                              KC_LALT, _______, _______, KC_LSFT,                        KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENT,             \
      MT(MOD_LSFT,KC_TAB), KC_Z,                   KC_X,           KC_C,          KC_V, KC_B, MT(MOD_LGUI,KC_LANG2), LOWER,   KC_ENT,  KC_SPC,  RAISE,   MT(MOD_RGUI,KC_LANG1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_LSFT,KC_TAB) \
      ),

  [_WALK] = KEYMAP( \
      _______, _______, _______, _______, _______, XXXXXXX,                                                             LALT(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LALT(KC_RGHT), XXXXXXX,       _______, \
      _______, _______, _______, _______, _______, LGUI(KC_LEFT),          _______, _______, _______, _______,          KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT,       LGUI(KC_RGHT), _______, \
      _______, _______, _______, _______, _______, LGUI(KC_Z),    _______, _______, _______, _______, _______, _______, LCTL(KC_K),    LGUI(KC_X),    LGUI(KC_C),  LGUI(KC_V),    XXXXXXX,       _______  \
      ),

  [_SELECT] = KEYMAP( \
      _______, _______, _______, _______, _______, XXXXXXX,                                                                   LSFT(LALT(KC_LEFT)), LSFT(LGUI(KC_DOWN)), LSFT(LGUI(KC_UP)), LSFT(LALT(KC_RGHT)), XXXXXXX,             _______, \
      _______, _______, _______, _______, _______, LSFT(LGUI(KC_LEFT)),          _______, _______, _______, _______,          LSFT(KC_LEFT),       LSFT(KC_DOWN),       LSFT(KC_UP),       LSFT(KC_RGHT),       LSFT(LGUI(KC_RGHT)), _______, \
      _______, _______, _______, _______, _______, LGUI(KC_Z),          _______, _______, _______, _______, _______, _______, LCTL(KC_K),          LGUI(KC_X),          LGUI(KC_C),        LGUI(KC_V),          XXXXXXX,             _______  \
      ),

  [_NUM] = KEYMAP( \
      _______, _______, _______, _______, _______, _______,                                                       KC_PPLS, KC_P7, KC_P8, KC_P9, KC_P0,   _______, \
      _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,          KC_PMNS, KC_P4, KC_P5, KC_P6, KC_PAST, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PEQL, KC_P1, KC_P2, KC_P3, KC_PSLS, _______  \
      ),

  [_LOWER] = KEYMAP( \
      _______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC,                                                       KC_CIRC, KC_AMPR,       KC_ASTR,      KC_BSLS,     _______, _______, \
      _______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS,          _______, _______, _______, _______,          KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______, \
      _______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS, _______, _______, _______, _______, _______, _______, KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______  \
      ),

  [_RAISE] = KEYMAP( \
      _______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC,                                                       KC_CIRC, KC_AMPR,       KC_ASTR,      KC_BSLS,     _______, _______, \
      _______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS,          _______, _______, _______, _______,          KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______, \
      _______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS, _______, _______, _______, _______, _______, _______, KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______  \
      ),

  [_ADJUST] =  KEYMAP( \
      _______, _______, _______, KC_PGUP, KC_VOLU, LCTL(KC_F2),                                                               LCTL(KC_F5),         _______, LGUI(LSFT(LCTL(KC_4))), _______, _______, _______, \
      _______, _______, _______, KC_PGDN, KC_VOLD, LGUI(LSFT(KC_LBRC)),          _______, _______, _______, _______,          LGUI(LSFT(KC_RBRC)), _______, LGUI(LSFT(KC_4)),       _______, _______, _______, \
      _______, RESET,   _______, _______, _______, LGUI(KC_LBRC),       _______, _______, _______, _______, _______, _______, LGUI(KC_RBRC),       _______, LGUI(LSFT(KC_3)),       _______, _______, _______  \
      )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_QWERTY);
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
  case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);
    }
    return false;
    break;
  }
  return true;
}
