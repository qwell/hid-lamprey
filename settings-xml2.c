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

char *settings_xml_file = "settings/settings.xml";
char *settings_xsd_file = "resources/settings.xsd";
char *mappings_xml_file = "settings/mappings.xml";
char *mappings_xsd_file = "resources/mappings.xsd";
char *shortcuts_xml_file = "settings/shortcuts.xml";
char *shortcuts_xsd_file = "resources/shortcuts.xsd";
char *emulations_xml_file = "settings/emulations.xml";
char *emulations_xsd_file = "resources/emulations.xsd";

void xml_generic_error_func(void *ctx, const char *msg, ...) {
	return;
}

char *xml_debug_node(xmlDoc *doc, xmlNode *node) {

	xmlBuffer *buffer = xmlBufferCreate();
	xmlNodeDump(buffer, doc, node, 0, 0);

	return strdup((char *)buffer->content);
}

void settings_xml_init() {
	xmlSetGenericErrorFunc(NULL, xml_generic_error_func);
}

void settings_xml_destroy() {
	xmlCleanupParser();
}

bool settings_xml_verify(xmlDoc *doc, char *xml_file, char *xsd_file) {
	xmlSchemaParserCtxt *parser_context;
	xmlSchema *schema;
	xmlSchemaValidCtxt *valid_context;

	if (!xsd_file) {
		printf("No schema file given for '%s'.  Skipping verification.\n", xml_file);
		return true;
	}

	if (!(parser_context = xmlSchemaNewParserCtxt(xsd_file))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
		return false;
	}

	if (!(schema = xmlSchemaParse(parser_context))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
		xmlSchemaFreeParserCtxt(parser_context);
		return false;
	}

	if (!(valid_context = xmlSchemaNewValidCtxt(schema))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsd_file);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(parser_context);
		return false;
	}

	if (xmlSchemaValidateDoc(valid_context, doc)) {
		printf("Settings file '%s' did not validate against %s.\n", xml_file, xsd_file);
		xmlSchemaFreeValidCtxt(valid_context);
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(parser_context);
		return false;
	}

	xmlSchemaFreeValidCtxt(valid_context);
	xmlSchemaFree(schema);
	xmlSchemaFreeParserCtxt(parser_context);

	return true;
}

void settings_xml_load_settings() {
	xmlDoc *doc;
	xmlXPathContext *context;
	xmlXPathObject *result;
	xmlNodeSet *nodeset;

	if (!hl_settings) {
		hl_settings = (struct hl_settings *)calloc(1, sizeof(hl_settings));
	}
		
	if (!(doc = xmlParseFile(settings_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", settings_xml_file);
		return;
	}

	if (!settings_xml_verify(doc, settings_xml_file, settings_xsd_file)) {
		xmlFreeDoc(doc);
		return;
	}
	
	if (!(context = xmlXPathNewContext(doc))) {
		printf("Settings file '%s' could not be loaded.\n", settings_xml_file);
		xmlFreeDoc(doc);
		return;
	}

	if (!(result = xmlXPathEvalExpression((xmlChar *)"/settings", context))) {
		printf("Settings file has no category 'settings'.\n");
		xmlXPathFreeContext(context);
		xmlFreeDoc(doc);
		return;
	}

	nodeset = result->nodesetval;
	for (int i = 0; i < nodeset->nodeNr; i++) {
		xmlNode *node = nodeset->nodeTab[i];

		for (xmlNode *cur = node->children; cur; cur = cur->next) {
			if (cur->type == XML_ELEMENT_NODE) {
				if (!xmlStrcmp(cur->name, (const xmlChar *)"device")) {
					struct device *device = (struct device *)calloc(1, sizeof(struct device));
					xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");
					xmlChar *uniqueid = xmlNodeGetContent(cur->children);

					device->name = strdup((char *)name);
					device->uniqueid = strdup((char *)uniqueid);

					devices = (struct device **)realloc(devices, (device_count + 1) * sizeof(*devices));
					devices[device_count] = device;
					device_count++;
					debug_print("Added device: %s (%s)\n", name, uniqueid);

					xmlFree(name);
					xmlFree(uniqueid);
				} else if (!xmlStrcmp(cur->name, (const xmlChar *) "skin")) {
					xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");
					xmlChar *background = xmlGetProp(cur, (const xmlChar *)"background");

					if (name && background) {
						hl_settings->skin = (struct hl_settings_skin *)calloc(1, sizeof(struct hl_settings_skin));
						hl_settings->skin->name = strdup((char *)name);
						hl_settings->skin->background = strdup((char *)background);
					}

					xmlFree(name);
					xmlFree(background);
				} else if (!xmlStrcmp(cur->name, (const xmlChar *) "option")) {
					xmlChar *name = xmlGetProp(cur, (const xmlChar *)"name");
					xmlChar *content = xmlNodeGetContent(cur->children);

					if (!xmlStrcmp(name, (xmlChar *)"deadzone_axis")) {
						hl_settings->deadzone_axis = atof((char *)content);
					} else if (!xmlStrcmp(name, (xmlChar *)"deadzone_hat")) {
						hl_settings->deadzone_hat = atof((char *)content);
					}

					xmlFree(name);
					xmlFree(content);
				}
			}
		}
	}

	xmlXPathFreeObject(result);
	xmlXPathFreeContext(context);
	xmlFreeDoc(doc);

	printf("Settings file '%s loaded.\n", settings_xml_file);
}

void settings_xml_load_mappings() {
	xmlDoc *doc;
	xmlXPathContext *context;
	xmlXPathObject *result;
	xmlNodeSet *nodeset;

	if (!(doc = xmlParseFile(mappings_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", mappings_xml_file);
		return;
	}

	/*
	if (!settings_xml_verify(doc, mappings_xml_file, mappings_xsd_file)) {
		xmlFreeDoc(doc);
		return;
	}
	*/

	if (!(context = xmlXPathNewContext(doc))) {
		printf("Settings file '%s' could not be loaded.\n", mappings_xml_file);
		xmlFreeDoc(doc);
		return;
	}

	if (!(result = xmlXPathEvalExpression((xmlChar *)"/mappings/mapping", context))) {
		printf("Settings file has no category 'mapping'.\n");
		xmlXPathFreeContext(context);
		xmlFreeDoc(doc);
		return;
	}

	nodeset = result->nodesetval;
	for (int i = 0; i < nodeset->nodeNr; i++) {
		xmlNode *node = nodeset->nodeTab[i];

		xmlChar *device = xmlGetProp(node, (const xmlChar *)"device");
		xmlChar *rawname = xmlGetProp(node, (const xmlChar *)"rawname");
		xmlChar *maptype = xmlGetProp(node, (const xmlChar *)"maptype");
		xmlChar *mapcode = xmlGetProp(node, (const xmlChar *)"mapcode");

		if (struct button_code *button_code = hl_controller_get_code_by_name((char *)maptype, (char *)mapcode)) {
			struct input_mapping *dinput_mapping;

			dinput_mapping = (struct input_mapping *)malloc(sizeof(struct input_mapping));
			dinput_mapping->mapvalue = 0;
			dinput_mapping->builtin = false;
			dinput_mapping->device = strdup((char *)device);
			dinput_mapping->rawname = strdup((char *)rawname);
			dinput_mapping->maptype = button_code->type;
			dinput_mapping->mapcode = button_code->code;

			input_mappings = (struct input_mapping **)realloc(input_mappings, (input_mapping_count + 1) * sizeof(*input_mappings));
			input_mappings[input_mapping_count++] = dinput_mapping;
		}

		xmlFree(device);
		xmlFree(rawname);
		xmlFree(maptype);
		xmlFree(mapcode);
	}

	xmlXPathFreeObject(result);
	xmlXPathFreeContext(context);
	xmlFreeDoc(doc);

	printf("Settings file '%s loaded.\n", mappings_xml_file);
}

void settings_xml_load_shortcuts() {
	xmlDoc *doc;
	xmlXPathContext *context;
	xmlXPathObject *result;
	xmlNodeSet *nodeset;

	if (!(doc = xmlParseFile(shortcuts_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", shortcuts_xml_file);
		return;
	}

	if (!settings_xml_verify(doc, shortcuts_xml_file, shortcuts_xsd_file)) {
		xmlFreeDoc(doc);
		return;
	}

	if (!(context = xmlXPathNewContext(doc))) {
		printf("Settings file '%s' could not be loaded.\n", shortcuts_xml_file);
		xmlFreeDoc(doc);
		return;
	}

	if (!(result = xmlXPathEvalExpression((xmlChar *)"/shortcuts/shortcut", context))) {
		printf("Settings file has no category 'shortcut'.\n");
		xmlXPathFreeContext(context);
		xmlFreeDoc(doc);
		return;
	}

	nodeset = result->nodesetval;
	for (int i = 0; i < nodeset->nodeNr; i++) {
		xmlNode *node = nodeset->nodeTab[i];

		struct shortcut *shortcut = (struct shortcut *)calloc(1, sizeof(struct shortcut));
		xmlChar *shortcut_name = xmlGetProp(node, (const xmlChar *)"name");
		xmlChar *shortcut_type = xmlGetProp(node, (const xmlChar *)"type");

		shortcut->name = strdup((char *)shortcut_name);
		if (!xmlStrcmp(shortcut_type, (const xmlChar *)"simultaneous")) {
			shortcut->type = simultaneous;
		} else if (!xmlStrcmp(shortcut_type, (const xmlChar *)"consecutive")) {
			shortcut->type = consecutive;
		}

		xmlFree(shortcut_name);
		xmlFree(shortcut_type);

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
					struct button_code *button_code;

					xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
					xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");
					xmlChar *trigger_low = xmlGetProp(cur, (const xmlChar *)"trigger_low");
					xmlChar *trigger_high = xmlGetProp(cur, (const xmlChar *)"trigger_high");

					if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
						struct shortcut_button *button = (struct shortcut_button *)calloc(1, sizeof(struct shortcut_button));
						button->code = button_code->code;
						button->type = button_code->type;

						if (xmlStrlen(trigger_low) > 0) {
							button->trigger_low = atol((char *)trigger_low);
						} else if (xmlStrlen(trigger_high) > 0) {
							button->trigger_high = atol((char *)trigger_high);
						}

						shortcut->buttons = (struct shortcut_button **)realloc(shortcut->buttons, (shortcut->button_count + 1) * sizeof(*shortcut->buttons));
						shortcut->buttons[shortcut->button_count] = button;
						shortcut->button_count++;
					}

					xmlFree(code);
					xmlFree(type);
					xmlFree(trigger_low);
					xmlFree(trigger_high);
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

	xmlXPathFreeObject(result);
	xmlXPathFreeContext(context);
	xmlFreeDoc(doc);

	printf("Settings file '%s loaded.\n", shortcuts_xml_file); }

void settings_xml_load_emulations() {
	xmlDoc *doc;
	xmlXPathContext *context;
	xmlXPathObject *result;
	xmlNodeSet *nodeset;

	if (!(doc = xmlParseFile(emulations_xml_file))) {
		printf("Settings file '%s' is missing or invalid.\n", emulations_xml_file);
		return;
	}

	if (!settings_xml_verify(doc, emulations_xml_file, emulations_xsd_file)) {
		xmlFreeDoc(doc);
		return;
	}

	if (!(context = xmlXPathNewContext(doc))) {
		printf("Settings file '%s' could not be loaded.\n", emulations_xml_file);
		xmlFreeDoc(doc);
		return;
	}

	if (!(result = xmlXPathEvalExpression((xmlChar *)"/emulations/emulation", context))) {
		printf("Settings file has no category 'emulation'.\n");
		xmlXPathFreeContext(context);
		xmlFreeDoc(doc);
		return;
	}
	
	nodeset = result->nodesetval;
	for (int i = 0; i < nodeset->nodeNr; i++) {
		struct emulation *emulation = (struct emulation *)calloc(1, sizeof(struct emulation));

		xmlNode *node = nodeset->nodeTab[i];

		for (xmlNode *cur = node->children; cur; cur = cur->next) {
			if (cur->type == XML_ELEMENT_NODE) {
				if (!xmlStrcmp(cur->name, (const xmlChar *)"in") || !xmlStrcmp(cur->name, (const xmlChar *)"out")) {
					struct button_code *button_code;

					xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
					xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");

					if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
						if (!xmlStrcmp(cur->name, (const xmlChar *)"in")) {
							struct button_trigger *button_trigger = (struct button_trigger *)calloc(1, sizeof(struct button_trigger));
								
							xmlChar *trigger_low = xmlGetProp(cur, (const xmlChar *)"trigger_low");
							xmlChar *trigger_high = xmlGetProp(cur, (const xmlChar *)"trigger_high");

							button_trigger->code = button_code->code;
							button_trigger->type = button_code->type;
							if (xmlStrlen(trigger_low) > 0) {
								button_trigger->trigger_low = atol((char *)trigger_low);
							} else if (xmlStrlen(trigger_high) > 0) {
								button_trigger->trigger_high = atol((char *)trigger_high);
							} else {
								button_trigger->trigger_low = 0;
								button_trigger->trigger_high = 0;
							}
							emulation->in = button_trigger;
							xmlFree(trigger_low);
							xmlFree(trigger_high);
						} else if (!xmlStrcmp(cur->name, (const xmlChar *)"out")) {
							struct button_trigger_out *button_trigger_out = (struct button_trigger_out *)calloc(1, sizeof(struct button_trigger_out));

							xmlChar *trigger = xmlGetProp(cur, (const xmlChar *)"trigger");

							button_trigger_out->code = button_code->code;
							button_trigger_out->type = button_code->type;
							if (xmlStrlen(trigger) > 0) {
								button_trigger_out->trigger = atol((char *)trigger);
							} else {
								button_trigger_out->trigger = 0;
							}
							emulation->out = button_trigger_out;
							xmlFree(trigger);
						}
					}

					xmlFree(code);
					xmlFree(type);
				}
			}
		}
		if (emulation->in && emulation->out) {
			emulations = (struct emulation **)realloc(emulations, (emulation_count + 1) * sizeof(*emulations));
			emulations[emulation_count] = emulation;
			emulation_count++;

			debug_print("Added emulation: in %d / %d (%d), out %d / %d (%d)\n",
				emulation->in->type, emulation->in->code, emulation->in->triggervalue,
				emulation->out->type, emulation->out->code, emulation->out->triggervalue);
		} else {
			if (emulation->in) {
				free(emulation->in);
			} else if (emulation->out) {
				free(emulation->out);
			}
			free(emulation);
		}
	}

	xmlXPathFreeObject(result);
	xmlXPathFreeContext(context);
	xmlFreeDoc(doc);

	printf("Settings file '%s' loaded.\n", emulations_xml_file);
}

void settings_xml_save_mappings() {
	xmlDoc *doc;
	xmlNode *mappings;

	doc = xmlNewDoc((xmlChar *)"1.0");
	mappings = xmlNewNode(NULL, (xmlChar *)"mappings");
	xmlDocSetRootElement(doc, mappings);

	for (int i = 0; i < input_mapping_count; i++) {
		struct input_mapping *input_mapping = input_mappings[i];

		if (!input_mapping) {
			continue;
		}

		if (input_mapping->builtin) {
			continue;
		}

		for (int j = 0; j < codelookup_count / sizeof(*codelookups); j++) {
			struct codelookup code = codelookups[j];
			if (code.typestr && code.type == input_mapping->maptype) {
				for (int k = 0; k < sizeof(code.codes) / sizeof(*code.codes); k++) {
					if (code.codes[k].codestr && code.codes[k].code == input_mapping->mapcode) {
						xmlNode *child;

						char maptype[32];
						char mapcode[32];

						snprintf(maptype, sizeof(maptype) - 1, "%s", code.typestr);
						snprintf(mapcode, sizeof(mapcode) - 1, "%s", code.codes[k].codestr);

						child = xmlNewChild(mappings, NULL, (xmlChar *)"mapping", NULL);
						xmlNewProp(child, (xmlChar *)"device", (xmlChar *)input_mapping->device);
						xmlNewProp(child, (xmlChar *)"rawname", (xmlChar *)input_mapping->rawname);
						xmlNewProp(child, (xmlChar *)"maptype", (xmlChar *)maptype);
						xmlNewProp(child, (xmlChar *)"mapcode", (xmlChar *)mapcode);
					}
				}
			}
		}
	}
	xmlSaveFormatFileEnc(mappings_xml_file, doc, "UTF-8", 1);
}
