/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_OUTPUT_H
#define LAMPREY_OUTPUT_H

#if defined(HAVE_EVDEV)
#include "output-evdev.h"

#define hl_output_init() hl_output_evdev_init()
#define hl_output_destroy() hl_output_evdev_destroy()
#define hl_output_inject(type, code, value) hl_output_evdev_inject(type, code, value)
#elif defined(_WIN32)
#include "output-win32.h"

#define hl_output_init() hl_output_win32_init()
#define hl_output_destroy() hl_output_win32_destroy()
#define hl_output_inject(type, code, value) hl_output_win32_inject(type, code, value)
#else
#define hl_output_init()
#define hl_output_destroy()
#define hl_output_inject(type, code, value)
#endif

#endif
