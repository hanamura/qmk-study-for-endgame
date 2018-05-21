#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

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

extern uint8_t is_master;

#define _QWERTY 0
#define _WALK 1
#define _SELECT 2
#define _NUM 3
#define _LOWER 4
#define _RAISE 5
#define _BACKLIT 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  RGBRST
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = KEYMAP( \
      KC_TAB,              KC_Q,    KC_W,             KC_E,           KC_R,                  KC_T,                   KC_Y,  KC_U,                  KC_I,          KC_O,    KC_P,    KC_BSPC,             \
      MT(MOD_LCTL,KC_ESC), KC_A,    LT(_SELECT,KC_S), LT(_WALK,KC_D), LT(_NUM,KC_F),         KC_G,                   KC_H,  KC_J,                  KC_K,          KC_L,    KC_SCLN, KC_ENT,              \
      MT(MOD_LSFT,KC_TAB), KC_Z,    KC_X,             KC_C,           KC_V,                  KC_B,                   KC_N,  KC_M,                  KC_COMM,       KC_DOT,  KC_SLSH, MT(MOD_RSFT,KC_TAB), \
      LCTL(LALT(KC_LGUI)), _______, _______,          KC_LALT,        MT(MOD_LGUI,KC_LANG2), LOWER, KC_LSFT, KC_SPC, RAISE, MT(MOD_RGUI,KC_LANG1), LGUI(KC_LALT), _______, _______, _______              \
      ),

  [_WALK] = KEYMAP( \
      _______, _______, _______, _______, _______, XXXXXXX,                         LALT(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LALT(KC_RGHT), XXXXXXX,       _______, \
      _______, _______, _______, _______, _______, LGUI(KC_LEFT),                   KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT,       LGUI(KC_RGHT), _______, \
      _______, _______, _______, _______, _______, LGUI(KC_Z),                      LCTL(KC_K),    LGUI(KC_X),    LGUI(KC_C),  LGUI(KC_V),    XXXXXXX,       _______, \
      _______, _______, _______, _______, _______, _______,       _______, _______, _______,       _______,       _______,     _______,       _______,       _______  \
      ),

  [_SELECT] = KEYMAP( \
      _______, _______, _______, _______, _______, XXXXXXX,                               LSFT(LALT(KC_LEFT)), LSFT(LGUI(KC_DOWN)), LSFT(LGUI(KC_UP)), LSFT(LALT(KC_RGHT)), XXXXXXX,             _______, \
      _______, _______, _______, _______, _______, LSFT(LGUI(KC_LEFT)),                   LSFT(KC_LEFT),       LSFT(KC_DOWN),       LSFT(KC_UP),       LSFT(KC_RGHT),       LSFT(LGUI(KC_RGHT)), _______, \
      _______, _______, _______, _______, _______, LGUI(KC_Z),                            LCTL(KC_K),          LGUI(KC_X),          LGUI(KC_C),        LGUI(KC_V),          XXXXXXX,             _______, \
      _______, _______, _______, _______, _______, _______,             _______, _______, _______,             _______,             _______,           _______,             _______,             _______  \
      ),

  [_NUM] = KEYMAP( \
      _______, _______, _______, _______, _______, _______,                   KC_PPLS, KC_P7,   KC_P8,   KC_P9,   KC_P0,   _______, \
      _______, _______, _______, _______, _______, _______,                   KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),

  [_LOWER] = KEYMAP( \
      _______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC,                   KC_CIRC, KC_AMPR,       KC_ASTR,      _______,     KC_BSLS, _______, \
      _______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS,                   KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______, \
      _______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS,                   KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______, \
      _______, _______, _______, _______,       _______,       _______, _______, _______, _______, _______,       _______,      _______,     _______, _______  \
      ),

  [_RAISE] = KEYMAP( \
      _______, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,        KC_PERC,                   KC_CIRC, KC_AMPR,       KC_ASTR,      _______,     KC_BSLS, _______, \
      _______, KC_TILD, KC_GRV,  KC_DQT,        KC_QUOT,       KC_UNDS,                   KC_MINS, TD(TD_LEFT),   TD(TD_RIGHT), TD(TD_BOTH), _______, _______, \
      _______, _______, _______, LALT(KC_LBRC), LALT(KC_RBRC), KC_PLUS,                   KC_EQL,  LALT(KC_SCLN), KC_PIPE,      _______,     _______, _______, \
      _______, _______, _______, _______,       _______,       _______, _______, _______, _______, _______,       _______,      _______,     _______, _______  \
      ),

  [_BACKLIT] = KEYMAP( \
      _______, _______, _______,  _______,  _______, _______,                   _______, _______,  _______, _______, _______, _______, \
      _______, RGB_M_X, RGB_M_SN, RGB_M_R,  RGB_M_P, RGBRST,                    RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, _______, \
      _______, RGB_M_G, RGB_M_K,  RGB_M_SW, RGB_M_B, _______,                   _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, \
      _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______  \
      ),

  [_ADJUST] = KEYMAP( \
      _______, _______, _______, KC_PGUP, KC_VOLU, LCTL(KC_F2),                           LCTL(KC_F5),         BACKLIT, LGUI(LSFT(LCTL(KC_4))), _______, _______, _______, \
      _______, _______, _______, KC_PGDN, KC_VOLD, LGUI(LSFT(KC_LBRC)),                   LGUI(LSFT(KC_RBRC)), QWERTY,  LGUI(LSFT(KC_4)),       _______, _______, _______, \
      _______, RESET,   _______, _______, _______, LGUI(KC_LBRC),                         LGUI(KC_RBRC),       _______, LGUI(LSFT(KC_3)),       _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,             _______, _______, _______,             _______, _______,                _______, _______, _______  \
      )
};

bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
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
        if (TOG_STATUS) {
        } else {
          TOG_STATUS = !TOG_STATUS;
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        if (TOG_STATUS) {
        } else {
          TOG_STATUS = !TOG_STATUS;
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BACKLIT);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_config.mode;
#endif
#ifdef SSD1306OLED
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
  iota_gfx_init(!has_usb());
#endif
}

#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

#define L_BASE 0
#define L_WALK 2
#define L_SELECT 4
#define L_WALK_SELECT 6
#define L_NUM 8
#define L_LOWER 16
#define L_RAISE 32
#define L_ADJUST 65536
#define L_ADJUST_TRI 65584

static void render_logo(struct CharacterMatrix *matrix) {
  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
}

void render_status(struct CharacterMatrix *matrix) {
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
  switch (layer_state) {
    case L_BASE:
      matrix_write_P(matrix, PSTR("Qwerty"));
      break;
    case L_WALK:
      matrix_write_P(matrix, PSTR("Text Walk"));
      break;
    case L_SELECT:
    case L_WALK_SELECT:
      matrix_write_P(matrix, PSTR("Text Select"));
      break;
    case L_NUM:
      matrix_write_P(matrix, PSTR("Numpad"));
      break;
    case L_LOWER:
      matrix_write_P(matrix, PSTR("Lower"));
      break;
    case L_RAISE:
      matrix_write_P(matrix, PSTR("Raise"));
      break;
    case L_ADJUST:
    case L_ADJUST_TRI:
      matrix_write_P(matrix, PSTR("Adjust"));
      break;
    default:
      matrix_write(matrix, buf);
  }

  char led[40];
  snprintf(led, sizeof(led), "\n%s  %s  %s",
      (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
      (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
      (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
