/*
* Copyright (C) 2018, Jason Parker
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/

#include <string.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

struct hl_active_skin *hl_active_skin;

void xml_generic_skin_error_func(void *ctx, const char *msg, ...) {
	return;
}

struct button_code *skin_lookup_button(char *compat_name) {
	struct compat_list {
		char *name;
		uint8_t type;
		uint16_t code;
	} compat_list[] = {
		{ "up", EV_KEY, BTN_DPAD_UP },
		{ "right", EV_KEY, BTN_DPAD_RIGHT },
		{ "down", EV_KEY, BTN_DPAD_DOWN },
		{ "left", EV_KEY, BTN_DPAD_LEFT },
		{ "x", EV_KEY, BTN_NORTH },
		{ "y", EV_KEY, BTN_WEST },
		{ "a", EV_KEY, BTN_EAST },
		{ "b", EV_KEY, BTN_SOUTH },
		{ "l", EV_KEY, BTN_TL },
		{ "r", EV_KEY, BTN_TR},
		{ "select", EV_KEY, BTN_SELECT },
		{ "start", EV_KEY, BTN_START },
	};

	for (int i = 0; i < sizeof(compat_list) / sizeof(*compat_list); i++) {
		if (!strcmp(compat_list[i].name, compat_name)) {
			struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));
			button->type = compat_list[i].type;
			button->code = compat_list[i].code;
			return button;
		}
	}
	return NULL;
}

void hl_skin_load(char *skin_name, char *background_name) {
	char *skin_xml_file = "skin.xml";

	char **skin_list = NULL;
	int skin_count = 0;

	xmlDoc *doc;

#if defined(_WIN32)
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR scanPath[64];
	snprintf(scanPath, sizeof(scanPath) - 1, "skins\\*");

	if ((hFind = FindFirstFile(scanPath, &ffd)) != INVALID_HANDLE_VALUE) {
		do {
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, "..")) {
					continue;
				}
				skin_list = (char **)realloc(skin_list, (skin_count + 1) * sizeof(*skin_list));
				skin_list[skin_count] = strdup(ffd.cFileName);
				skin_count++;
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		FindClose(hFind);
	}
#else
#endif

	xmlSetGenericErrorFunc(NULL, xml_generic_skin_error_func);

	for (int z = 0; z < skin_count; z++) {
		char skin_path[128];
		snprintf(skin_path, sizeof(skin_path) - 1, "skins/%s/%s", skin_list[z], skin_xml_file);

		if (!(doc = xmlParseFile(skin_path))) {
			printf("Skin file '%s' is missing or invalid.\n", skin_list[z]);
			return;
		} else {
			//TODO Verify against an XSD
			xmlXPathContext *context;

			xmlChar *xpath = (xmlChar *)"/skin";
			xmlXPathObject *result;

			if (!(context = xmlXPathNewContext(doc))) {
				printf("Skin file '%s' could not be loaded.\n", skin_list[z]);
				xmlFreeDoc(doc);
				continue;
			}

			if (!(result = xmlXPathEvalExpression(xpath, context))) {
				printf("Skin file has no category skin'.\n");
			} else {
				xmlNodeSet *nodeset = result->nodesetval;

				for (int i = 0; i < nodeset->nodeNr; i++) {
					xmlNode *node = nodeset->nodeTab[i];

					xmlChar *nodename = xmlGetProp(node, (const xmlChar *)"name");

					if (!xmlStrcmp(nodename, (const xmlChar *)skin_name)) {
						hl_active_skin = (struct hl_active_skin *)calloc(1, sizeof(struct hl_active_skin));
						snprintf(hl_active_skin->path, sizeof(hl_active_skin->path) - 1, "skins/%s/", skin_list[z]);
						strncpy(hl_active_skin->name, (char *)nodename, sizeof(hl_active_skin->name) - 1);

						for (xmlNode *cur = node->children; cur; cur = cur->next) {
							if (cur->type == XML_ELEMENT_NODE) {
								if (!xmlStrcmp(cur->name, (const xmlChar *)"background")) {
									xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");
									xmlChar *image = xmlGetProp(cur, (const xmlChar *)"image");

									if (!xmlStrcmp(name, (xmlChar *)background_name)) {
										strncpy(hl_active_skin->background.name, (char *)name, sizeof(hl_active_skin->background.name) - 1);
										strncpy(hl_active_skin->background.filename, (char *)image, sizeof(hl_active_skin->background.filename) - 1);
									}

									xmlFree(name);
									xmlFree(image);
								}
								else if (!xmlStrcmp(cur->name, (const xmlChar *)"button")) {
									struct button_code *button_code;

									xmlChar *image = xmlGetProp(cur, (const xmlChar *)"image");
									xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");
									xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
									xmlChar *pos_x = xmlGetProp(cur, (const xmlChar *)"x");
									xmlChar *pos_y = xmlGetProp(cur, (const xmlChar *)"y");

									if (type && code) {
										button_code = hl_controller_get_code_by_name((char *)type, (char *)code);
									}
									else {
										// For compatibility with NintendoSpy skins, lookup type and code for button "name".
										xmlChar *compat_name = xmlGetProp(cur, (const xmlChar *)"name");
										button_code = skin_lookup_button((char *)compat_name);
										xmlFree(compat_name);
									}

									if (button_code) {
										struct hl_skin_button *button = (struct hl_skin_button *)calloc(1, sizeof(struct hl_skin_button));

										strncpy(button->filename, (char *)image, sizeof(button->filename) - 1);
										button->code = button_code->code;
										button->type = button_code->type;
										button->x = atoi((char *)pos_x);
										button->y = atoi((char *)pos_y);

										hl_active_skin->buttons = (struct hl_skin_button **)realloc(hl_active_skin->buttons, (hl_active_skin->button_count + 1) * sizeof(*hl_active_skin->buttons));
										hl_active_skin->buttons[hl_active_skin->button_count] = button;
										hl_active_skin->button_count++;

										free(button_code);
									}

									xmlFree(image);
									xmlFree(type);
									xmlFree(code);
									xmlFree(pos_x);
									xmlFree(pos_y);
								}
							}
						}

						if (!strlen(hl_active_skin->background.filename)) {
							free(hl_active_skin);
							hl_active_skin = NULL;
						}
					}
					xmlFree(nodename);
				}
				xmlXPathFreeObject(result);
			}

			xmlFree(context);
			xmlFreeDoc(doc);

			printf("Skin file '%s' checked.\n", skin_list[z]);
		}
	}
}
