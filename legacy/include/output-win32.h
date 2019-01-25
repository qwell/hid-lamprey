/*
* Copyright (C) 2018, Jason Parker
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/

#ifndef LAMPREY_OUTPUT_WIN32_H
#define LAMPREY_OUTPUT_WIN32_H

#include "lamprey.h"

#include "threads.h"

void hl_output_win32_init();
void hl_output_win32_destroy();
void hl_output_win32_inject(uint8_t type, uint16_t code, int16_t value);

#endif
