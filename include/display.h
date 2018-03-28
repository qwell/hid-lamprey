/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifdef __linux__
#include "display-cli.h"

#ifdef USE_GTK
#include "display-gtk.h"

#define hl_display_init(...) hl_gtk_init(__VA_ARGS__)
#else
#define hl_display_init(...)
#endif
#endif
