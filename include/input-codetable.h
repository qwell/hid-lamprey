/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#define CODETABLE \
	{ "EV_KEY", EV_KEY, {\
		{ "BTN_LEFT", BTN_LEFT },\
		{ "BTN_RIGHT", BTN_RIGHT },\
		{ "BTN_MIDDLE", BTN_MIDDLE },\
		{ "BTN_SIDE", BTN_SIDE },\
		{ "BTN_EXTRA", BTN_EXTRA },\
		{ "BTN_FORWARD", BTN_FORWARD },\
		{ "BTN_BACK", BTN_BACK },\
		{ "BTN_TASK", BTN_TASK },\
		{ "BTN_SOUTH", BTN_SOUTH },\
		{ "BTN_A", BTN_A },\
		{ "BTN_EAST", BTN_EAST },\
		{ "BTN_B", BTN_B },\
		{ "BTN_C", BTN_C },\
		{ "BTN_NORTH", BTN_NORTH },\
		{ "BTN_X", BTN_X },\
		{ "BTN_WEST", BTN_WEST },\
		{ "BTN_Y", BTN_Y },\
		{ "BTN_Z", BTN_Z },\
		{ "BTN_TL", BTN_TL },\
		{ "BTN_TR", BTN_TR },\
		{ "BTN_TL2", BTN_TL2 },\
		{ "BTN_TR2", BTN_TR2 },\
		{ "BTN_SELECT", BTN_SELECT },\
		{ "BTN_START", BTN_START },\
		{ "BTN_MODE", BTN_MODE },\
		{ "BTN_THUMBL", BTN_THUMBL },\
		{ "BTN_THUMBR", BTN_THUMBR },\
		{ "BTN_DPAD_UP", BTN_DPAD_UP },\
		{ "BTN_DPAD_DOWN", BTN_DPAD_DOWN },\
		{ "BTN_DPAD_LEFT", BTN_DPAD_LEFT },\
		{ "BTN_DPAD_RIGHT", BTN_DPAD_RIGHT },\
		{ "KEY_ESC", KEY_ESC },\
		{ "KEY_1", KEY_1 },\
		{ "KEY_2", KEY_2 },\
		{ "KEY_3", KEY_3 },\
		{ "KEY_4", KEY_4 },\
		{ "KEY_5", KEY_5 },\
		{ "KEY_6", KEY_6 },\
		{ "KEY_7", KEY_7 },\
		{ "KEY_8", KEY_8 },\
		{ "KEY_9", KEY_9 },\
		{ "KEY_0", KEY_0 },\
		{ "KEY_MINUS", KEY_MINUS },\
		{ "KEY_EQUAL", KEY_EQUAL },\
		{ "KEY_BACKSPACE", KEY_BACKSPACE },\
		{ "KEY_TAB", KEY_TAB },\
		{ "KEY_Q", KEY_Q },\
		{ "KEY_W", KEY_W },\
		{ "KEY_E", KEY_E },\
		{ "KEY_R", KEY_R },\
		{ "KEY_T", KEY_T },\
		{ "KEY_Y", KEY_Y },\
		{ "KEY_U", KEY_U },\
		{ "KEY_I", KEY_I },\
		{ "KEY_O", KEY_O },\
		{ "KEY_P", KEY_P },\
		{ "KEY_LEFTBRACE", KEY_LEFTBRACE },\
		{ "KEY_RIGHTBRACE", KEY_RIGHTBRACE },\
		{ "KEY_ENTER", KEY_ENTER },\
		{ "KEY_LEFTCTRL", KEY_LEFTCTRL },\
		{ "KEY_A", KEY_A },\
		{ "KEY_S", KEY_S },\
		{ "KEY_D", KEY_D },\
		{ "KEY_F", KEY_F },\
		{ "KEY_G", KEY_G },\
		{ "KEY_H", KEY_H },\
		{ "KEY_J", KEY_J },\
		{ "KEY_K", KEY_K },\
		{ "KEY_L", KEY_L },\
		{ "KEY_SEMICOLON", KEY_SEMICOLON },\
		{ "KEY_APOSTROPHE", KEY_APOSTROPHE },\
		{ "KEY_GRAVE", KEY_GRAVE },\
		{ "KEY_LEFTSHIFT", KEY_LEFTSHIFT },\
		{ "KEY_BACKSLASH", KEY_BACKSLASH },\
		{ "KEY_Z", KEY_Z },\
		{ "KEY_X", KEY_X },\
		{ "KEY_C", KEY_C },\
		{ "KEY_V", KEY_V },\
		{ "KEY_B", KEY_B },\
		{ "KEY_N", KEY_N },\
		{ "KEY_M", KEY_M },\
		{ "KEY_COMMA", KEY_COMMA },\
		{ "KEY_DOT", KEY_DOT },\
		{ "KEY_SLASH", KEY_SLASH },\
		{ "KEY_RIGHTSHIFT", KEY_RIGHTSHIFT },\
		{ "KEY_KPASTERISK", KEY_KPASTERISK },\
		{ "KEY_LEFTALT", KEY_LEFTALT },\
		{ "KEY_SPACE", KEY_SPACE },\
		{ "KEY_CAPSLOCK", KEY_CAPSLOCK },\
		{ "KEY_F1", KEY_F1 },\
		{ "KEY_F2", KEY_F2 },\
		{ "KEY_F3", KEY_F3 },\
		{ "KEY_F4", KEY_F4 },\
		{ "KEY_F5", KEY_F5 },\
		{ "KEY_F6", KEY_F6 },\
		{ "KEY_F7", KEY_F7 },\
		{ "KEY_F8", KEY_F8 },\
		{ "KEY_F9", KEY_F9 },\
		{ "KEY_F10", KEY_F10 },\
		{ "KEY_NUMLOCK", KEY_NUMLOCK },\
		{ "KEY_SCROLLLOCK", KEY_SCROLLLOCK },\
		{ "KEY_KP7", KEY_KP7 },\
		{ "KEY_KP8", KEY_KP8 },\
		{ "KEY_KP9", KEY_KP9 },\
		{ "KEY_KPMINUS", KEY_KPMINUS },\
		{ "KEY_KP4", KEY_KP4 },\
		{ "KEY_KP5", KEY_KP5 },\
		{ "KEY_KP6", KEY_KP6 },\
		{ "KEY_KPPLUS", KEY_KPPLUS },\
		{ "KEY_KP1", KEY_KP1 },\
		{ "KEY_KP2", KEY_KP2 },\
		{ "KEY_KP3", KEY_KP3 },\
		{ "KEY_KP0", KEY_KP0 },\
		{ "KEY_KPDOT", KEY_KPDOT },\
		{ "KEY_ZENKAKUHANKAKU", KEY_ZENKAKUHANKAKU },\
		{ "KEY_102ND", KEY_102ND },\
		{ "KEY_F11", KEY_F11 },\
		{ "KEY_F12", KEY_F12 },\
		{ "KEY_RO", KEY_RO },\
		{ "KEY_KATAKANA", KEY_KATAKANA },\
		{ "KEY_HIRAGANA", KEY_HIRAGANA },\
		{ "KEY_HENKAN", KEY_HENKAN },\
		{ "KEY_KATAKANAHIRAGANA", KEY_KATAKANAHIRAGANA },\
		{ "KEY_MUHENKAN", KEY_MUHENKAN },\
		{ "KEY_KPJPCOMMA", KEY_KPJPCOMMA },\
		{ "KEY_KPENTER", KEY_KPENTER },\
		{ "KEY_RIGHTCTRL", KEY_RIGHTCTRL },\
		{ "KEY_KPSLASH", KEY_KPSLASH },\
		{ "KEY_SYSRQ", KEY_SYSRQ },\
		{ "KEY_RIGHTALT", KEY_RIGHTALT },\
		{ "KEY_HOME", KEY_HOME },\
		{ "KEY_UP", KEY_UP },\
		{ "KEY_PAGEUP", KEY_PAGEUP },\
		{ "KEY_LEFT", KEY_LEFT },\
		{ "KEY_RIGHT", KEY_RIGHT },\
		{ "KEY_END", KEY_END },\
		{ "KEY_DOWN", KEY_DOWN },\
		{ "KEY_PAGEDOWN", KEY_PAGEDOWN },\
		{ "KEY_INSERT", KEY_INSERT },\
		{ "KEY_DELETE", KEY_DELETE },\
		{ "KEY_MUTE", KEY_MUTE },\
		{ "KEY_VOLUMEDOWN", KEY_VOLUMEDOWN },\
		{ "KEY_VOLUMEUP", KEY_VOLUMEUP },\
		{ "KEY_POWER", KEY_POWER },\
		{ "KEY_KPEQUAL", KEY_KPEQUAL },\
		{ "KEY_PAUSE", KEY_PAUSE },\
		{ "KEY_KPCOMMA", KEY_KPCOMMA },\
		{ "KEY_HANGEUL", KEY_HANGEUL },\
		{ "KEY_HANJA", KEY_HANJA },\
		{ "KEY_YEN", KEY_YEN },\
		{ "KEY_LEFTMETA", KEY_LEFTMETA },\
		{ "KEY_RIGHTMETA", KEY_RIGHTMETA },\
		{ "KEY_COMPOSE", KEY_COMPOSE },\
		{ "KEY_STOP", KEY_STOP },\
		{ "KEY_AGAIN", KEY_AGAIN },\
		{ "KEY_PROPS", KEY_PROPS },\
		{ "KEY_UNDO", KEY_UNDO },\
		{ "KEY_FRONT", KEY_FRONT },\
		{ "KEY_COPY", KEY_COPY },\
		{ "KEY_OPEN", KEY_OPEN },\
		{ "KEY_PASTE", KEY_PASTE },\
		{ "KEY_FIND", KEY_FIND },\
		{ "KEY_CUT", KEY_CUT },\
		{ "KEY_HELP", KEY_HELP },\
		{ "KEY_CALC", KEY_CALC },\
		{ "KEY_SLEEP", KEY_SLEEP },\
		{ "KEY_WWW", KEY_WWW },\
		{ "KEY_COFFEE", KEY_COFFEE },\
		{ "KEY_BACK", KEY_BACK },\
		{ "KEY_FORWARD", KEY_FORWARD },\
		{ "KEY_EJECTCD", KEY_EJECTCD },\
		{ "KEY_NEXTSONG", KEY_NEXTSONG },\
		{ "KEY_PLAYPAUSE", KEY_PLAYPAUSE },\
		{ "KEY_PREVIOUSSONG", KEY_PREVIOUSSONG },\
		{ "KEY_STOPCD", KEY_STOPCD },\
		{ "KEY_REFRESH", KEY_REFRESH },\
		{ "KEY_EDIT", KEY_EDIT },\
		{ "KEY_SCROLLUP", KEY_SCROLLUP },\
		{ "KEY_SCROLLDOWN", KEY_SCROLLDOWN },\
		{ "KEY_KPLEFTPAREN", KEY_KPLEFTPAREN },\
		{ "KEY_KPRIGHTPAREN", KEY_KPRIGHTPAREN },\
		{ "KEY_F13", KEY_F13 },\
		{ "KEY_F14", KEY_F14 },\
		{ "KEY_F15", KEY_F15 },\
		{ "KEY_F16", KEY_F16 },\
		{ "KEY_F17", KEY_F17 },\
		{ "KEY_F18", KEY_F18 },\
		{ "KEY_F19", KEY_F19 },\
		{ "KEY_F20", KEY_F20 },\
		{ "KEY_F21", KEY_F21 },\
		{ "KEY_F22", KEY_F22 },\
		{ "KEY_F23", KEY_F23 },\
		{ "KEY_F24", KEY_F24 },\
		{ "KEY_WAKEUP", KEY_WAKEUP },\
		{ "KEY_FILE", KEY_FILE },\
		{ "KEY_MAIL", KEY_MAIL },\
		{ "KEY_BOOKMARKS", KEY_BOOKMARKS },\
		{ "KEY_CONFIG", KEY_CONFIG },\
		{ "KEY_HOMEPAGE", KEY_HOMEPAGE },\
		{ "KEY_SEARCH", KEY_SEARCH },\
		{ "KEY_WORDPROCESSOR", KEY_WORDPROCESSOR },\
		{ "KEY_SPREADSHEET", KEY_SPREADSHEET },\
		{ "KEY_PRESENTATION", KEY_PRESENTATION },\
	}},\
	{ "EV_ABS", EV_ABS, {\
		{ "ABS_X", ABS_X },\
		{ "ABS_Y", ABS_Y },\
		{ "ABS_Z", ABS_Z },\
		{ "ABS_RX", ABS_RX },\
		{ "ABS_RY", ABS_RY },\
		{ "ABS_RZ", ABS_RZ },\
		{ "ABS_THROTTLE", ABS_THROTTLE },\
		{ "ABS_RUDDER", ABS_RUDDER },\
		{ "ABS_WHEEL", ABS_WHEEL },\
		{ "ABS_GAS", ABS_GAS },\
		{ "ABS_BRAKE", ABS_BRAKE },\
		{ "ABS_HAT0X", ABS_HAT0X },\
		{ "ABS_HAT0Y", ABS_HAT0Y },\
		{ "ABS_HAT1X", ABS_HAT1X },\
		{ "ABS_HAT1Y", ABS_HAT1Y },\
		{ "ABS_HAT2X", ABS_HAT2X },\
		{ "ABS_HAT2Y", ABS_HAT2Y },\
		{ "ABS_HAT3X", ABS_HAT3X },\
		{ "ABS_HAT3Y", ABS_HAT3Y },\
	}},\
	{ "EV_REL", EV_REL, {\
		{ "REL_X", REL_X },\
		{ "REL_Y", REL_Y },\
		{ "REL_Z", REL_Z },\
		{ "REL_RX", REL_RX },\
		{ "REL_RY", REL_RY },\
		{ "REL_RZ", REL_RZ },\
		{ "REL_HWHEEL", REL_HWHEEL },\
		{ "REL_DIAL", REL_DIAL },\
		{ "REL_WHEEL", REL_WHEEL },\
		{ "REL_MISC", REL_MISC },\
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
#define BTN_A BTN_SOUTH
#define BTN_EAST 51
#define BTN_B BTN_EAST
#define BTN_C 52
#define BTN_NORTH 53
#define BTN_X BTN_NORTH
#define BTN_WEST 54
#define BTN_Y BTN_WEST
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
