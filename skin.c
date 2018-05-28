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

struct hl_skin **hl_skins;
int hl_skin_count;

void xml_generic_skin_error_func(void *ctx, const char *msg, ...) {
	return;
}

struct button_code *skin_lookup_button(char *compat_type, char *compat_name) {
	struct compat_input {
		char *name;
		uint8_t type;
		uint16_t code;
	};
	struct compat_list {
		char *type;
		struct compat_input inputs[32];
	} compat_list[] = {
		{ "nes",{
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "a", EV_KEY, BTN_EAST },
			{ "b", EV_KEY, BTN_SOUTH },
			{ "select", EV_KEY, BTN_SELECT },
			{ "start", EV_KEY, BTN_START },
		} },
		{ "snes", {
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "x", EV_KEY, BTN_NORTH },
			{ "y", EV_KEY, BTN_WEST },
			{ "a", EV_KEY, BTN_EAST },
			{ "b", EV_KEY, BTN_SOUTH },
			{ "l", EV_KEY, BTN_TL },
			{ "r", EV_KEY, BTN_TR },
			{ "select", EV_KEY, BTN_SELECT },
			{ "start", EV_KEY, BTN_START },
		} },
		{ "n64", {
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "cup", EV_KEY, BTN_NORTH },
			{ "cright", EV_KEY, BTN_EAST },
			{ "cdown", EV_KEY, BTN_SOUTH },
			{ "cleft", EV_KEY, BTN_WEST },
			{ "b", EV_KEY, BTN_C },
			{ "a", EV_KEY, BTN_Z },
			{ "z", EV_KEY, BTN_TL2 },
			{ "start", EV_KEY, BTN_START },
			{ "l", EV_KEY, BTN_TL },
			{ "r", EV_KEY, BTN_TR },
			{ "start", EV_KEY, BTN_START },
			{ "stick_x", EV_ABS, ABS_X },
			{ "stick_y", EV_ABS, ABS_Y },
		} },
		{ "gamecube",{
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "x", EV_KEY, BTN_NORTH },
			{ "y", EV_KEY, BTN_WEST },
			{ "a", EV_KEY, BTN_EAST },
			{ "b", EV_KEY, BTN_SOUTH },
			{ "z", EV_KEY, BTN_Z },
			{ "l", EV_KEY, BTN_TL },
			{ "r", EV_KEY, BTN_TR },
			{ "start", EV_KEY, BTN_START },
		} },
		{ "playstation",{
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "triangle", EV_KEY, BTN_NORTH },
			{ "square", EV_KEY, BTN_WEST },
			{ "circle", EV_KEY, BTN_EAST },
			{ "x", EV_KEY, BTN_SOUTH },
			{ "lstick", EV_KEY, BTN_THUMBL },
			{ "rstick", EV_KEY, BTN_THUMBR },
			{ "l1", EV_KEY, BTN_TL },
			{ "r1", EV_KEY, BTN_TR },
			{ "l2", EV_KEY, BTN_TL2 },
			{ "r2", EV_KEY, BTN_TR2 },
			{ "select", EV_KEY, BTN_SELECT },
			{ "start", EV_KEY, BTN_START },
		} },
		{ "sega", {
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "a", EV_KEY, BTN_WEST },
			{ "b", EV_KEY, BTN_SOUTH },
			{ "c", EV_KEY, BTN_EAST },
			{ "x", EV_KEY, BTN_NORTH },
			{ "y", EV_KEY, BTN_C },
			{ "z", EV_KEY, BTN_Z },
			{ "start", EV_KEY, BTN_START },
		} },
		{ "classic", {
			{ "up", EV_KEY, BTN_DPAD_UP },
			{ "right", EV_KEY, BTN_DPAD_RIGHT },
			{ "down", EV_KEY, BTN_DPAD_DOWN },
			{ "left", EV_KEY, BTN_DPAD_LEFT },
			{ "1", EV_KEY, BTN_SOUTH },
			{ "2", EV_KEY, BTN_EAST },
		}},
	};

	for (int i = 0; i < sizeof(compat_list) / sizeof(*compat_list); i++) {
		if (!compat_list[i].type || strcmp(compat_list[i].type, compat_type)) {
			continue;
		}

		for (int j = 0; j < sizeof(compat_list[i].inputs) / sizeof(*compat_list[i].inputs); j++) {
			if (!compat_list[i].inputs[j].name || strcmp(compat_list[i].inputs[j].name, compat_name)) {
				continue;
			}

			struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));
			button->type = compat_list[i].inputs[j].type;
			button->code = compat_list[i].inputs[j].code;
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

				hl_skin *skin = (struct hl_skin *)calloc(1, sizeof(struct hl_skin));

				for (int i = 0; i < nodeset->nodeNr; i++) {
					xmlNode *node = nodeset->nodeTab[i];

					xmlChar *skinname = xmlGetProp(node, (const xmlChar *)"name");
					xmlChar *skintype = xmlGetProp(node, (const xmlChar *)"type");

					snprintf(skin->path, sizeof(skin->path) - 1, "skins/%s/", skin_list[z]);
					strncpy(skin->name, (char *)skinname, sizeof(skin->name) - 1);

					for (xmlNode *cur = node->children; cur; cur = cur->next) {
						if (cur->type == XML_ELEMENT_NODE) {
							if (!xmlStrcmp(cur->name, (const xmlChar *)"background")) {
								struct hl_skin_background *background = (struct hl_skin_background *)calloc(1, sizeof(struct hl_skin_background));

								xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");
								xmlChar *image = xmlGetProp(cur, (const xmlChar *)"image");

								strncpy(background->name, (char *)name, sizeof(background->name) - 1);
								strncpy(background->filename, (char *)image, sizeof(background->filename) - 1);

								skin->backgrounds = (struct hl_skin_background **)realloc(skin->backgrounds, (skin->background_count + 1) * sizeof(*skin->backgrounds));
								skin->backgrounds[skin->background_count] = background;
								skin->background_count++;

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
								else if (skintype) {
									// For compatibility with NintendoSpy skins, lookup type and code for button "name" on controller "type".
									xmlChar *compat_name = xmlGetProp(cur, (const xmlChar *)"name");
									button_code = skin_lookup_button((char *)skintype, (char *)compat_name);
									xmlFree(compat_name);
								}

								if (button_code) {
									struct hl_skin_button *button = (struct hl_skin_button *)calloc(1, sizeof(struct hl_skin_button));

									strncpy(button->filename, (char *)image, sizeof(button->filename) - 1);
									button->code = button_code->code;
									button->type = button_code->type;
									button->x = atoi((char *)pos_x);
									button->y = atoi((char *)pos_y);

									skin->buttons = (struct hl_skin_button **)realloc(skin->buttons, (skin->button_count + 1) * sizeof(*skin->buttons));
									skin->buttons[skin->button_count] = button;
									skin->button_count++;

									free(button_code);
								}

								xmlFree(image);
								xmlFree(type);
								xmlFree(code);
								xmlFree(pos_x);
								xmlFree(pos_y);
							}
							else if (!xmlStrcmp(cur->name, (const xmlChar *)"axis")) {
								struct button_code *button_code_x;
								struct button_code *button_code_y;

								xmlChar *image = xmlGetProp(cur, (const xmlChar *)"image");

								xmlChar *type_x = xmlGetProp(cur, (const xmlChar *)"type_x");
								xmlChar *code_x = xmlGetProp(cur, (const xmlChar *)"code_x");
								xmlChar *pos_x = xmlGetProp(cur, (const xmlChar *)"x");
								xmlChar *offset_x = xmlGetProp(cur, (const xmlChar *)"offset_x");
								xmlChar *trigger_x = xmlGetProp(cur, (const xmlChar *)"trigger_x");

								xmlChar *type_y = xmlGetProp(cur, (const xmlChar *)"type_y");
								xmlChar *code_y = xmlGetProp(cur, (const xmlChar *)"code_y");
								xmlChar *pos_y = xmlGetProp(cur, (const xmlChar *)"y");
								xmlChar *offset_y = xmlGetProp(cur, (const xmlChar *)"offset_y");
								xmlChar *trigger_y = xmlGetProp(cur, (const xmlChar *)"trigger_y");

								if (type_x && code_x) {
									button_code_x = hl_controller_get_code_by_name((char *)type_x, (char *)code_x);
								}
								if (type_y && code_y) {
									button_code_y = hl_controller_get_code_by_name((char *)type_y, (char *)code_y);
								}

								if (button_code_x || button_code_y) {
									struct hl_skin_axis *axis = (struct hl_skin_axis *)calloc(1, sizeof(struct hl_skin_axis));

									strncpy(axis->filename, (char *)image, sizeof(axis->filename) - 1);
									axis->x = atoi((char *)pos_x);
									axis->y = atoi((char *)pos_y);
									if (offset_x) {
										axis->offset_x = strtoul((char *)offset_x, (char **)NULL, 10);
									}
									if (offset_y) {
										axis->offset_y = strtoul((char *)offset_y, (char **)NULL, 10);
									}
									if (trigger_x) {
										axis->trigger_x = strtoul((char *)trigger_x, (char **)NULL, 10);
									}
									if (trigger_y) {
										axis->trigger_y = strtoul((char *)trigger_y, (char **)NULL, 10);
									}

									if (button_code_x) {
										axis->code_x = button_code_x->code;
										axis->type_x = button_code_x->type;
										free(button_code_x);
									}
									if (button_code_y) {
										axis->code_y = button_code_y->code;
										axis->type_y = button_code_y->type;
										free(button_code_y);
									}

									skin->axes = (struct hl_skin_axis **)realloc(skin->axes, (skin->axis_count + 1) * sizeof(*skin->axes));
									skin->axes[skin->axis_count] = axis;
									skin->axis_count++;
								}

								xmlFree(image);
								xmlFree(type_x);
								xmlFree(code_x);
								xmlFree(pos_x);
								xmlFree(offset_x);
								xmlFree(trigger_x);
								xmlFree(type_y);
								xmlFree(code_y);
								xmlFree(pos_y);
								xmlFree(offset_y);
								xmlFree(trigger_y);
							}
							else if (!xmlStrcmp(cur->name, (const xmlChar *)"stick")) {
								/* For compatibility. */
								struct button_code *button_code_x;
								struct button_code *button_code_y;

								xmlChar *image = xmlGetProp(cur, (const xmlChar *)"image");

								xmlChar *xname = xmlGetProp(cur, (const xmlChar *)"xname");
								xmlChar *pos_x = xmlGetProp(cur, (const xmlChar *)"x");
								xmlChar *range_x = xmlGetProp(cur, (const xmlChar *)"xrange");

								xmlChar *yname = xmlGetProp(cur, (const xmlChar *)"yname");
								xmlChar *pos_y = xmlGetProp(cur, (const xmlChar *)"y");
								xmlChar *range_y = xmlGetProp(cur, (const xmlChar *)"yrange");

								if (skintype) {
									button_code_x = skin_lookup_button((char *)skintype, (char *)xname);
									button_code_y = skin_lookup_button((char *)skintype, (char *)yname);
								}

								if (button_code_x || button_code_y) {
									struct hl_skin_axis *axis = (struct hl_skin_axis *)calloc(1, sizeof(struct hl_skin_axis));

									strncpy(axis->filename, (char *)image, sizeof(axis->filename) - 1);
									axis->x = atoi((char *)pos_x);
									axis->y = atoi((char *)pos_y);
									axis->offset_x = atoi((char *)range_x);
									axis->offset_y = atoi((char *)range_y);

									if (button_code_x) {
										axis->code_x = button_code_x->code;
										axis->type_x = button_code_x->type;
										free(button_code_x);
									}
									if (button_code_y) {
										axis->code_y = button_code_y->code;
										axis->type_y = button_code_y->type;
										free(button_code_y);
									}

									skin->axes = (struct hl_skin_axis **)realloc(skin->axes, (skin->axis_count + 1) * sizeof(*skin->axes));
									skin->axes[skin->axis_count] = axis;
									skin->axis_count++;
								}

								xmlFree(image);
								xmlFree(xname);
								xmlFree(yname);
								xmlFree(pos_x);
								xmlFree(pos_y);
								xmlFree(range_x);
								xmlFree(range_y);
							}
						}
					}
					xmlFree(skinname);
					xmlFree(skintype);
				}

				hl_skins = (struct hl_skin **)realloc(hl_skins, (hl_skin_count + 1) * sizeof(*hl_skins));
				hl_skins[hl_skin_count] = skin;
				hl_skin_count++;

				xmlXPathFreeObject(result);
			}

			xmlXPathFreeContext(context);
			xmlFreeDoc(doc);

			printf("Skin file '%s' checked.\n", skin_list[z]);
		}
	}
}
