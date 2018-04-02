/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#if defined(HAVE_EVDEV)
#include "input-evdev.h"

#define hl_input_init(...) hl_evdev_init(__VA_ARGS__)
#define hl_input_inject(id, type, code, value) hl_evdev_inject(id, type, code, value)
#else
#include "input-defines.h"

#define hl_input_init(...)
#define hl_input_inject(id, type, code, value)
#endif
