/*
* Copyright (C) 2018, Jason Parker
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/

extern hl_thread_t t_display_win32;
extern hl_mutex_t mutex_display_win32;

void hl_display_win32_init(int argc, char **argv);
void hl_display_win32_output_raw(const char *device, const char *rawname, int value);
void hl_display_win32_output_controller(struct controller *controller);