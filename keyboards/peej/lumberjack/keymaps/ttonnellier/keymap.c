/* Copyright 2020 Paul James
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
  _QWERTY = 0,
  _FUNCTION
};

#define FN MO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   `  |  1   |  2   |  3   |  4   |  5   | |  6   |  7   |  8   |  9   |  0   | BkSp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   | |  Y   |  U   |  I   |  O   |  P   | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   | |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft |  Z   |  X   |  C   |  V   |  B   | |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl |  Fn  | Alt  | Cmd  |  Fn  | Spac | | Spac |  Fn  | Left | Down |  Up  | Rght |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    QK_GESC,       KC_1,    KC_2,    KC_3,   KC_4, KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,        KC_Q,    KC_W,    KC_E,   KC_R, KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    KC_LSFT,       KC_A,    KC_S,    KC_D,   KC_F, KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, RSFT_T(KC_QUOT),
    KC_LCTL,       KC_Z,    KC_X,    KC_C,   KC_V, KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LBRC,
    LCTL(KC_LALT), KC_LGUI, KC_LALT, KC_GRV, FN,   KC_SPC, KC_ENT, KC_BSPC, KC_DEL,  KC_RALT, KC_BSLS, KC_RBRC
),

/* Function
* ,------------------------------------------. ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  | |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 | |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_5x12(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, _______,
  KC_CAPS, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, KC_BRID, KC_CALC, KC_BRIU, QK_BOOT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

void keyboard_pre_init_user() {
    writePin(LED1, true);
    writePin(LED2, true);
}

void keyboard_post_init_user() {
    writePin(LED1, false);
    writePin(LED2, false);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED2, state);

    return state;
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED1, led_state.caps_lock);
    }
    return res;
}

