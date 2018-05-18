/*
* Copyright (C) 2018, Jason Parker
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/

#ifndef LAMPREY_INPUT_DINPUT_H
#define LAMPREY_INPUT_DINPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "lamprey.h"

#include "threads.h"

struct dinput_device {
	char name[32];
	DWORD type;
	LPDIRECTINPUTDEVICE8 device;
	DIDEVCAPS capabilities;
	HANDLE event;
	BYTE state[256];
};

struct hl_input_dinput {
	LPDIRECTINPUT8 di;
	struct dinput_device **devices;
	int device_count;
	int gamepad_count;
	int mouse_count;
	int keyboard_count;
};

extern hl_thread_t t_input_dinput;
extern hl_mutex_t mutex_input_dinput;
extern struct hl_input_dinput *hl_input_dinput;

void hl_input_dinput_init();
void hl_input_dinput_destroy();
void *hl_input_dinput_poll();

#define DINPUT_DEFAULT_KEYMAP \
	{ DIK_A, EV_KEY, KEY_A },\
	{ DIK_B, EV_KEY, KEY_B },\
	{ DIK_C, EV_KEY, KEY_C },\
	{ DIK_D, EV_KEY, KEY_D },\
	{ DIK_E, EV_KEY, KEY_E },\
	{ DIK_F, EV_KEY, KEY_F },\
	{ DIK_G, EV_KEY, KEY_G },\
	{ DIK_H, EV_KEY, KEY_H },\
	{ DIK_I, EV_KEY, KEY_I },\
	{ DIK_J, EV_KEY, KEY_J },\
	{ DIK_K, EV_KEY, KEY_K },\
	{ DIK_L, EV_KEY, KEY_L },\
	{ DIK_M, EV_KEY, KEY_M },\
	{ DIK_N, EV_KEY, KEY_N },\
	{ DIK_O, EV_KEY, KEY_O },\
	{ DIK_P, EV_KEY, KEY_P },\
	{ DIK_Q, EV_KEY, KEY_Q },\
	{ DIK_R, EV_KEY, KEY_R },\
	{ DIK_S, EV_KEY, KEY_S },\
	{ DIK_T, EV_KEY, KEY_T },\
	{ DIK_U, EV_KEY, KEY_U },\
	{ DIK_V, EV_KEY, KEY_V },\
	{ DIK_W, EV_KEY, KEY_W },\
	{ DIK_X, EV_KEY, KEY_X },\
	{ DIK_Y, EV_KEY, KEY_Y },\
	{ DIK_Z, EV_KEY, KEY_Z },\
	{ DIK_NUMPAD0, EV_KEY, KEY_KP0 },\
	{ DIK_NUMPAD1, EV_KEY, KEY_KP1 },\
	{ DIK_NUMPAD2, EV_KEY, KEY_KP2 },\
	{ DIK_NUMPAD3, EV_KEY, KEY_KP3 },\
	{ DIK_NUMPAD4, EV_KEY, KEY_KP4 },\
	{ DIK_NUMPAD5, EV_KEY, KEY_KP5 },\
	{ DIK_NUMPAD6, EV_KEY, KEY_KP6 },\
	{ DIK_NUMPAD7, EV_KEY, KEY_KP7 },\
	{ DIK_NUMPAD8, EV_KEY, KEY_KP8 },\
	{ DIK_NUMPAD9, EV_KEY, KEY_KP9 },\
	{ DIK_NUMPADENTER, EV_KEY, KEY_KPENTER },\
	{ DIK_NUMPADSTAR, EV_KEY, KEY_KPASTERISK },\
	{ DIK_NUMPADSLASH, EV_KEY, KEY_KPSLASH },\
	{ DIK_NUMPADMINUS, EV_KEY, KEY_KPMINUS },\
	{ DIK_NUMPADPLUS, EV_KEY, KEY_KPPLUS },\
	{ DIK_NUMPADPERIOD, EV_KEY, KEY_KPDOT },\
	{ DIK_ESCAPE, EV_KEY, KEY_ESC },\
	{ DIK_F1, EV_KEY, KEY_F1 },\
	{ DIK_F2, EV_KEY, KEY_F2 },\
	{ DIK_F3, EV_KEY, KEY_F3 },\
	{ DIK_F4, EV_KEY, KEY_F4 },\
	{ DIK_F5, EV_KEY, KEY_F5 },\
	{ DIK_F6, EV_KEY, KEY_F6 },\
	{ DIK_F7, EV_KEY, KEY_F7 },\
	{ DIK_F8, EV_KEY, KEY_F8 },\
	{ DIK_F9, EV_KEY, KEY_F9 },\
	{ DIK_F10, EV_KEY, KEY_F10 },\
	{ DIK_F11, EV_KEY, KEY_F11 },\
	{ DIK_F12, EV_KEY, KEY_F12 },\
	{ DIK_0, EV_KEY, KEY_0 },\
	{ DIK_1, EV_KEY, KEY_1 },\
	{ DIK_2, EV_KEY, KEY_2 },\
	{ DIK_3, EV_KEY, KEY_3 },\
	{ DIK_4, EV_KEY, KEY_4 },\
	{ DIK_5, EV_KEY, KEY_5 },\
	{ DIK_6, EV_KEY, KEY_6 },\
	{ DIK_7, EV_KEY, KEY_7 },\
	{ DIK_8, EV_KEY, KEY_8 },\
	{ DIK_9, EV_KEY, KEY_9 },\
	{ DIK_LEFT, EV_KEY, KEY_LEFT },\
	{ DIK_RIGHT, EV_KEY, KEY_RIGHT },\
	{ DIK_UP, EV_KEY, KEY_UP },\
	{ DIK_DOWN, EV_KEY, KEY_DOWN },\
	{ DIK_LSHIFT, EV_KEY, KEY_LEFTSHIFT },\
	{ DIK_RSHIFT, EV_KEY, KEY_RIGHTSHIFT },\
	{ DIK_LCONTROL, EV_KEY, KEY_LEFTCTRL },\
	{ DIK_RCONTROL, EV_KEY, KEY_RIGHTCTRL },\
	{ DIK_LALT, EV_KEY, KEY_LEFTALT },\
	{ DIK_RALT, EV_KEY, KEY_RIGHTALT },\
	{ DIK_GRAVE, EV_KEY, KEY_GRAVE },\
	{ DIK_MINUS, EV_KEY, KEY_MINUS },\
	{ DIK_EQUALS, EV_KEY, KEY_EQUAL },\
	{ DIK_BACKSPACE, EV_KEY, KEY_BACKSPACE },\
	{ DIK_TAB, EV_KEY, KEY_TAB },\
	{ DIK_LBRACKET, EV_KEY, KEY_LEFTBRACE },\
	{ DIK_RBRACKET, EV_KEY, KEY_RIGHTBRACE },\
	{ DIK_SEMICOLON, EV_KEY, KEY_SEMICOLON },\
	{ DIK_APOSTROPHE, EV_KEY, KEY_APOSTROPHE },\
	{ DIK_RETURN, EV_KEY, KEY_ENTER },\
	{ DIK_COMMA, EV_KEY, KEY_COMMA },\
	{ DIK_PERIOD, EV_KEY, KEY_DOT },\
	{ DIK_SLASH, EV_KEY, KEY_SLASH },\
	{ DIK_SPACE, EV_KEY, KEY_SPACE },\
	{ DIK_BACKSLASH, EV_KEY, KEY_BACKSLASH },\

#endif
