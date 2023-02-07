#ifndef UEVENT_UEVENT_H
#define UEVENT_UEVENT_H

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

void uevent_initialize(void);
void uevent_add_fildes(int, void (*)(void *), void *);
void uevent_add_signal(int, void (*)(void *), void *);
void uevent_loop(void);

#endif
