/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "include/lamprey.h"

#include "include/xdo.h"

void *hl_xdo_init() {
	struct hl_xdo *hl_xdo = malloc(sizeof(struct hl_xdo));

	printf("libxdo module version: %s\n", xdo_version());

	hl_xdo->xdo = xdo_new(NULL);

	return hl_xdo;
}

void hl_xdo_dostuff(struct hl_xdo *hl_xdo) {
	Window activewindow = 0;
	Window *searchwindow = NULL;
	unsigned int nwindows;
	char *test_window_name = "LiveSplit";

	hl_xdo_getactive(hl_xdo->xdo, &activewindow);
	printf("Active Window: %ld\n", activewindow);

	hl_xdo_search(hl_xdo->xdo, test_window_name, &searchwindow, &nwindows);
	if (nwindows > 0) {
		printf("%s Window: %ld\n", test_window_name, searchwindow[0]);
		if (!hl_xdo_activate(hl_xdo->xdo, searchwindow[0])) {

			hl_xdo_keys(hl_xdo->xdo, searchwindow[0], "1");
		}
	}
	hl_xdo_activate(hl_xdo->xdo, activewindow);
}

int hl_xdo_getactive(xdo_t *xdo, Window *window_ret) {
	int ret = xdo_get_active_window(xdo, window_ret);
	return ret;
}

int hl_xdo_search(xdo_t *xdo, char *window_name, Window **window_ret, unsigned int *nwindows) {
	int ret;
	xdo_search_t search;

	memset(&search, 0, sizeof(xdo_search_t));

	search.max_depth = -1;
	search.require = SEARCH_ALL;
	search.searchmask |= SEARCH_NAME;
	search.searchmask |= SEARCH_ONLYVISIBLE;
	search.limit = 1;
	search.winname = window_name;

	ret = xdo_search_windows(xdo, &search, window_ret, nwindows);
	return ret;
}

int hl_xdo_activate(xdo_t *xdo, Window window) {
	int ret = xdo_activate_window(xdo, window);
	if (ret) {
		return ret;
	} else {
		int r;
		Window activewindow = 0;
		while (activewindow != window) {
			r = xdo_get_active_window(xdo, &activewindow);
			if (r == XDO_ERROR) {
				return r;
			}
			usleep(1000);
		}
//		xdo_wait_for_window_active(xdo, window, 1);
	}

	return ret;
}

int hl_xdo_keys(xdo_t *xdo, Window window, const char *keyseq) {
	useconds_t key_delay = 50000;

	int ret = xdo_send_keysequence_window(xdo, window, keyseq, key_delay);
	return ret;
}
