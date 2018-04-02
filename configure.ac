AC_INIT([lamprey], [0.0.1])

AC_CONFIG_FILES([config.out])
AC_CONFIG_HEADERS([include/config.h])

AC_PREREQ([2.69])

AC_CANONICAL_HOST

PKG_PROG_PKG_CONFIG()

LOCAL_WITH_HAVE([CLI], [cli])
LOCAL_WITH_PKG([EVDEV], [evdev], [], [libevdev])
LOCAL_WITH_LIB([XML2], [xml2], [], [xmlNewDoc])
LOCAL_WITHOUT_PKG([GTK3], [gtk3], [ (for output display)], [gtk+-3.0])
LOCAL_WITHOUT_LIB([XDO], [xdo], [], [xdo_new])

AC_OUTPUT()
