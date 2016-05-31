#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

/*
 * JIS配列として認識させた上で使用するキーマップ
 * 元々用意されているもの
 * 全角/半角 : KC_ZKHK
 * ろ(_)     : KC_RO
 * 円(\)     : KC_JYEN
 *
 * 割り当てし直したもの
 * ^ : JKC_CIRC = KC_EQL
 * @ : JKC_AT   = KC_LBRC
 * [ : JKC_LBRC = KC_RBRC
 * ] : JKC_RBRC = KC_BSLS
 * { : JKC_LCBR = LSFT(JKC_LBRC)
 * } : JKC_RCBR = LSFT(JKC_RBRC)
 * ( : JKC_LPRN = LSFT(KC_8)
 * ) : JKC_RPRN = LSFT(KC_9)
 */

#define JKC_CIRC KC_EQL          // ^
#define JKC_AT KC_LBRC           // @
#define JKC_LBRC KC_RBRC         // [
#define JKC_RBRC KC_BSLS         // ]
#define JKC_LCBR LSFT(JKC_LBRC)  // {
#define JKC_RCBR LSFT(JKC_RBRC)  // }
#define JKC_LPRN LSFT(KC_8)      // (
#define JKC_RPRN LSFT(KC_9)      // )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |  6   |           |  5   |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  ^   |           |  \   |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | =/Ctrl |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   :    |
 * |--------+------+------+------+------+------|  -   |           |  -   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |_/RShift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ~L1  |ZenHan|Alt   | LGui |ESC   |                                       |L2/Ent|BkSpc |   [  |   ]  | ~L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Left |Right |       | Left | Right  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Up   |       | Up   |        |      |
 *                                 |L1/   |      |------|       |------|        |L1/   |
 *                                 |Space |EISU  | Down |       | Down |KANA    |Space |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
        KC_TAB,         KC_Q,         KC_W,    KC_E,   KC_R,   KC_T,   JKC_CIRC,
        CTL_T(KC_EQL),  KC_A,         KC_S,    KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   KC_MINS,
        KC_LANG2,       KC_ZKHK,      KC_LALT, KC_LGUI,KC_ESC,

                                               KC_LEFT,                 KC_RGHT,
                                                                        KC_UP,
                                               LT(SYMB, KC_SPC),KC_LANG2,KC_DOWN,
        // right hand
        KC_5,         KC_6,   KC_7,   KC_8,   KC_9,    KC_0,             KC_MINS,
        KC_JYEN,      KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,             JKC_AT,
                      KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,          KC_QUOT,
        KC_MINS,      KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_SLSH,   SFT_T(KC_RO),
                            LT(MDIA,KC_ENT), KC_BSPC, JKC_LBRC,JKC_RBRC,         KC_RO,

        KC_LEFT,         KC_RGHT,
        KC_UP,
        KC_DOWN,KC_LANG1,LT(SYMB, KC_SPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |   [  |   ]  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  &   |   {  |   }  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,JKC_LBRC, JKC_RBRC,KC_TRNS,KC_TRNS,
               KC_TRNS,KC_AMPR,JKC_LCBR, JKC_RCBR,KC_TRNS, KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      | WhUp |      |           |      |      |      |      |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | RESET  |      |MsLeft|MsDown|MsRght|WhDown|------|           |------| Left | Down | Up   | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_WH_U, KC_TRNS,
       RESET,   KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
                 KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
