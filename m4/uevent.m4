AC_DEFUN([UEVENT_CHECK_FEATURES],
[

AC_ARG_WITH([epoll],
[AS_HELP_STRING([--with-epoll],
[use epoll for event backend @<:@default=auto@:>@])], [],
[with_epoll=auto])

AC_ARG_WITH([kqueue],
[AS_HELP_STRING([--with-kqueue],
[use kqueue for event backend @<:@default=auto@:>@])], [],
[with_kqueue=auto])

AC_ARG_WITH([signalfd],
[AS_HELP_STRING([--with-signalfd],
[use signalfd for signal handling @<:@default=auto@:>@])], [],
[with_signalfd=auto])

uevent_epoll=no
uevent_kqueue=no
uevent_signalfd=no

AS_IF([test "x$with_epoll" != xno],
[AC_CHECK_HEADERS([sys/epoll.h],
[AC_SUBST([uevent_epoll], [yes])
AC_DEFINE([HAVE_EPOLL], [1], [Define if you have epoll.])
],
[if test "x$with_epoll" != xauto; then
AC_MSG_FAILURE([--with-epoll was given, but test for epoll failed])
fi])])

AS_IF([test "x$with_kqueue" != xno],
[AC_CHECK_HEADERS([sys/event.h],
[AC_SUBST([uevent_kqueue], [yes])
AC_DEFINE([HAVE_KQUEUE], [1], [Define if you have kqueue.])
],
[if test "x$with_kqueue" != xauto; then
AC_MSG_FAILURE([--with-kqueue was given, but test for kqueue failed])
fi])])

AS_IF([test "x$with_signalfd" != xno],
[AC_CHECK_HEADERS([sys/signalfd.h],
[AC_SUBST([uevent_signalfd], [yes])
AC_DEFINE([HAVE_SIGNALFD], [1], [Define if you have signalfd.])
],
[if test "x$with_signalfd" != xauto; then
AC_MSG_FAILURE([--with-signalfd was given, but test for signalfd failed])
fi])])

AM_CONDITIONAL([EPOLL], [test "x$uevent_epoll" = xyes])
AM_CONDITIONAL([KQUEUE], [test "x$uevent_kqueue" = xyes])
AM_CONDITIONAL([SIGNALFD], [test "x$uevent_signalfd" = xyes])

])
