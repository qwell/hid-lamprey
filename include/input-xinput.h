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

extern hl_thread_t t_input_xinput;
extern hl_mutex_t mutex_input_xinput;

void hl_input_xinput_init();
void hl_input_xinput_destroy();
void *hl_input_xinput_poll();

#endif
