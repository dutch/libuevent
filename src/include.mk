include_HEADERS = %D%/uevent.h
lib_LTLIBRARIES = %D%/libuevent.la
%C%_libuevent_la_SOURCES = %D%/uevent.c %D%/uevent.h %D%/private.h
%C%_libuevent_la_LDFLAGS = -version-info 0:1:0
if EPOLL
%C%_libuevent_la_SOURCES += %D%/epoll.c
endif
if SIGNALFD
%C%_libuevent_la_SOURCES += %D%/signalfd.c
endif
if KQUEUE
%C%_libuevent_la_SOURCES += %D%/kqueue.c
endif
