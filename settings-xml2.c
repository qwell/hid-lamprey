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

//TODO Save devices somewhere.
void settings_xml_load_devices(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/settings/devices/device";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'devices'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			xmlNode *node = nodeset->nodeTab[i];
			xmlChar *name = xmlGetProp(node, (const xmlChar *)"name");
			xmlChar *device = xmlNodeGetContent(node->children);

			printf("Device %d: %s = %s\n", i, name, device);

			xmlFree(name);
			xmlFree(device);
		}
		xmlXPathFreeObject(result);
	}
}

void settings_xml_load_shortcuts(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/settings/shortcuts/shortcut";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'shortcuts'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			xmlNode *node = nodeset->nodeTab[i];

			struct shortcut *shortcut = calloc(1, sizeof(struct shortcut));
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
/*
struct shortcut {
	void (*function) ();
	void *args;
};
*/
			for (xmlNode *cur = node->children; cur; cur = cur->next) {
				if (cur->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(cur->name, (const xmlChar *)"devices")) {
						for (xmlNode *child = cur->children; child; child = child->next) {
							if (child->type == XML_ELEMENT_NODE) {
								xmlChar *name = xmlGetProp(child, (const xmlChar *)"name");

								shortcut->devices = realloc(shortcut->devices, (shortcut->device_count + 1) * sizeof(*shortcut->devices));
								shortcut->devices[shortcut->device_count] = strdup((char *)name);
								shortcut->device_count++;

//TODO printf("Device with name '%s' does not exist.\n", name);
								xmlFree(name);
							}
						}
					} else if (!xmlStrcmp(cur->name, (const xmlChar *)"buttons")) {
						for (xmlNode *bchild = cur->children; bchild; bchild = bchild->next) {
							if (bchild->type == XML_ELEMENT_NODE) {
								/* <button/> */
								struct button *buttons = calloc(1, sizeof(struct button));

								for (xmlNode *tchild = bchild->children; tchild; tchild = tchild->next) {
									if (tchild->type == XML_ELEMENT_NODE) {
										/* <trigger/> */
										struct button_code *button_code;

										xmlChar *code = xmlGetProp(tchild, (const xmlChar *)"code");
										xmlChar *type = xmlGetProp(tchild, (const xmlChar *)"type");
										xmlChar *trigger = xmlGetProp(tchild, (const xmlChar *)"trigger");

										if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
											struct button_trigger *button_trigger = calloc(1, sizeof(struct button_trigger));
											button_trigger->code = button_code->code;
											button_trigger->type = button_code->type;
											if (xmlStrlen(trigger) > 0) {
												button_trigger->triggervalue = atol((char *)trigger);
											} else {
												button_trigger->triggervalue = 0;
											}

											buttons->triggers = realloc(buttons->triggers, (buttons->trigger_count + 1) * sizeof(*buttons->triggers));
											buttons->triggers[buttons->trigger_count] = button_trigger;
											buttons->trigger_count++;
										}

										xmlFree(code);
										xmlFree(type);
										xmlFree(trigger);
									}

								}

								shortcut->buttons = realloc(shortcut->buttons, (shortcut->button_count + 1) * sizeof(*shortcut->buttons));
								shortcut->buttons[shortcut->button_count] = buttons;
								shortcut->button_count++;
							}
						}
					} else if (!xmlStrcmp(cur->name, (const xmlChar *)"function")) {
					}
				}
			}

			shortcuts = realloc(shortcuts, (shortcut_count + 1) * sizeof(*shortcuts));
			shortcuts[shortcut_count] = shortcut;
			shortcut_count++;

			printf("Added shortcut: %s\n", shortcut->name);
		}
	}
}

void settings_xml_load_remaps(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"/settings/remaps/remap";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'remaps'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			struct remap *remap = calloc(1, sizeof(struct remap));

			xmlNode *node = nodeset->nodeTab[i];

			for (xmlNode *cur = node->children; cur; cur = cur->next) {
				if (cur->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(cur->name, (const xmlChar *)"in") || !xmlStrcmp(cur->name, (const xmlChar *)"out")) {
						struct button_code *button_code;

						xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
						xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");
						xmlChar *trigger = xmlGetProp(cur, (const xmlChar *)"trigger");

						if ((button_code = hl_controller_get_code_by_name((char *)type, (char *)code))) {
							struct button_trigger *button_trigger = calloc(1, sizeof(struct button_trigger));
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
				remaps = realloc(remaps, (remap_count + 1) * sizeof(*remaps));
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

void hl_settings_xml_load() {
	char *xmlfilename = "settings.xml";
	char *xsdfilename = "settings.xsd";
	xmlDoc *doc;
	xmlSchemaParserCtxt *parser_context;
	xmlSchema *schema;
	xmlSchemaValidCtxt *valid_context;
	xmlXPathContext *context;

	xmlSetGenericErrorFunc(NULL, xml_generic_error_func);

	if (!(doc = xmlParseFile(xmlfilename))) {
		printf("Settings file '%s' is missing or invalid.\n", xmlfilename);
		return;
	}

	if (!(parser_context = xmlSchemaNewParserCtxt(xsdfilename))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsdfilename);
		xmlFreeDoc(doc);
		return;
	}
	if (!(schema = xmlSchemaParse(parser_context))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsdfilename);
		xmlSchemaFreeParserCtxt(parser_context);
		xmlFreeDoc(doc);
		return;
	}
	if (!(valid_context = xmlSchemaNewValidCtxt(schema))) {
		printf("Settings file schema '%s' could not be loaded.\n", xsdfilename);
		xmlSchemaFreeParserCtxt(parser_context);
		xmlSchemaFree(schema);
		xmlFreeDoc(doc);
		return;
	}
	if (xmlSchemaValidateDoc(valid_context, doc)) {
		printf("Settings file '%s' did not validate against %s.\n", xmlfilename, xsdfilename);
		xmlSchemaFreeParserCtxt(parser_context);
		xmlSchemaFree(schema);
		xmlSchemaFreeValidCtxt(valid_context);
		xmlFreeDoc(doc);
		return;
	}
	xmlSchemaFreeParserCtxt(parser_context);
	xmlSchemaFree(schema);
	xmlSchemaFreeValidCtxt(valid_context);

	if (!(context = xmlXPathNewContext(doc))) {
		printf("Settings file '%s' could not be loaded.\n", xmlfilename);
		xmlFreeDoc(doc);
		return;
	}

	settings_xml_load_devices(context);
	settings_xml_load_shortcuts(context);
	settings_xml_load_remaps(context);

	printf("Settings file '%s' loaded successfully.\n", xmlfilename);

	xmlFree(context);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

void hl_settings_xml_save() {
}
