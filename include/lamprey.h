/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_H
#define LAMPREY_H

#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef HAVE_STDBOOL_H
	#include <stdbool.h>
#else
	#ifndef HAVE__BOOL
		#ifdef __cplusplus
			typedef bool _Bool;
		#else
			#define _Bool signed char
		#endif
	#endif
	#define bool _Bool
	#define false 0
	#define true 1
#endif

#include "config.h"
#include "settings.h"
#include "defaults.h"

#if defined(DEBUG)
	#define debug_print(...) printf(__VA_ARGS__)
#else
	#define debug_print(...) do {} while(0)
#endif

#endif
