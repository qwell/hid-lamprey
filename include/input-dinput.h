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
void hl_input_dinput_inject(int id, uint8_t type, uint16_t code, int16_t value);

#endif