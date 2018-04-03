/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "include/lamprey.h"

#include "include/settings.h"

void xml_generic_error_func(void *ctx, const char *msg, ...) {
	return;
}

void hl_settings_xml_load() {
	char *filename = "settings.xml";
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr node;

	xmlSetGenericErrorFunc(NULL, xml_generic_error_func);

	if (!(doc = xmlParseFile(filename))) {
		printf("Settings file '%s' is missing or invalid.\n", filename);
		return;
	}

	if (!(root = xmlDocGetRootElement(doc))) {
		printf("Settings file '%s' is empty.\n", filename);
		xmlFreeDoc(doc);
		return;
	}

	node = root->xmlChildrenNode;
	while (node) {

		node = node->next;
	}

	xmlFreeDoc(doc);
}

void hl_settings_xml_save() {
}
