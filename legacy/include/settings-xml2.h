/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlschemas.h>
#include <libxml/xpath.h>

void settings_xml_load_settings();
void settings_xml_load_mappings();
void settings_xml_load_shortcuts();
void settings_xml_load_emulations();
void settings_xml_save_mappings();
void settings_xml_init();
void settings_xml_destroy();
