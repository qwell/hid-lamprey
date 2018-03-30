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

#define SHORTCUT_DECL(name, ...) \
struct cb_ ##name {\
__VA_ARGS__\
};\
void callback_ ##name (void *args);

SHORTCUT_DECL(test,
	char *foo;
	int bar;
);

#endif
