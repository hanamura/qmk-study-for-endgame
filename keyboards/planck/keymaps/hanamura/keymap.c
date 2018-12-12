#include "planck.h"
#include "action_layer.h"
#include "muse.h"

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

void dance_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LGUI);
    register_code(KC_LALT);
  } else if (state->count == 2) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
  } else {
    register_code(KC_LGUI);
    register_code(KC_LALT);
    register_code(KC_LSFT);
  }
}

void dance_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
  } else if (state->count == 2) {
    unregister_code(KC_LGUI);
    unregister_code(KC_LSFT);
  } else {
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
  }
}

enum {
  TD_LEFT = 0,
  TD_RIGHT,
  TD_BOTH,
  TD_MOD
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_finished, dance_left_reset),
  [TD_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_finished, dance_right_reset),
  [TD_BOTH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_both_finished, dance_both_reset),
  [TD_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mod_finished, dance_mod_reset),
};

enum planck_layers {
  _QWERTY,
  _WALK,
  _SELECT,
  _NUM,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
    {KC_TAB,              KC_Q,     KC_W,             KC_E,                  KC_R,          KC_T,          KC_Y,   KC_U,       KC_I,                  KC_O,    KC_P,    KC_BSPC},
    {MT(MOD_LCTL,KC_ESC), KC_A,     LT(_SELECT,KC_S), LT(_WALK,KC_D),        LT(_NUM,KC_F), KC_G,          KC_H,   KC_J,       KC_K,                  KC_L,    KC_SCLN, MT(MOD_LCTL,KC_ENT)},
    {MT(MOD_LSFT,KC_TAB), KC_Z,     LCAG_T(KC_X),     KC_C,                  KC_V,          KC_B,          KC_N,   KC_M,       KC_COMM,               KC_DOT,  KC_SLSH, MT(MOD_LSFT,KC_TAB)},
    {RGB_TOG,             RGB_MOD,  KC_LALT,          MT(MOD_LGUI,KC_LANG2), MO(_LOWER),    LGUI(KC_LALT), KC_SPC, MO(_RAISE), MT(MOD_RGUI,KC_LANG1), KC_RALT, KC_LEFT, KC_RGHT}
  },

  [_WALK] = {
    {_______, _______, _______, _______, _______, XXXXXXX,       LALT(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LALT(KC_RGHT), XXXXXXX,       _______},
    {_______, _______, _______, _______, _______, LGUI(KC_LEFT), KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT,       LGUI(KC_RGHT), _______},
    {_______, _______, _______, _______, _______, LGUI(KC_Z),    LCTL(KC_K),    LGUI(KC_X),    LGUI(KC_C),  LGUI(KC_V),    XXXXXXX,       _______},
    {_______, _______, _______, _______, _______, _______,       _______,       _______,       _______,     _______,       _______,       _______}
  },

  [_SELECT] = {
    {_______, _______, _______, _______, _______, XXXXXXX,             LSFT(LALT(KC_LEFT)), LSFT(LGUI(KC_DOWN)), LSFT(LGUI(KC_UP)), LSFT(LALT(KC_RGHT)), XXXXXXX,             _______},
    {_______, _______, _______, _______, _______, LSFT(LGUI(KC_LEFT)), LSFT(KC_LEFT),       LSFT(KC_DOWN),       LSFT(KC_UP),       LSFT(KC_RGHT),       LSFT(LGUI(KC_RGHT)), _______},
    {_______, _______, _______, _______, _______, LGUI(KC_Z),          LCTL(KC_K),          LGUI(KC_X),          LGUI(KC_C),        LGUI(KC_V),          XXXXXXX,             _______},
    {_______, _______, _______, _______, _______, _______,             _______,             _______,             _______,           _______,             _______,             _______}
  },

  [_NUM] = {
    {_______, _______, _______, _______, _______, _______, KC_PPLS, KC_P7,   KC_P8,   KC_P9,   KC_P0,   _______},
    {_______, _______, _______, _______, _______, _______, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______},
    {_______, _______, _______, _______, _______, _______, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  },

  [_LOWER] = {
    {_______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC, KC_CIRC, KC_AMPR,       KC_ASTR,      KC_BSLS,     _______, _______},
    {_______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS, KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______},
    {_______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS, KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______},
    {_______, _______, _______, _______,       _______,       _______, _______, _______,       _______,      _______,     _______, _______}
  },

  [_RAISE] = {
    {_______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC, KC_CIRC, KC_AMPR,       KC_ASTR,      KC_BSLS,     _______, _______},
    {_______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS, KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______},
    {_______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS, KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______},
    {_______, _______, _______, _______,       _______,       _______, _______, _______,       _______,      _______,     _______, _______}
  },

  [_ADJUST] = {
    {_______, _______, _______, KC_PGUP, KC_VOLU, LCTL(KC_F2),         LCTL(KC_F5),         KC_BTN1, LGUI(LSFT(LCTL(KC_4))), _______, _______, _______},
    {_______, _______, _______, KC_PGDN, KC_VOLD, LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), KC_MS_L, LGUI(LSFT(KC_4)),       _______, _______, _______},
    {_______, RESET,   _______, _______, _______, LGUI(KC_LBRC),       LGUI(KC_RBRC),       RGB_M_P, LGUI(LSFT(KC_3)),       _______, _______, _______},
    {_______, _______, _______, _______, _______, _______,             _______,             _______, _______,                _______, _______, _______}
  }
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
