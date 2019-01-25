/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_SETTINGS_H
#define LAMPREY_SETTINGS_H

struct hl_settings_skin {
	char *name;
	char *background;
};

struct hl_settings {
	struct hl_settings_skin *skin;
	float deadzone_axis;
	float deadzone_hat;
};

extern struct hl_settings *hl_settings;

#if defined(HAVE_XML2)
#include "settings-xml2.h"
#define hl_settings_load_settings(...) settings_xml_load_settings(__VA_ARGS__)
#define hl_settings_load_mappings(...) settings_xml_load_mappings(__VA_ARGS__)
#define hl_settings_load_shortcuts(...) settings_xml_load_shortcuts(__VA_ARGS__)
#define hl_settings_load_emulations(...) settings_xml_load_emulations(__VA_ARGS__)
#define hl_settings_save_mappings(...) settings_xml_save_mappings(__VA_ARGS__)
#define hl_settings_init(...) settings_xml_init(__VA_ARGS__)
#define hl_settings_destroy(...) settings_xml_destroy(__VA_ARGS__)
#else
#define hl_settings_load_settings(...)
#define hl_settings_load_mappings(...)
#define hl_settings_load_shortcuts(...)
#define hl_settings_load_emulations(...)
#define hl_settings_save_mappings(...)
#define hl_settings_init(...)
#define hl_settings_destroy(...)
#endif

#endif
