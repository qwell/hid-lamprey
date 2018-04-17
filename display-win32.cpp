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

using namespace System;
using namespace System::Windows::Forms;

void hl_display_win32_init(int argc, char **argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	hidlamprey::formMain form;
	Application::Run(%form);

	return;
}

void hl_display_win32_output_controller(struct controller_display *controller) {
}

