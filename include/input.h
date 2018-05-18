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

#if defined(HAVE_EVDEV)
#include "input-evdev.h"

#define hl_input_init(...) hl_input_evdev_init(__VA_ARGS__)
#elif defined(_WIN32)
#include "input-dinput.h"
#include "input-xinput.h"

#define hl_input_init(...) {\
	hl_input_dinput_init(__VA_ARGS__);\
	hl_input_xinput_init(__VA_ARGS__);\
};
#else
#define hl_input_init(...)
#endif

#include "input-codetable.h"

#endif
