/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_INPUT_H
#define LAMPREY_INPUT_H

#if defined(HAVE_EVDEV) && defined(HAVE_SDL2)
#include "input-evdev.h"
#include "input-sdl2.h"

#define hl_input_init(...) {\
	hl_evdev_init(__VA_ARGS__);\
	hl_sdl2_init(__VA_ARGS__);\
}
#define hl_input_inject(id, type, code, value) {\
	hl_evdev_inject(id, type, code, value);\
	hl_sdl2_inject(id, type, code, value);\
}
#elif defined(HAVE_EVDEV)
#include "input-evdev.h"

#define hl_input_init(...) hl_evdev_init(__VA_ARGS__)
#define hl_input_inject(id, type, code, value) hl_evdev_inject(id, type, code, value)
#elif defined(HAVE_SDL2)
#include "input-sdl2.h"

#define hl_input_init(...) hl_sdl2_init(__VA_ARGS__)
#define hl_input_inject(id, type, code, value) hl_sdl2_inject(id, type, code, value)
#else
#define hl_input_init(...)
#define hl_input_inject(id, type, code, value)
#endif

#include "input-codetable.h"

#endif
