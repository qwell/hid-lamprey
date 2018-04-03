/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef _LAMPREY_H
#define _LAMPREY_H

#include "configure.h"
#include "settings.h"
#include "defaults.h"

#ifndef __linux__
#error "No.  Go get a real OS and try again."
#endif

#if defined(DEBUG)
#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...) do {} while(0)
#endif

#endif
