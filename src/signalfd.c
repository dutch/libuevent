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
#include <signal.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>

struct _signalfd_thunk
{
  void (*func)(void *);
  void *arg;
};

sigset_t _signalfd_sigs;
int _signalfd_fd;
struct _signalfd_thunk _signalfd_thunks[64];

void
_signalfd_initialize(void)
{
  sigemptyset(&_signalfd_sigs);
  _signalfd_fd = signalfd(-1, &_signalfd_sigs, 0);
}

void
_signalfd_read(void *p)
{
  struct signalfd_siginfo ssi;

  read(_signalfd_fd, &ssi, sizeof(struct signalfd_siginfo));
  _signalfd_thunks[ssi.ssi_signo].func(_signalfd_thunks[ssi.ssi_signo].arg);
}

void
uevent_add_signal(int signo, void (*func)(void *), void *arg)
{
  sigaddset(&_signalfd_sigs, signo);
  sigprocmask(SIG_BLOCK, &_signalfd_sigs, NULL);
  signalfd(_signalfd_fd, &_signalfd_sigs, 0);
  _signalfd_thunks[signo].func = func;
  _signalfd_thunks[signo].arg = arg;
  uevent_add_fildes(_signalfd_fd, _signalfd_read, NULL);
}
