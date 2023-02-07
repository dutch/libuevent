AC_INIT([libuevent],
[m4_esyscmd([build-aux/git-version-gen .tarball-version])],
[https://github.com/dutch/libuevent/issues], [],
[https://github.com/dutch/libuevent])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT
AC_PROG_CC
UEVENT_CHECK_FEATURES
PKG_INSTALLDIR
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile libuevent.pc])
AC_OUTPUT
