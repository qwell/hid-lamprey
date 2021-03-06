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

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/display.h"

#include "include/display-win32-main.h"
#include "include/display-win32-settings.h"

using namespace hidlamprey;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Threading::Tasks;

hl_thread_t t_display_win32;
hl_mutex_t mutex_display_win32;

void *display_win32_show_window() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	formMain^ form = formMain::Instance();
	Application::Run(form);

	exit(1); //TODO: Signal the main thread to die.
	return NULL;
}

void hl_display_win32_init(int argc, char **argv) {
	hl_mutex_create(&mutex_display_win32);
	hl_thread_create(&t_display_win32, display_win32_show_window, NULL);
	return;
}

void hl_display_win32_output_controller(struct controller *controller) {
	if (!controller) {
		return;
	}

	formMain::Instance()->output_controller(controller);
}

void hl_display_win32_output_raw(const char *device, const char *rawname, int value) {
	formMain::Instance()->output_raw(device, rawname, value);
}
