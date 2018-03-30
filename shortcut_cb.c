/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>

#include "include/shortcut_cb.h"

void callback_test(void *ptr) {
	struct cb_test *args = ptr;

	printf("callback_test, args->foo: %s, args->bar: %d\n", args->foo, args->bar);
}
