/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

enum code_category {
	UnknownCategory = 0,
	GamepadButton,
	MouseButton,
	KeyboardKey,
	KeyboardNumpadKey,
	KeyboardMiscKey,
	AbsoluteAxis,
	RelativeAxis,
};

#define CODETABLE \
	{ "EV_KEY", EV_KEY, "Button", {\
		{ "BTN_SOUTH", BTN_SOUTH, GamepadButton, "Button South (A)" },\
		{ "BTN_EAST", BTN_EAST, GamepadButton, "Button East (B)" },\
		{ "BTN_C", BTN_C, GamepadButton, "Button C" },\
		{ "BTN_NORTH", BTN_NORTH, GamepadButton, "Button North (X)" },\
		{ "BTN_WEST", BTN_WEST, GamepadButton, "Button West (Y)" },\
		{ "BTN_Z", BTN_Z, GamepadButton, "Button Z" },\
		{ "BTN_TL", BTN_TL, GamepadButton, "Button L1" },\
		{ "BTN_TR", BTN_TR, GamepadButton, "Button R1" },\
		{ "BTN_TL2", BTN_TL2, GamepadButton, "Button L2 (digital)" },\
		{ "BTN_TR2", BTN_TR2, GamepadButton, "Button R2 (digital)" },\
		{ "BTN_SELECT", BTN_SELECT, GamepadButton, "Button Select" },\
		{ "BTN_START", BTN_START, GamepadButton, "Button Start" },\
		{ "BTN_MODE", BTN_MODE, GamepadButton, "Button Menu" },\
		{ "BTN_THUMBL", BTN_THUMBL, GamepadButton, "Button Thumb Left" },\
		{ "BTN_THUMBR", BTN_THUMBR, GamepadButton, "Button Thumb Right" },\
		{ "BTN_DPAD_UP", BTN_DPAD_UP, GamepadButton, "D-pad Up" },\
		{ "BTN_DPAD_DOWN", BTN_DPAD_DOWN, GamepadButton, "D-pad Down" },\
		{ "BTN_DPAD_LEFT", BTN_DPAD_LEFT, GamepadButton, "D-pad Left" },\
		{ "BTN_DPAD_RIGHT", BTN_DPAD_RIGHT, GamepadButton, "D-pad Right" },\
		{ "BTN_LEFT", BTN_LEFT, MouseButton, "Mouse Left" },\
		{ "BTN_RIGHT", BTN_RIGHT, MouseButton, "Mouse Right" },\
		{ "BTN_MIDDLE", BTN_MIDDLE, MouseButton, "Mouse Middle" },\
		{ "BTN_SIDE", BTN_SIDE, MouseButton, "Mouse 4" },\
		{ "BTN_EXTRA", BTN_EXTRA, MouseButton, "Mouse 5" },\
		{ "BTN_FORWARD", BTN_FORWARD, MouseButton, "Mouse Forward" },\
		{ "BTN_BACK", BTN_BACK, MouseButton, "Mouse Back" },\
		{ "BTN_TASK", BTN_TASK, MouseButton, "Mouse Task" },\
		{ "KEY_0", KEY_0, KeyboardKey, "0" },\
		{ "KEY_1", KEY_1, KeyboardKey, "1" },\
		{ "KEY_2", KEY_2, KeyboardKey, "2" },\
		{ "KEY_3", KEY_3, KeyboardKey, "3" },\
		{ "KEY_4", KEY_4, KeyboardKey, "4" },\
		{ "KEY_5", KEY_5, KeyboardKey, "5" },\
		{ "KEY_6", KEY_6, KeyboardKey, "6" },\
		{ "KEY_7", KEY_7, KeyboardKey, "7" },\
		{ "KEY_8", KEY_8, KeyboardKey, "8" },\
		{ "KEY_9", KEY_9, KeyboardKey, "9" },\
		{ "KEY_A", KEY_A, KeyboardKey, "A" },\
		{ "KEY_B", KEY_B, KeyboardKey, "B" },\
		{ "KEY_C", KEY_C, KeyboardKey, "C" },\
		{ "KEY_D", KEY_D, KeyboardKey, "D" },\
		{ "KEY_E", KEY_E, KeyboardKey, "E" },\
		{ "KEY_F", KEY_F, KeyboardKey, "F" },\
		{ "KEY_G", KEY_G, KeyboardKey, "G" },\
		{ "KEY_H", KEY_H, KeyboardKey, "H" },\
		{ "KEY_I", KEY_I, KeyboardKey, "I" },\
		{ "KEY_J", KEY_J, KeyboardKey, "J" },\
		{ "KEY_K", KEY_K, KeyboardKey, "K" },\
		{ "KEY_L", KEY_L, KeyboardKey, "L" },\
		{ "KEY_M", KEY_M, KeyboardKey, "M" },\
		{ "KEY_N", KEY_N, KeyboardKey, "N" },\
		{ "KEY_O", KEY_O, KeyboardKey, "O" },\
		{ "KEY_P", KEY_P, KeyboardKey, "P" },\
		{ "KEY_Q", KEY_Q, KeyboardKey, "Q" },\
		{ "KEY_R", KEY_R, KeyboardKey, "R" },\
		{ "KEY_S", KEY_S, KeyboardKey, "S" },\
		{ "KEY_T", KEY_T, KeyboardKey, "T" },\
		{ "KEY_U", KEY_U, KeyboardKey, "U" },\
		{ "KEY_V", KEY_V, KeyboardKey, "V" },\
		{ "KEY_W", KEY_W, KeyboardKey, "W" },\
		{ "KEY_X", KEY_X, KeyboardKey, "X" }, \
		{ "KEY_Y", KEY_Y, KeyboardKey, "Y" },\
		{ "KEY_Z", KEY_Z, KeyboardKey, "Z" },\
		{ "KEY_F1", KEY_F1, KeyboardKey, "F1" },\
		{ "KEY_F2", KEY_F2, KeyboardKey, "F2" },\
		{ "KEY_F3", KEY_F3, KeyboardKey, "F3" },\
		{ "KEY_F4", KEY_F4, KeyboardKey, "F4" },\
		{ "KEY_F5", KEY_F5, KeyboardKey, "F5" },\
		{ "KEY_F6", KEY_F6, KeyboardKey, "F6" },\
		{ "KEY_F7", KEY_F7, KeyboardKey, "F7" },\
		{ "KEY_F8", KEY_F8, KeyboardKey, "F8" },\
		{ "KEY_F9", KEY_F9, KeyboardKey, "F9" },\
		{ "KEY_F10", KEY_F10, KeyboardKey, "F10" },\
		{ "KEY_F11", KEY_F11, KeyboardKey, "F11" },\
		{ "KEY_F12", KEY_F12, KeyboardKey, "F12" },\
		{ "KEY_F13", KEY_F13, KeyboardKey, "F13" },\
		{ "KEY_F14", KEY_F14, KeyboardKey, "F14" },\
		{ "KEY_F15", KEY_F15, KeyboardKey, "F15" },\
		{ "KEY_F16", KEY_F16, KeyboardKey, "F16" },\
		{ "KEY_F17", KEY_F17, KeyboardKey, "F17" },\
		{ "KEY_F18", KEY_F18, KeyboardKey, "F18" },\
		{ "KEY_F19", KEY_F19, KeyboardKey, "F19" },\
		{ "KEY_F20", KEY_F20, KeyboardKey, "F20" },\
		{ "KEY_F21", KEY_F21, KeyboardKey, "F21" },\
		{ "KEY_F22", KEY_F22, KeyboardKey, "F22" },\
		{ "KEY_F23", KEY_F23, KeyboardKey, "F23" },\
		{ "KEY_F24", KEY_F24, KeyboardKey, "F24" },\
		{ "KEY_KP0", KEY_KP0, KeyboardNumpadKey, "Keypad 0" },\
		{ "KEY_KP1", KEY_KP1, KeyboardNumpadKey, "Keypad 1" },\
		{ "KEY_KP2", KEY_KP2, KeyboardNumpadKey, "Keypad 2" },\
		{ "KEY_KP3", KEY_KP3, KeyboardNumpadKey, "Keypad 3" },\
		{ "KEY_KP4", KEY_KP4, KeyboardNumpadKey, "Keypad 4" },\
		{ "KEY_KP5", KEY_KP5, KeyboardNumpadKey, "Keypad 5" },\
		{ "KEY_KP6", KEY_KP6, KeyboardNumpadKey, "Keypad 6" },\
		{ "KEY_KP7", KEY_KP7, KeyboardNumpadKey, "Keypad 7" },\
		{ "KEY_KP8", KEY_KP8, KeyboardNumpadKey, "Keypad 8" },\
		{ "KEY_KP9", KEY_KP9, KeyboardNumpadKey, "Keypad 9" },\
		{ "KEY_KPMINUS", KEY_KPMINUS, KeyboardNumpadKey, "Keypad -" },\
		{ "KEY_KPPLUS", KEY_KPPLUS, KeyboardNumpadKey, "Keypad  +" },\
		{ "KEY_KPSLASH", KEY_KPSLASH, KeyboardNumpadKey, "Keypad /" }, \
		{ "KEY_KPASTERISK", KEY_KPASTERISK, KeyboardNumpadKey, "Keypad *" },\
		{ "KEY_KPDOT", KEY_KPDOT, KeyboardNumpadKey, "Keypad ." },\
		{ "KEY_KPEQUAL", KEY_KPEQUAL, KeyboardNumpadKey, "Keypad =" },\
		{ "KEY_KPCOMMA", KEY_KPCOMMA, KeyboardNumpadKey, "Keypad ," }, \
		{ "KEY_KPLEFTPAREN", KEY_KPLEFTPAREN, KeyboardNumpadKey, "Keypad (" },\
		{ "KEY_KPRIGHTPAREN", KEY_KPRIGHTPAREN, KeyboardNumpadKey, "Keypad )" },\
		{ "KEY_KPENTER", KEY_KPENTER, KeyboardNumpadKey, "Keypad Enter" }, \
		{ "KEY_ESC", KEY_ESC, KeyboardKey, "Escape" },\
		{ "KEY_GRAVE", KEY_GRAVE, KeyboardKey, "`" },\
		{ "KEY_MINUS", KEY_MINUS, KeyboardKey, "-" },\
		{ "KEY_EQUAL", KEY_EQUAL, KeyboardKey, "=" },\
		{ "KEY_BACKSPACE", KEY_BACKSPACE, KeyboardKey, "Backspace" },\
		{ "KEY_TAB", KEY_TAB, KeyboardKey, "Tab" },\
		{ "KEY_LEFTBRACE", KEY_LEFTBRACE, KeyboardKey, "[" },\
		{ "KEY_RIGHTBRACE", KEY_RIGHTBRACE, KeyboardKey, "]" },\
		{ "KEY_BACKSLASH", KEY_BACKSLASH, KeyboardKey, "\\" },\
		{ "KEY_CAPSLOCK", KEY_CAPSLOCK, KeyboardKey, "Capslock" },\
		{ "KEY_SEMICOLON", KEY_SEMICOLON, KeyboardKey, ";" },\
		{ "KEY_APOSTROPHE", KEY_APOSTROPHE, KeyboardKey, "'" },\
		{ "KEY_ENTER", KEY_ENTER, KeyboardKey, "Enter" },\
		{ "KEY_LEFTSHIFT", KEY_LEFTSHIFT, KeyboardKey, "Left Shift" },\
		{ "KEY_COMMA", KEY_COMMA, KeyboardKey, "," },\
		{ "KEY_DOT", KEY_DOT, KeyboardKey, "." },\
		{ "KEY_SLASH", KEY_SLASH, KeyboardKey, "/" },\
		{ "KEY_RIGHTSHIFT", KEY_RIGHTSHIFT, KeyboardKey, "Right Shift" },\
		{ "KEY_LEFTCTRL", KEY_LEFTCTRL, KeyboardKey, "Left Ctrl" },\
		{ "KEY_LEFTMETA", KEY_LEFTMETA, KeyboardKey, "Left Meta" },\
		{ "KEY_LEFTALT", KEY_LEFTALT, KeyboardKey, "Left Alt" },\
		{ "KEY_SPACE", KEY_SPACE, KeyboardKey, "Space" },\
		{ "KEY_RIGHTALT", KEY_RIGHTALT, KeyboardKey, "Right Alt" }, \
		{ "KEY_RIGHTMETA", KEY_RIGHTMETA, KeyboardKey, "Right Meta" },\
		{ "KEY_RIGHTCTRL", KEY_RIGHTCTRL, KeyboardKey, "Right Ctrl" }, \
		{ "KEY_INSERT", KEY_INSERT, KeyboardKey, "Insert" }, \
		{ "KEY_DELETE", KEY_DELETE, KeyboardKey, "Delete" }, \
		{ "KEY_HOME", KEY_HOME, KeyboardKey, "Home" }, \
		{ "KEY_END", KEY_END, KeyboardKey, "End" }, \
		{ "KEY_PAGEUP", KEY_PAGEUP, KeyboardKey, "PgUp" }, \
		{ "KEY_PAGEDOWN", KEY_PAGEDOWN, KeyboardKey, "PgDn" }, \
		{ "KEY_UP", KEY_UP, KeyboardKey, "Up Arrow" }, \
		{ "KEY_LEFT", KEY_LEFT, KeyboardKey, "Left Arrow" }, \
		{ "KEY_RIGHT", KEY_RIGHT, KeyboardKey, "Right Arrow" }, \
		{ "KEY_DOWN", KEY_DOWN, KeyboardKey, "Down Arrow" }, \
		{ "KEY_NUMLOCK", KEY_NUMLOCK, KeyboardKey, "Numlock" },\
		{ "KEY_SCROLLLOCK", KEY_SCROLLLOCK, KeyboardKey, "Scroll Lock" }, \
		{ "KEY_SYSRQ", KEY_SYSRQ, KeyboardKey, "SysRq" }, \
		{ "KEY_MUTE", KEY_MUTE, KeyboardKey, "Mute" },\
		{ "KEY_VOLUMEDOWN", KEY_VOLUMEDOWN, KeyboardKey, "Vol Down" },\
		{ "KEY_VOLUMEUP", KEY_VOLUMEUP, KeyboardKey, "Vol Up" },\
		{ "KEY_POWER", KEY_POWER, KeyboardKey, "Power" },\
		{ "KEY_PAUSE", KEY_PAUSE, KeyboardKey, "Pause" },\
		{ "KEY_COMPOSE", KEY_COMPOSE, KeyboardKey, "Compose" },\
		{ "KEY_STOP", KEY_STOP, KeyboardKey, "Stop" },\
		{ "KEY_AGAIN", KEY_AGAIN, KeyboardKey },\
		{ "KEY_PROPS", KEY_PROPS, KeyboardKey },\
		{ "KEY_UNDO", KEY_UNDO, KeyboardKey, "Undo" },\
		{ "KEY_FRONT", KEY_FRONT, KeyboardKey },\
		{ "KEY_COPY", KEY_COPY, KeyboardKey, "Copy" },\
		{ "KEY_OPEN", KEY_OPEN, KeyboardKey, "Open" },\
		{ "KEY_PASTE", KEY_PASTE, KeyboardKey, "Paste" },\
		{ "KEY_FIND", KEY_FIND, KeyboardKey, "Find" },\
		{ "KEY_CUT", KEY_CUT, KeyboardKey, "Cut" },\
		{ "KEY_HELP", KEY_HELP, KeyboardKey, "Help" },\
		{ "KEY_CALC", KEY_CALC, KeyboardKey, "Calc" },\
		{ "KEY_SLEEP", KEY_SLEEP, KeyboardKey, "Sleep" },\
		{ "KEY_WWW", KEY_WWW, KeyboardKey, "WWW" },\
		{ "KEY_COFFEE", KEY_COFFEE, KeyboardKey },\
		{ "KEY_BACK", KEY_BACK, KeyboardKey, "Back" },\
		{ "KEY_FORWARD", KEY_FORWARD, KeyboardKey, "Forward" },\
		{ "KEY_EJECTCD", KEY_EJECTCD, KeyboardKey, "Eject" },\
		{ "KEY_NEXTSONG", KEY_NEXTSONG, KeyboardKey, "Next" },\
		{ "KEY_PLAYPAUSE", KEY_PLAYPAUSE, KeyboardKey, "Play/Pause" },\
		{ "KEY_PREVIOUSSONG", KEY_PREVIOUSSONG, KeyboardKey, "Prev" },\
		{ "KEY_STOPCD", KEY_STOPCD, KeyboardKey },\
		{ "KEY_REFRESH", KEY_REFRESH, KeyboardKey, "Refresh" },\
		{ "KEY_EDIT", KEY_EDIT, KeyboardKey, "Edit" },\
		{ "KEY_SCROLLUP", KEY_SCROLLUP, KeyboardKey },\
		{ "KEY_SCROLLDOWN", KEY_SCROLLDOWN, KeyboardKey },\
		{ "KEY_WAKEUP", KEY_WAKEUP, KeyboardKey, "Wakeup" },\
		{ "KEY_FILE", KEY_FILE, KeyboardKey, "File" },\
		{ "KEY_MAIL", KEY_MAIL, KeyboardKey, "Mail" },\
		{ "KEY_BOOKMARKS", KEY_BOOKMARKS, KeyboardKey, "Bookmarks" },\
		{ "KEY_CONFIG", KEY_CONFIG, KeyboardKey, "Config" },\
		{ "KEY_HOMEPAGE", KEY_HOMEPAGE, KeyboardKey, "Homepage" },\
		{ "KEY_SEARCH", KEY_SEARCH, KeyboardKey, "Search" },\
		{ "KEY_WORDPROCESSOR", KEY_WORDPROCESSOR, KeyboardKey },\
		{ "KEY_SPREADSHEET", KEY_SPREADSHEET, KeyboardKey },\
		{ "KEY_PRESENTATION", KEY_PRESENTATION, KeyboardKey },\
		{ "KEY_KPJPCOMMA", KEY_KPJPCOMMA, KeyboardMiscKey }, \
		{ "KEY_ZENKAKUHANKAKU", KEY_ZENKAKUHANKAKU, KeyboardMiscKey }, \
		{ "KEY_102ND", KEY_102ND, KeyboardMiscKey }, \
		{ "KEY_RO", KEY_RO, KeyboardMiscKey }, \
		{ "KEY_KATAKANA", KEY_KATAKANA, KeyboardMiscKey }, \
		{ "KEY_HIRAGANA", KEY_HIRAGANA, KeyboardMiscKey }, \
		{ "KEY_HENKAN", KEY_HENKAN, KeyboardMiscKey }, \
		{ "KEY_KATAKANAHIRAGANA", KEY_KATAKANAHIRAGANA, KeyboardMiscKey }, \
		{ "KEY_MUHENKAN", KEY_MUHENKAN, KeyboardMiscKey }, \
		{ "KEY_HANGEUL", KEY_HANGEUL, KeyboardMiscKey }, \
		{ "KEY_HANJA", KEY_HANJA, KeyboardMiscKey }, \
		{ "KEY_YEN", KEY_YEN, KeyboardMiscKey }, \
	}},\
	{ "EV_ABS", EV_ABS, "Absolute Axis", {\
		{ "ABS_X", ABS_X, AbsoluteAxis, "Left X Axis" },\
		{ "ABS_Y", ABS_Y, AbsoluteAxis, "Left Y Axis" },\
		{ "ABS_Z", ABS_Z, AbsoluteAxis, "Left Z Axis" },\
		{ "ABS_RX", ABS_RX, AbsoluteAxis, "Right X Axis" },\
		{ "ABS_RY", ABS_RY, AbsoluteAxis, "Right Y Axis" },\
		{ "ABS_RZ", ABS_RZ, AbsoluteAxis, "Right Z Axis" },\
		{ "ABS_HAT0X", ABS_HAT0X, AbsoluteAxis, "Hat 0 X" },\
		{ "ABS_HAT0Y", ABS_HAT0Y, AbsoluteAxis, "Hat 0 Y" },\
		{ "ABS_HAT1X", ABS_HAT1X, AbsoluteAxis, "Hat 1 X" },\
		{ "ABS_HAT1Y", ABS_HAT1Y, AbsoluteAxis, "Hat 1 Y" },\
		{ "ABS_HAT2X", ABS_HAT2X, AbsoluteAxis, "Hat 2 X" },\
		{ "ABS_HAT2Y", ABS_HAT2Y, AbsoluteAxis, "Hat 2 Y" },\
		{ "ABS_HAT3X", ABS_HAT3X, AbsoluteAxis, "Hat 3 X" },\
		{ "ABS_HAT3Y", ABS_HAT3Y, AbsoluteAxis, "Hat 3 Y" },\
		{ "ABS_THROTTLE", ABS_THROTTLE, AbsoluteAxis, "Throttle" },\
		{ "ABS_RUDDER", ABS_RUDDER, AbsoluteAxis, "Rudder" },\
		{ "ABS_WHEEL", ABS_WHEEL, AbsoluteAxis, "Wheel" },\
		{ "ABS_GAS", ABS_GAS, AbsoluteAxis, "Gas" },\
		{ "ABS_BRAKE", ABS_BRAKE, AbsoluteAxis, "Brake" },\
	}},\
	{ "EV_REL", EV_REL, "Relative Axis", {\
		{ "REL_X", REL_X, RelativeAxis, "Left X Axis" },\
		{ "REL_Y", REL_Y, RelativeAxis, "Left Y Axis"},\
		{ "REL_Z", REL_Z, RelativeAxis, "Left Z Axis" },\
		{ "REL_RX", REL_RX, RelativeAxis, "Right X Axis" },\
		{ "REL_RY", REL_RY, RelativeAxis, "Right Y Axis" },\
		{ "REL_RZ", REL_RZ, RelativeAxis, "Right Z Axis" },\
		{ "REL_WHEEL", REL_WHEEL, RelativeAxis, "Vertical Wheel" },\
		{ "REL_HWHEEL", REL_HWHEEL, RelativeAxis, "Horizontal Wheel" },\
		{ "REL_DIAL", REL_DIAL, RelativeAxis, "Dial" },\
		{ "REL_MISC", REL_MISC, RelativeAxis, "Misc" },\
	}},


#if !defined(EV_ABS)
#define EV_ABS 1
#define EV_KEY 2
#define EV_REL 3

/* Mouse */
#define BTN_LEFT 1
#define BTN_RIGHT 2
#define BTN_MIDDLE 3
#define BTN_SIDE 4
#define BTN_EXTRA 5
#define BTN_FORWARD 6
#define BTN_BACK 7
#define BTN_TASK 8

/* Gamepad */
#define BTN_SOUTH 50
#define BTN_EAST 51
#define BTN_C 52
#define BTN_NORTH 53
#define BTN_WEST 54
#define BTN_Z 55
#define BTN_TL 56
#define BTN_TR 57
#define BTN_TL2 58
#define BTN_TR2 59
#define BTN_SELECT 60
#define BTN_START 61
#define BTN_MODE 62
#define BTN_THUMBL 63
#define BTN_THUMBR 64
#define BTN_DPAD_UP 65
#define BTN_DPAD_DOWN 66
#define BTN_DPAD_LEFT 67
#define BTN_DPAD_RIGHT 68

/* Keyboard */
#define KEY_ESC 100
#define KEY_1 101
#define KEY_2 102
#define KEY_3 103
#define KEY_4 104
#define KEY_5 105
#define KEY_6 106
#define KEY_7 107
#define KEY_8 108
#define KEY_9 109
#define KEY_0 110
#define KEY_MINUS 111
#define KEY_EQUAL 112
#define KEY_BACKSPACE 113
#define KEY_TAB 114
#define KEY_Q 115
#define KEY_W 116
#define KEY_E 117
#define KEY_R 118
#define KEY_T 119
#define KEY_Y 120
#define KEY_U 121
#define KEY_I 122
#define KEY_O 123
#define KEY_P 124
#define KEY_LEFTBRACE 125
#define KEY_RIGHTBRACE 126
#define KEY_ENTER 127
#define KEY_LEFTCTRL 128
#define KEY_A 129
#define KEY_S 130
#define KEY_D 131
#define KEY_F 132
#define KEY_G 133
#define KEY_H 134
#define KEY_J 135
#define KEY_K 136
#define KEY_L 137
#define KEY_SEMICOLON 138
#define KEY_APOSTROPHE 139
#define KEY_GRAVE 140
#define KEY_LEFTSHIFT 141
#define KEY_BACKSLASH 142
#define KEY_Z 143
#define KEY_X 144
#define KEY_C 145
#define KEY_V 146
#define KEY_B 147
#define KEY_N 148
#define KEY_M 149
#define KEY_COMMA 150
#define KEY_DOT 151
#define KEY_SLASH 152
#define KEY_RIGHTSHIFT 153
#define KEY_KPASTERISK 154
#define KEY_LEFTALT 155
#define KEY_SPACE 156
#define KEY_CAPSLOCK 157
#define KEY_F1 158
#define KEY_F2 159
#define KEY_F3 160
#define KEY_F4 161
#define KEY_F5 162
#define KEY_F6 163
#define KEY_F7 164
#define KEY_F8 165
#define KEY_F9 166
#define KEY_F10 167
#define KEY_NUMLOCK 168
#define KEY_SCROLLLOCK 169
#define KEY_KP7 170
#define KEY_KP8 171
#define KEY_KP9 172
#define KEY_KPMINUS 173
#define KEY_KP4 174
#define KEY_KP5 175
#define KEY_KP6 176
#define KEY_KPPLUS 177
#define KEY_KP1 178
#define KEY_KP2 179
#define KEY_KP3 180
#define KEY_KP0 181
#define KEY_KPDOT 182
#define KEY_ZENKAKUHANKAKU 183
#define KEY_102ND 184
#define KEY_F11 185
#define KEY_F12 186
#define KEY_RO 187
#define KEY_KATAKANA 188
#define KEY_HIRAGANA 189
#define KEY_HENKAN 190
#define KEY_KATAKANAHIRAGANA 191
#define KEY_MUHENKAN 192
#define KEY_KPJPCOMMA 193
#define KEY_KPENTER 194
#define KEY_RIGHTCTRL 195
#define KEY_KPSLASH 196
#define KEY_SYSRQ 197
#define KEY_RIGHTALT 198
#define KEY_HOME 199
#define KEY_UP 200
#define KEY_PAGEUP 201
#define KEY_LEFT 202
#define KEY_RIGHT 203
#define KEY_END 204
#define KEY_DOWN 205
#define KEY_PAGEDOWN 206
#define KEY_INSERT 207
#define KEY_DELETE 208
#define KEY_MUTE 209
#define KEY_VOLUMEDOWN 210
#define KEY_VOLUMEUP 211
#define KEY_POWER 212
#define KEY_KPEQUAL 213
#define KEY_PAUSE 214
#define KEY_KPCOMMA 215
#define KEY_HANGEUL 216
#define KEY_HANJA 217
#define KEY_YEN 218
#define KEY_LEFTMETA 219
#define KEY_RIGHTMETA 220
#define KEY_COMPOSE 221
#define KEY_STOP 222
#define KEY_AGAIN 223
#define KEY_PROPS 224
#define KEY_UNDO 225
#define KEY_FRONT 226
#define KEY_COPY 227
#define KEY_OPEN 228
#define KEY_PASTE 229
#define KEY_FIND 230
#define KEY_CUT 231
#define KEY_HELP 232
#define KEY_CALC 233
#define KEY_SLEEP 234
#define KEY_WWW 235
#define KEY_COFFEE 236
#define KEY_BACK 237
#define KEY_FORWARD 238
#define KEY_EJECTCD 239
#define KEY_NEXTSONG 240
#define KEY_PLAYPAUSE 241
#define KEY_PREVIOUSSONG 242
#define KEY_STOPCD 243
#define KEY_REFRESH 244
#define KEY_EDIT 245
#define KEY_SCROLLUP 246
#define KEY_SCROLLDOWN 247
#define KEY_KPLEFTPAREN 248
#define KEY_KPRIGHTPAREN 249
#define KEY_F13 250
#define KEY_F14 251
#define KEY_F15 252
#define KEY_F16 253
#define KEY_F17 253
#define KEY_F18 254
#define KEY_F19 255
#define KEY_F20 256
#define KEY_F21 257
#define KEY_F22 258
#define KEY_F23 259
#define KEY_F24 260
#define KEY_WAKEUP 261
#define KEY_FILE 262
#define KEY_MAIL 263
#define KEY_BOOKMARKS 264
#define KEY_CONFIG 265
#define KEY_HOMEPAGE 266
#define KEY_SEARCH 267
#define KEY_WORDPROCESSOR 268
#define KEY_SPREADSHEET 269
#define KEY_PRESENTATION 270

/* Axes */
#define ABS_X 1
#define ABS_Y 2
#define ABS_Z 3
#define ABS_RX 4
#define ABS_RY 5
#define ABS_RZ 6
#define ABS_THROTTLE 7
#define ABS_RUDDER 8
#define ABS_WHEEL 9
#define ABS_GAS 10

/* Hats */
#define ABS_BRAKE 11
#define ABS_HAT0X 12
#define ABS_HAT0Y 13
#define ABS_HAT1X 14
#define ABS_HAT1Y 15
#define ABS_HAT2X 16
#define ABS_HAT2Y 17
#define ABS_HAT3X 18
#define ABS_HAT3Y 19

/* Relative axes */
#define REL_X 1
#define REL_Y 2
#define REL_Z 3
#define REL_RX 4
#define REL_RY 5
#define REL_RZ 6
#define REL_HWHEEL 7
#define REL_DIAL 8
#define REL_WHEEL 9
#define REL_MISC 10

#endif
