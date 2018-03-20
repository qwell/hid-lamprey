#include <libevdev/libevdev.h>

//#define LOW_KEY BTN_MISC
//#define HIGH_KEY BTN_THUMBR
#define LOW_KEY KEY_ESC
#define HIGH_KEY KEY_MAX

#define LOW_AXIS ABS_X
#define HIGH_AXIS ABS_BRAKE

#define LOW_HAT ABS_HAT0X
#define HIGH_HAT ABS_HAT3Y

void gamepad_start();
