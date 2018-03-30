/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef _SHORTCUT_CB_H
#define _SHORTCUT_CB_H

#define SHORTCUT_CB_DEFINE(name, ...) \
struct cb_ ##name {\
__VA_ARGS__\
};\
void callback_ ##name (void *args);

/* Define callback test with struct members foo and bar. */
SHORTCUT_CB_DEFINE(test,
	char *foo;
	int bar;
);

#endif
