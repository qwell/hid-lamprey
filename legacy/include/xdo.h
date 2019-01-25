/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <xdo.h>

struct hl_xdo {
	xdo_t *xdo;
};

void *hl_xdo_init();
int hl_xdo_getactive(xdo_t *xdo, Window *window_ret);
int hl_xdo_search(xdo_t *xdo, char *window_name, Window **window_ret, unsigned int *nwindows);
int hl_xdo_activate(xdo_t *xdo, Window window);
int hl_xdo_keys(xdo_t *xdo, Window window, const char *keyseq);
