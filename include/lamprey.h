/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "version.h"
#include "settings.h"
#include "defaults.h"

#ifdef DEBUG
#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif
