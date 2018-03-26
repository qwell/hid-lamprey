#include "version.h"
#include "settings.h"
#include "defaults.h"

#ifdef DEBUG
#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif
