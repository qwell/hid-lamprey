#include <stdio.h>
#include <xdo.h>

#include "include/xdo.h"

void xdo_init() {
	xdo_t* xdo = xdo_new(NULL);
	printf("libxdo module version: %s\n", xdo_version());

	xdo_free(xdo);
}
