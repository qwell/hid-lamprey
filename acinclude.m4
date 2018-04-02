dnl LOCAL_CHECK_GNU_MAKE
AC_DEFUN([LOCAL_CHECK_GNU_MAKE], [
	AC_CACHE_CHECK([for GNU make], [_cv_gnu_make_command], [
		_cv_gnu_make_command=""
		for a in "$MAKE" make gmake gnumake; do
			if test -z "$a"; then continue; fi
			if "$a" --version 2> /dev/null | grep GNU 2>&1 > /dev/null; then
				_cv_gnu_make_command=$a
				break;
			fi
		done
	])
	AC_SUBST([GNU_MAKE], [$_cv_gnu_make_command])
])

dnl LOCAL_SUBST_DEFINE(variable, value)
AC_DEFUN([LOCAL_SUBST_DEFINE], [
	AC_DEFINE([$1], [$2])
	AC_SUBST([$1], [$2])
])

dnl LOCAL_IF_WITH(module, yes-action, no-action, else-action)
AC_DEFUN([LOCAL_IF_WITH], [
	AS_IF(
		[test "x$with_$1" = "xyes"],
		[$2],
		[test "x$with_$1" = "xno"],
		[$3],
		[$4]
	)
])

dnl LOCAL_WITH(module, name, extra-desc)
AC_DEFUN([LOCAL_WITH], [
dnl	LOCAL_SUBST_DEFINE([HAVE_$1], [])
	AC_SUBST([$1_CFLAGS])
	AC_SUBST([$1_LIBS])

	AC_ARG_WITH([$2], AS_HELP_STRING([--with-$2], [Enable $1 support$3]), [with_$1=${withval}], [with_$1=])
])

dnl LOCAL_WITH_HAVE(module, name, extra-desc)
AC_DEFUN([LOCAL_WITH_HAVE], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [LOCAL_SUBST_DEFINE([HAVE_$1]), [1]], [], [LOCAL_SUBST_DEFINE([HAVE_$1], [1])])
])

dnl LOCAL_WITHOUT_HAVE(module, name, extra-desc)
AC_DEFUN([LOCAL_WITHOUT_HAVE], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [LOCAL_SUBST_DEFINE([HAVE_$1], [1])], [], [])
])

dnl LOCAL_WITH_PKG(module, name, extra-desc, pkg-config)
AC_DEFUN([LOCAL_WITH_PKG], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [
		PKG_CHECK_MODULES([$1], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
		], [
			AC_MSG_FAILURE([--with-$2 was given, but cannot be used.])
		])
	], [
	], [
		PKG_CHECK_MODULES([$1], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
		], [
		])
	])
])

dnl LOCAL_WITHOUT_PKG(module, name, pkg-config, extra-desc)
AC_DEFUN([LOCAL_WITHOUT_PKG], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [
		PKG_CHECK_MODULES([$1], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
		], [
			AC_MSG_FAILURE([--with-$2 was given, but cannot be used.])
		])
	])
])

dnl LOCAL_WITH_LIB(module, name, extra-desc, function, other-libraries)
AC_DEFUN([LOCAL_WITH_LIB], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [
		AC_CHECK_LIB([$2], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
			AC_SUBST([$1_LIBS], [-l$2 $5])
		], [
			AC_MSG_FAILURE([--with-$2 was given, but cannot be used.])
		])
	], [
	], [
		AC_CHECK_LIB([$2], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
			AC_SUBST([$1_LIBS], [-l$2 $5])
		])
	])
])

dnl LOCAL_WITHOUT_LIB(module, name, extra-desc, function, other-libraries)
AC_DEFUN([LOCAL_WITHOUT_LIB], [
	LOCAL_WITH([$1], [$2], [$3])
	LOCAL_IF_WITH([$1], [
		AC_CHECK_LIB([$2], [$4], [
			LOCAL_SUBST_DEFINE([HAVE_$1], [1])
			AC_SUBST([$1_LIBS], [-l$2 $5])
		], [
			AC_MSG_FAILURE([--with-$2 was given, but cannot be used.])
		])
	])
])
