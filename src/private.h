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

#ifndef UEVENT_PRIVATE_H
#define UEVENT_PRIVATE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if !(defined(HAVE_EPOLL)||defined(HAVE_KQUEUE))
void _posix_initialize(void);
#endif

#ifdef HAVE_EPOLL
void _epoll_initialize(void);
#endif

#ifdef HAVE_SIGNALFD
void _signalfd_initialize(void);
#endif

#endif
