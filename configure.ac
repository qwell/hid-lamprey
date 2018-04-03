AC_PREREQ([2.69])
AC_CONFIG_MACRO_DIR([autoconf])

AC_INIT([lamprey], [0.0.1])

AC_CONFIG_FILES([config.out])
AC_CONFIG_HEADERS([include/config.h])

AC_CANONICAL_HOST

AC_PROG_CC
AX_CHECK_GNU_MAKE([
	AC_SUBST([GNU_MAKE], [$_cv_gnu_make_command])
])

AX_PTHREAD

AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T
AC_FUNC_MALLOC

PKG_PROG_PKG_CONFIG()

LOCAL_WITH_HAVE([CLI], [cli])
LOCAL_WITH_PKG([EVDEV], [evdev], [], [libevdev])
LOCAL_WITHOUT_PKG([GTK3], [gtk3], [ (for output display)], [gtk+-3.0])
LOCAL_WITHOUT_LIB([XDO], [xdo], [], [xdo_new])
LOCAL_WITH_PKG([XML2], [xml2], [], [libxml-2.0])

AC_OUTPUT()
