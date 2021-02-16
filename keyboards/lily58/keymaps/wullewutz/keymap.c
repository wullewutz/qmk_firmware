#include QMK_KEYBOARD_H
#include "keymap_german.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTZ = 0,
  _LO,
  _HI,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTZ] = LAYOUT( \
  KC_ESC,          DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                      DE_6,    DE_7,    DE_8,    DE_9,     DE_0,          DE_SS, \
  KC_TAB,          DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                      DE_Z,    DE_U,    DE_I,    DE_O,     DE_P,        DE_UDIA, \
  KC_LCTRL,        DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                      DE_H,    DE_J,    DE_K,    DE_L,  DE_ODIA,        DE_ADIA, \
  LSFT_T(DE_LABK), DE_Y,    DE_X,    DE_C,    DE_V,    DE_B, DE_PLUS, DE_HASH,    DE_N,    DE_M, DE_COMM,  DE_DOT,  DE_MINS, RSFT_T(KC_ENT), \
                                  KC_LGUI, KC_LALT, MO(_LO), KC_BSPC,  KC_SPC, MO(_HI), KC_BSPC, KC_DEL \
),

[_LO] = LAYOUT( \
  _______,      _______, _______, _______,  KC_END, _______,                   _______, _______, _______, _______, KC_HOME,        _______, \
  _______,      _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,        _______, \
  _______,      _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,        _______, \
  _______,      _______,  KC_DEL, _______, _______, _______, DE_LBRC, DE_RBRC, _______, _______, _______, _______, _______,        _______, \
                                  _______, _______, _______, _______, _______, _______, _______,  _______ \
),

[_HI] = LAYOUT( \
  DE_CIRC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,        DE_BSLS, \
  DE_TILD,        DE_AT, _______, DE_EURO, _______, _______,                   _______, _______, _______,  KC_F11,  KC_F12,        _______, \
  _______,      _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,        _______, \
  DE_PIPE,      _______, _______, _______, _______, _______, DE_LCBR, DE_RCBR, _______, DE_MICR, DE_ACUT, _______, _______,        _______, \
                                                    _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | / Space /       \Space \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
