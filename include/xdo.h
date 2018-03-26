#include <xdo.h>

struct hl_xdo {
	xdo_t *xdo;
};

void *hl_xdo_init();
int hl_xdo_getactive(xdo_t *xdo, Window *window_ret);
int hl_xdo_search(xdo_t *xdo, char *window_name, Window **window_ret, unsigned int *nwindows);
int hl_xdo_activate(xdo_t *xdo, Window window);
int hl_xdo_keys(xdo_t *xdo, Window window, const char *keyseq);
