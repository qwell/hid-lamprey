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

void settings_xml_load_devices(xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"//devices/device";
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

void settings_xml_load_remaps(xmlDoc *doc, xmlXPathContext *context) {
	xmlChar *xpath = (xmlChar *)"//remaps/remap";
	xmlXPathObject *result;

	if (!(result = xmlXPathEvalExpression(xpath, context))) {
		printf("Settings file has no category 'remaps'.\n");
	} else {
		xmlNodeSet *nodeset = result->nodesetval;
		for (int i = 0; i < nodeset->nodeNr; i++) {
			xmlNode *node = nodeset->nodeTab[i];

			debug_print("dump: %s\n", xml_debug_node(doc, node));

			printf("Remap %d\n", i);

			for (xmlNode *cur = node->children; cur; cur = cur->next) {
				if (cur->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(cur->name, (const xmlChar *)"in")) {
						xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
						xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");

						printf("In: %s, %s\n", code, type);

						xmlFree(code);
						xmlFree(type);
					} else if (!xmlStrcmp(cur->name, (const xmlChar *)"out")) {
						xmlChar *code = xmlGetProp(cur, (const xmlChar *)"code");
						xmlChar *type = xmlGetProp(cur, (const xmlChar *)"type");
						xmlChar *trigger = xmlGetProp(cur, (const xmlChar *)"trigger");

						printf("Out: %s, %s, %s\n", code, type, trigger);

						xmlFree(code);
						xmlFree(type);
						xmlFree(trigger);
					}
				}
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
	settings_xml_load_remaps(doc, context);

	printf("Settings file '%s' loaded successfully.\n", xmlfilename);

	xmlFree(context);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

void hl_settings_xml_save() {
}
