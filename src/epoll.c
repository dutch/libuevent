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
#include <stdio.h>
#include <sys/epoll.h>

struct _epoll_thunk
{
  void (*func)(void *);
  void *arg;
};

int _epoll_fd;
struct _epoll_thunk _epoll_thunks[1024];

void
_epoll_initialize(void)
{
  _epoll_fd = epoll_create1(0);
}

void
uevent_add_fildes(int fd, void (*func)(void *), void *arg)
{
  struct epoll_event ev;

  _epoll_thunks[fd].func = func;
  _epoll_thunks[fd].arg = arg;

  ev.events = EPOLLIN;
  ev.data.fd = fd;

  epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}

void
uevent_loop(void)
{
  int nevs;
  struct epoll_event evs[10];

  for (;;) {
    nevs = epoll_wait(_epoll_fd, evs, 10, -1);

    while (nevs --> 0)
      _epoll_thunks[evs[nevs].data.fd].func(_epoll_thunks[evs[nevs].data.fd].arg);
  }
}
