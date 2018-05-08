/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#define CODETABLE \
	{ "EV_KEY", EV_KEY, "Button", {\
		{ "BTN_SOUTH", BTN_SOUTH, "Button South (A)" },\
		{ "BTN_EAST", BTN_EAST, "Button East (B)" },\
		{ "BTN_C", BTN_C, "Button C" },\
		{ "BTN_NORTH", BTN_NORTH, "Button North (X)" },\
		{ "BTN_WEST", BTN_WEST, "Button West (Y)" },\
		{ "BTN_Z", BTN_Z, "Button Z" },\
		{ "BTN_TL", BTN_TL, "Button L1" },\
		{ "BTN_TR", BTN_TR, "Button R1" },\
		{ "BTN_TL2", BTN_TL2, "Button L2 (digital)" },\
		{ "BTN_TR2", BTN_TR2, "Button R2 (digital)" },\
		{ "BTN_SELECT", BTN_SELECT, "Button Select" },\
		{ "BTN_START", BTN_START, "Button Start" },\
		{ "BTN_MODE", BTN_MODE, "Button Menu" },\
		{ "BTN_THUMBL", BTN_THUMBL, "Button Thumb Left" },\
		{ "BTN_THUMBR", BTN_THUMBR, "Button Thumb Right" },\
		{ "BTN_DPAD_UP", BTN_DPAD_UP, "D-pad Up" },\
		{ "BTN_DPAD_DOWN", BTN_DPAD_DOWN, "D-pad Down" },\
		{ "BTN_DPAD_LEFT", BTN_DPAD_LEFT, "D-pad Left" },\
		{ "BTN_DPAD_RIGHT", BTN_DPAD_RIGHT, "D-pad Right" },\
		{ "BTN_LEFT", BTN_LEFT, "Mouse Left" },\
		{ "BTN_RIGHT", BTN_RIGHT, "Mouse Right" },\
		{ "BTN_MIDDLE", BTN_MIDDLE, "Mouse Middle" },\
		{ "BTN_SIDE", BTN_SIDE, "Mouse 4" },\
		{ "BTN_EXTRA", BTN_EXTRA, "Mouse 5" },\
		{ "BTN_FORWARD", BTN_FORWARD, "Mouse Forward" },\
		{ "BTN_BACK", BTN_BACK, "Mouse Back" },\
		{ "BTN_TASK", BTN_TASK, "Mouse Task" },\
		{ "KEY_F1", KEY_F1, "F1" },\
		{ "KEY_F2", KEY_F2, "F2" },\
		{ "KEY_F3", KEY_F3, "F3" },\
		{ "KEY_F4", KEY_F4, "F4" },\
		{ "KEY_F5", KEY_F5, "F5" },\
		{ "KEY_F6", KEY_F6, "F6" },\
		{ "KEY_F7", KEY_F7, "F7" },\
		{ "KEY_F8", KEY_F8, "F8" },\
		{ "KEY_F9", KEY_F9, "F9" },\
		{ "KEY_F10", KEY_F10, "F10" },\
		{ "KEY_F11", KEY_F11, "F11" },\
		{ "KEY_F12", KEY_F12, "F12" },\
		{ "KEY_0", KEY_0, "0" },\
		{ "KEY_1", KEY_1, "1" },\
		{ "KEY_2", KEY_2, "2" },\
		{ "KEY_3", KEY_3, "3" },\
		{ "KEY_4", KEY_4, "4" },\
		{ "KEY_5", KEY_5, "5" },\
		{ "KEY_6", KEY_6, "6" },\
		{ "KEY_7", KEY_7, "7" },\
		{ "KEY_8", KEY_8, "8" },\
		{ "KEY_9", KEY_9, "9" },\
		{ "KEY_KP0", KEY_KP0, "Keypad 0" },\
		{ "KEY_KP1", KEY_KP1, "Keypad 1" },\
		{ "KEY_KP2", KEY_KP2, "Keypad 2" },\
		{ "KEY_KP3", KEY_KP3, "Keypad 3" },\
		{ "KEY_KP4", KEY_KP4, "Keypad 4" },\
		{ "KEY_KP5", KEY_KP5, "Keypad 5" },\
		{ "KEY_KP6", KEY_KP6, "Keypad 6" },\
		{ "KEY_KP7", KEY_KP7, "Keypad 7" },\
		{ "KEY_KP8", KEY_KP8, "Keypad 8" },\
		{ "KEY_KP9", KEY_KP9, "Keypad 9" },\
		{ "KEY_KPMINUS", KEY_KPMINUS, "Keypad -" },\
		{ "KEY_KPPLUS", KEY_KPPLUS, "Keypad  +" },\
		{ "KEY_KPSLASH", KEY_KPSLASH, "Keypad /" }, \
		{ "KEY_KPASTERISK", KEY_KPASTERISK, "Keypad *" },\
		{ "KEY_KPDOT", KEY_KPDOT, "Keypad ." },\
		{ "KEY_KPEQUAL", KEY_KPEQUAL, "Keypad =" },\
		{ "KEY_KPCOMMA", KEY_KPCOMMA, "Keypad ," }, \
		{ "KEY_KPLEFTPAREN", KEY_KPLEFTPAREN, "Keypad (" },\
		{ "KEY_KPRIGHTPAREN", KEY_KPRIGHTPAREN, "Keypad )" },\
		{ "KEY_KPENTER", KEY_KPENTER, "Keypad Enter" }, \
		{ "KEY_A", KEY_A, "A" },\
		{ "KEY_B", KEY_B, "B" },\
		{ "KEY_C", KEY_C, "C" },\
		{ "KEY_D", KEY_D, "D" },\
		{ "KEY_E", KEY_E, "E" },\
		{ "KEY_F", KEY_F, "F" },\
		{ "KEY_G", KEY_G, "G" },\
		{ "KEY_H", KEY_H, "H" },\
		{ "KEY_I", KEY_I, "I" },\
		{ "KEY_J", KEY_J, "J" },\
		{ "KEY_K", KEY_K, "K" },\
		{ "KEY_L", KEY_L, "L" },\
		{ "KEY_M", KEY_M, "M" },\
		{ "KEY_N", KEY_N, "N" },\
		{ "KEY_O", KEY_O, "O" },\
		{ "KEY_P", KEY_P, "P" },\
		{ "KEY_Q", KEY_Q, "Q" },\
		{ "KEY_R", KEY_R, "R" },\
		{ "KEY_S", KEY_S, "S" },\
		{ "KEY_T", KEY_T, "T" },\
		{ "KEY_U", KEY_U, "U" },\
		{ "KEY_V", KEY_V, "V" },\
		{ "KEY_W", KEY_W, "W" },\
		{ "KEY_X", KEY_X, "X" }, \
		{ "KEY_Y", KEY_Y, "Y" },\
		{ "KEY_Z", KEY_Z, "Z" },\
		{ "KEY_ESC", KEY_ESC, "Escape" },\
		{ "KEY_GRAVE", KEY_GRAVE, "`" },\
		{ "KEY_MINUS", KEY_MINUS, "-" },\
		{ "KEY_EQUAL", KEY_EQUAL, "=" },\
		{ "KEY_BACKSPACE", KEY_BACKSPACE, "Backspace" },\
		{ "KEY_TAB", KEY_TAB, "Tab" },\
		{ "KEY_LEFTBRACE", KEY_LEFTBRACE, "[" },\
		{ "KEY_RIGHTBRACE", KEY_RIGHTBRACE, "]" },\
		{ "KEY_BACKSLASH", KEY_BACKSLASH, "\\" },\
		{ "KEY_CAPSLOCK", KEY_CAPSLOCK, "Capslock" },\
		{ "KEY_SEMICOLON", KEY_SEMICOLON, ";" },\
		{ "KEY_APOSTROPHE", KEY_APOSTROPHE, "'" },\
		{ "KEY_ENTER", KEY_ENTER, "Enter" },\
		{ "KEY_LEFTSHIFT", KEY_LEFTSHIFT, "Left Shift" },\
		{ "KEY_COMMA", KEY_COMMA, "," },\
		{ "KEY_DOT", KEY_DOT, "." },\
		{ "KEY_SLASH", KEY_SLASH, "/" },\
		{ "KEY_RIGHTSHIFT", KEY_RIGHTSHIFT, "Right Shift" },\
		{ "KEY_LEFTCTRL", KEY_LEFTCTRL, "Left Ctrl" },\
		{ "KEY_LEFTMETA", KEY_LEFTMETA, "Left Meta" },\
		{ "KEY_LEFTALT", KEY_LEFTALT, "Left Alt" },\
		{ "KEY_SPACE", KEY_SPACE, "Space" },\
		{ "KEY_RIGHTALT", KEY_RIGHTALT, "Right Alt" }, \
		{ "KEY_RIGHTMETA", KEY_RIGHTMETA, "Right Meta" },\
		{ "KEY_RIGHTCTRL", KEY_RIGHTCTRL, "Right Ctrl" }, \
		{ "KEY_INSERT", KEY_INSERT, "Insert" }, \
		{ "KEY_DELETE", KEY_DELETE, "Delete" }, \
		{ "KEY_HOME", KEY_HOME, "Home" }, \
		{ "KEY_END", KEY_END, "End" }, \
		{ "KEY_PAGEUP", KEY_PAGEUP, "PgUp" }, \
		{ "KEY_PAGEDOWN", KEY_PAGEDOWN, "PgDn" }, \
		{ "KEY_UP", KEY_UP, "Up Arrow" }, \
		{ "KEY_LEFT", KEY_LEFT, "Left Arrow" }, \
		{ "KEY_RIGHT", KEY_RIGHT, "Right Arrow" }, \
		{ "KEY_DOWN", KEY_DOWN, "Down Arrow" }, \
		{ "KEY_NUMLOCK", KEY_NUMLOCK, "Numlock" },\
		{ "KEY_SCROLLLOCK", KEY_SCROLLLOCK, "Scroll Lock" }, \
		{ "KEY_SYSRQ", KEY_SYSRQ, "SysRq" }, \
		{ "KEY_MUTE", KEY_MUTE, "Mute" },\
		{ "KEY_VOLUMEDOWN", KEY_VOLUMEDOWN, "Vol Down" },\
		{ "KEY_VOLUMEUP", KEY_VOLUMEUP, "Vol Up" },\
		{ "KEY_POWER", KEY_POWER, "Power" },\
		{ "KEY_PAUSE", KEY_PAUSE, "Pause" },\
		{ "KEY_COMPOSE", KEY_COMPOSE, "Compose" },\
		{ "KEY_STOP", KEY_STOP, "Stop" },\
		{ "KEY_AGAIN", KEY_AGAIN },\
		{ "KEY_PROPS", KEY_PROPS },\
		{ "KEY_UNDO", KEY_UNDO, "Undo" },\
		{ "KEY_FRONT", KEY_FRONT },\
		{ "KEY_COPY", KEY_COPY, "Copy" },\
		{ "KEY_OPEN", KEY_OPEN, "Open" },\
		{ "KEY_PASTE", KEY_PASTE, "Paste" },\
		{ "KEY_FIND", KEY_FIND, "Find" },\
		{ "KEY_CUT", KEY_CUT, "Cut" },\
		{ "KEY_HELP", KEY_HELP, "Help" },\
		{ "KEY_CALC", KEY_CALC, "Calc" },\
		{ "KEY_SLEEP", KEY_SLEEP, "Sleep" },\
		{ "KEY_WWW", KEY_WWW, "WWW" },\
		{ "KEY_COFFEE", KEY_COFFEE },\
		{ "KEY_BACK", KEY_BACK, "Back" },\
		{ "KEY_FORWARD", KEY_FORWARD, "Forward" },\
		{ "KEY_EJECTCD", KEY_EJECTCD, "Eject" },\
		{ "KEY_NEXTSONG", KEY_NEXTSONG, "Next" },\
		{ "KEY_PLAYPAUSE", KEY_PLAYPAUSE, "Play/Pause" },\
		{ "KEY_PREVIOUSSONG", KEY_PREVIOUSSONG, "Prev" },\
		{ "KEY_STOPCD", KEY_STOPCD },\
		{ "KEY_REFRESH", KEY_REFRESH, "Refresh" },\
		{ "KEY_EDIT", KEY_EDIT, "Edit" },\
		{ "KEY_SCROLLUP", KEY_SCROLLUP },\
		{ "KEY_SCROLLDOWN", KEY_SCROLLDOWN },\
		{ "KEY_F13", KEY_F13, "F13" },\
		{ "KEY_F14", KEY_F14, "F14" },\
		{ "KEY_F15", KEY_F15, "F15" },\
		{ "KEY_F16", KEY_F16, "F16" },\
		{ "KEY_F17", KEY_F17, "F17" },\
		{ "KEY_F18", KEY_F18, "F18" },\
		{ "KEY_F19", KEY_F19, "F19" },\
		{ "KEY_F20", KEY_F20, "F20" },\
		{ "KEY_F21", KEY_F21, "F21" },\
		{ "KEY_F22", KEY_F22, "F22" },\
		{ "KEY_F23", KEY_F23, "F23" },\
		{ "KEY_F24", KEY_F24, "F24" },\
		{ "KEY_WAKEUP", KEY_WAKEUP, "Wakeup" },\
		{ "KEY_FILE", KEY_FILE, "File" },\
		{ "KEY_MAIL", KEY_MAIL, "Mail" },\
		{ "KEY_BOOKMARKS", KEY_BOOKMARKS, "Bookmarks" },\
		{ "KEY_CONFIG", KEY_CONFIG, "Config" },\
		{ "KEY_HOMEPAGE", KEY_HOMEPAGE, "Homepage" },\
		{ "KEY_SEARCH", KEY_SEARCH, "Search" },\
		{ "KEY_WORDPROCESSOR", KEY_WORDPROCESSOR },\
		{ "KEY_SPREADSHEET", KEY_SPREADSHEET },\
		{ "KEY_PRESENTATION", KEY_PRESENTATION },\
		{ "KEY_KPJPCOMMA", KEY_KPJPCOMMA }, \
		{ "KEY_ZENKAKUHANKAKU", KEY_ZENKAKUHANKAKU }, \
		{ "KEY_102ND", KEY_102ND }, \
		{ "KEY_RO", KEY_RO }, \
		{ "KEY_KATAKANA", KEY_KATAKANA }, \
		{ "KEY_HIRAGANA", KEY_HIRAGANA }, \
		{ "KEY_HENKAN", KEY_HENKAN }, \
		{ "KEY_KATAKANAHIRAGANA", KEY_KATAKANAHIRAGANA }, \
		{ "KEY_MUHENKAN", KEY_MUHENKAN }, \
		{ "KEY_HANGEUL", KEY_HANGEUL }, \
		{ "KEY_HANJA", KEY_HANJA }, \
		{ "KEY_YEN", KEY_YEN }, \
	}},\
	{ "EV_ABS", EV_ABS, "Absolute Axis", {\
		{ "ABS_X", ABS_X, "Left X Axis" },\
		{ "ABS_Y", ABS_Y, "Left Y Axis" },\
		{ "ABS_Z", ABS_Z, "Left Z Axis" },\
		{ "ABS_RX", ABS_RX, "Right X Axis" },\
		{ "ABS_RY", ABS_RY, "Right Y Axis" },\
		{ "ABS_RZ", ABS_RZ, "Right Z Axis" },\
		{ "ABS_HAT0X", ABS_HAT0X, "Hat 0 X" },\
		{ "ABS_HAT0Y", ABS_HAT0Y, "Hat 0 Y" },\
		{ "ABS_HAT1X", ABS_HAT1X, "Hat 1 X" },\
		{ "ABS_HAT1Y", ABS_HAT1Y, "Hat 1 Y" },\
		{ "ABS_HAT2X", ABS_HAT2X, "Hat 2 X" },\
		{ "ABS_HAT2Y", ABS_HAT2Y, "Hat 2 Y" },\
		{ "ABS_HAT3X", ABS_HAT3X, "Hat 3 X" },\
		{ "ABS_HAT3Y", ABS_HAT3Y, "Hat 3 Y" },\
		{ "ABS_THROTTLE", ABS_THROTTLE, "Throttle" },\
		{ "ABS_RUDDER", ABS_RUDDER, "Rudder" },\
		{ "ABS_WHEEL", ABS_WHEEL, "Wheel" },\
		{ "ABS_GAS", ABS_GAS, "Gas" },\
		{ "ABS_BRAKE", ABS_BRAKE, "Brake" },\
	}},\
	{ "EV_REL", EV_REL, "Relative Axis", {\
		{ "REL_X", REL_X, "Left X Axis" },\
		{ "REL_Y", REL_Y, "Left Y Axis"},\
		{ "REL_Z", REL_Z, "Left Z Axis" },\
		{ "REL_RX", REL_RX, "Right X Axis" },\
		{ "REL_RY", REL_RY, "Right Y Axis" },\
		{ "REL_RZ", REL_RZ, "Right Z Axis" },\
		{ "REL_WHEEL", REL_WHEEL, "Vertical Wheel" },\
		{ "REL_HWHEEL", REL_HWHEEL, "Horizontal Wheel" },\
		{ "REL_DIAL", REL_DIAL, "Dial" },\
		{ "REL_MISC", REL_MISC, "Misc" },\
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
