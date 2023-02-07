/*
 * Copyright (C) 2023 Dutch Lamberson.
 *
 * This file is part of the libuevent.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "uevent.h"
#include "private.h"

void
uevent_initialize(void)
{
#if !(defined(HAVE_EPOLL)||defined(HAVE_KQUEUE))
  _posix_initialize();
#endif

#ifdef HAVE_EPOLL
  _epoll_initialize();
#endif

#ifdef HAVE_SIGNALFD
  _signalfd_initialize();
#endif
}

#if !(defined(HAVE_EPOLL)||defined(HAVE_KQUEUE))

#include <stdlib.h>
#include <sys/select.h>

struct _posix_thunk
{
  void (*func)(void *);
  void *arg;
};

int _posix_nfds;
int _posix_fds[100];
struct _posix_thunk _posix_thunks[1024];

void
_posix_initialize(void)
{
  _posix_nfds = 0;
}

void
uevent_add_fildes(int fd, void (*func)(void *), void *arg)
{
  _posix_fds[_posix_nfds++] = fd;
  _posix_thunks[fd].func = func;
  _posix_thunks[fd].arg = arg;
}

void
uevent_loop(void)
{
  int i;
  fd_set readfds;

  for (;;) {
    FD_ZERO(&readfds);
    for (i = 0; i < _posix_nfds; ++i)
      FD_SET(_posix_fds[i], &readfds);
    select(FD_SETSIZE-1, &readfds, NULL, NULL, NULL);
    for (i = 0; i < _posix_nfds; ++i)
      if (FD_ISSET(_posix_fds[i], &readfds))
        _posix_thunks[_posix_fds[i]].func(_posix_thunks[_posix_fds[i]].arg);
  }
}

#endif

#ifndef HAVE_SIGNALFD

#include <signal.h>
#include <stdlib.h>

struct _posix_signal_thunk
{
  void (*func)(void *);
  void *arg;
};

struct _posix_signal_thunk _posix_signal_thunks[65];

void
_posix_signal_handler(int signo)
{
  _posix_signal_thunks[signo].func(_posix_signal_thunks[signo].arg);
}

void
uevent_add_signal(int signo, void (*func)(void *), void *arg)
{
  struct sigaction sa;

  _posix_signal_thunks[signo].func = func;
  _posix_signal_thunks[signo].arg = arg;

  sa.sa_handler = _posix_signal_handler;

  sigaction(signo, &sa, NULL);
}

#endif
