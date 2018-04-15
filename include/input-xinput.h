/*
* Copyright (C) 2018, Jason Parker
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/

#ifndef LAMPREY_INPUT_XINPUT_H
#define LAMPREY_INPUT_XINPUT_H

#include "lamprey.h"

#include "threads.h"

extern HL_THREAD t_xinput;
extern HL_MUTEX mutex_xinput;

void hl_input_xinput_init();
void hl_input_xinput_destroy();
void *hl_input_xinput_poll();
void hl_input_xinput_inject(int id, uint8_t type, uint16_t code, int16_t value);

#endif