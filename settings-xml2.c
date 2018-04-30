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

/* Fuck everything about libxml2. */

void xml_generic_error_func(void *ctx, const char *msg, ...) {
	return;
}

char *xml_debug_node(xmlDoc *doc, xmlNode *node) {

	xmlBuffer *buffer = xmlBufferCreate();
	xmlNodeDump(buffer, doc, node, 0, 0);

	return strdup((char *)buffer->content);
}

void settings_xml_load_settings(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/settings/devices/device";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'devices'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			xmlNode *node = nodeset->nodeTab[i];

			struct device *device = (struct device *)calloc(1, sizeof(struct device));
			xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
			xmlChar *uniqueid = xmlNodeGetContent(node->children);

			device->name = strdup((char *)name);
			device->uniqueid = strdup((char *)uniqueid);

			devices = (struct device **)realloc(devices, (device_count + 1) * sizeof(*devices));
			devices[device_count] = device;
			device_count++;
			debug_print("Added device: %s (%s)\n", name, uniqueid);

			xmlFree(name);
			xmlFree(uniqueid);
		}
		xmlXPathFreeObject(result);
	}
}

void settings_xml_load_shortcuts(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/shortcuts/shortcut";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'shortcuts'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			xmlNode *node = nodeset->nodeTab[i];

			struct shortcut *shortcut = (struct shortcut *)calloc(1, sizeof(struct shortcut));
			xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
			xmlChar *type = xmlGetProp(node, (const xmlChar *)"type");

			shortcut->name = strdup((char *)name);
			if (!xmlStrcmp(type, (const xmlChar *)"simultaneous")) {
				shortcut->type = simultaneous;
			} else if (!xmlStrcmp(type, (const xmlChar *)"consecutive")) {
				shortcut->type = consecutive;
			}

			xmlFree(name);
			xmlFree(type);

			for (xmlNode *cur = node->children; cur; cur = cur->next) {
				if (cur->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(cur->name, (const xmlChar *)"device")) {
						xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");

						for (int i = 0; i < device_count; i++) {
							if (!xmlStrcmp(name, (const xmlChar *)devices[i]->name)) {
								shortcut->devices = (char **)realloc(shortcut->devices, (shortcut->device_count + 1) * sizeof(*shortcut->devices));
								shortcut->devices[shortcut->device_count] = strdup(devices[i]->uniqueid);
								shortcut->device_count++;
							}
						}

						xmlFree(name);
					} else if (!xmlStrcmp(cur->name, (const xmlChar *)"button")) {
						struct shortcut_button *button = (struct shortcut_button *)calloc(1, sizeof(struct shortcut_button));

						for (xmlNode *tchild = cur->children; tchild; tchild = tchild->next) {
							if (tchild->type == XML_ELEMENT_NODE) {
								/* <trigger/> */
								struct button_code *button_code;

								xmlChar *code = xmlGetProp(tchild, (const xmlChar *)"code");
								xmlChar *type = xmlGetProp(tchild, (const xmlChar *)"type");
								xmlChar *trigger = xmlGetProp(tchild, (const xmlChar *)"trigger");

								if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
									struct button_trigger *button_trigger = (struct button_trigger *)calloc(1, sizeof(struct button_trigger));
									button_trigger->code = button_code->code;
									button_trigger->type = button_code->type;
									if (xmlStrlen(trigger) > 0) {
										button_trigger->triggervalue = atol((char *)trigger);
									} else {
										button_trigger->triggervalue = 0;
									}

									button->triggers = (struct button_trigger **)realloc(button->triggers, (button->trigger_count + 1) * sizeof(*button->triggers));
									button->triggers[button->trigger_count] = button_trigger;
									button->trigger_count++;
								}

								xmlFree(code);
								xmlFree(type);
								xmlFree(trigger);
							}
						}

						shortcut->buttons = (struct shortcut_button **)realloc(shortcut->buttons, (shortcut->button_count + 1) * sizeof(*shortcut->buttons));
						shortcut->buttons[shortcut->button_count] = button;
						shortcut->button_count++;
					} else if (!xmlStrcmp(cur->name, (const xmlChar *)"function")) {
/*
struct shortcut {
	void (*function) ();
	void *args;
};
*/
					}
				}
			}

			shortcuts = (struct shortcut **)realloc(shortcuts, (shortcut_count + 1) * sizeof(*shortcuts));
			shortcuts[shortcut_count] = shortcut;
			shortcut_count++;

			debug_print("Added shortcut: %s\n", shortcut->name);
		}
	}
}

void settings_xml_load_remaps(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/remaps/remap";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'remaps'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			struct remap *remap = (struct remap *)calloc(1, sizeof(struct remap));

			xmlNode *node = nodeset->nodeTab[i];

			for (xmlNode *cur = node->children; cur; cur = cur->next) {
				if (cur->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(cur->name, (const xmlChar *)"in") || !xmlStrcmp(cur->name, (const xmlChar *)"out")) {
						struct button_code *button_code;

						xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
						xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");
						xmlChar *trigger = xmlGetProp(cur, (const xmlChar *)"trigger");

						if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
							struct button_trigger *button_trigger = (struct button_trigger *)calloc(1, sizeof(struct button_trigger));
							button_trigger->code = button_code->code;
							button_trigger->type = button_code->type;
							if (xmlStrlen(trigger) > 0) {
								button_trigger->triggervalue = atol((char *)trigger);
							} else {
								button_trigger->triggervalue = 0;
							}
							if (!xmlStrcmp(cur->name, (const xmlChar *)"in")) {
								remap->in = button_trigger;
							} else if (!xmlStrcmp(cur->name, (const xmlChar *)"out")) {
								remap->out = button_trigger;
							}
						}

						xmlFree(code);
						xmlFree(type);
						xmlFree(trigger);
					}
				}
			}
			if (remap->in && remap->out) {
				remaps = (struct remap **)realloc(remaps, (remap_count + 1) * sizeof(*remaps));
				remaps[remap_count] = remap;
				remap_count++;

				debug_print("Added remap: in %d / %d (%d), out %d / %d (%d)\n",
					remap->in->type, remap->in->code, remap->in->triggervalue,
					remap->out->type, remap->out->code, remap->out->triggervalue);
			} else {
				if (remap->in) {
					free(remap->in);
				} else if (remap->out) {
					free(remap->out);
				}
				free(remap);
			}
		}
		xmlXPathFreeObject(result);
	}
}

bool settings_xml_verify(xmlDoc *doc, char *xml_file, char *xsd_file) {
	if (!xsd_file) {
		printf("No schema file given for '%s'.  Skipping verification.\n", xml_file);
	} else {
		xmlSchemaParserCtxt *parser_context;
		xmlSchema *schema;
		xmlSchemaValidCtxt *valid_context;

		if (!(parser_context = xmlSchemaNewParserCtxt(xsd_file))) {
			printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
			xmlFreeDoc(doc);
			return false;
		}
		if (!(schema = xmlSchemaParse(parser_context))) {
			printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
			xmlSchemaFreeParserCtxt(parser_context);
			xmlFreeDoc(doc);
			return false;
		}
		if (!(valid_context = xmlSchemaNewValidCtxt(schema))) {
			printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
			xmlSchemaFreeParserCtxt(parser_context);
			xmlSchemaFree(schema);
			xmlFreeDoc(doc);
			return false;
		}
		if (xmlSchemaValidateDoc(valid_context, doc)) {
			printf("Settings file '%s' did not validate against %s.\n", xml_file, xsd_file);
			xmlSchemaFreeParserCtxt(parser_context);
			xmlSchemaFree(schema);
			xmlSchemaFreeValidCtxt(valid_context);
			xmlFreeDoc(doc);
			return false;
		}
		xmlSchemaFreeParserCtxt(parser_context);
		xmlSchemaFree(schema);
		xmlSchemaFreeValidCtxt(valid_context);
	}

	return true;
}

void hl_settings_xml_load() {
	char *settings_xml_file = "settings/settings.xml";
	char *settings_xsd_file = "settings/settings.xsd";

	char *shortcuts_xml_file = "settings/shortcuts.xml";
	char *shortcuts_xsd_file = "settings/shortcuts.xsd";

	char *remaps_xml_file = "settings/remaps.xml";
	char *remaps_xsd_file = "settings/remaps.xsd";

	xmlDoc *doc;

	xmlSetGenericErrorFunc(NULL, xml_generic_error_func);

	if (!(doc = xmlParseFile(settings_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", settings_xml_file);
		return;
	} else {
		if (settings_xml_verify(doc, settings_xml_file, settings_xsd_file)) {
			xmlXPathContext *context;

			if (!(context = xmlXPathNewContext(doc))) {
				printf("Settings file '%s' could not be loaded.\n", settings_xml_file);
				xmlFreeDoc(doc);
				return;
			}

			settings_xml_load_settings(context);

			xmlFree(context);
		}
		xmlFreeDoc(doc);
	}

	if (!(doc = xmlParseFile(shortcuts_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", shortcuts_xml_file);
		return;
	} else {
		if (settings_xml_verify(doc, shortcuts_xml_file, shortcuts_xsd_file)) {
			xmlXPathContext *context;

			if (!(context = xmlXPathNewContext(doc))) {
				printf("Settings file '%s' could not be loaded.\n", shortcuts_xml_file);
				xmlFreeDoc(doc);
				return;
			}

			settings_xml_load_shortcuts(context);

			xmlFree(context);
		}
		xmlFreeDoc(doc);
	}

	if (!(doc = xmlParseFile(remaps_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", remaps_xml_file);
		return;
	} else {
		if (settings_xml_verify(doc, remaps_xml_file, remaps_xsd_file)) {
			xmlXPathContext *context;

			if (!(context = xmlXPathNewContext(doc))) {
				printf("Settings file '%s' could not be loaded.\n", remaps_xml_file);
				xmlFreeDoc(doc);
				return;
			}

			settings_xml_load_remaps(context);

			xmlFree(context);
		}
		xmlFreeDoc(doc);
	}

	xmlCleanupParser();
}

void hl_settings_xml_save() {
}
