/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_SDL2_H
#define LAMPREY_SDL2_H

#include <sys/poll.h>

#include <SDL2/SDL.h>

extern pthread_t t_sdl2;
extern pthread_mutex_t mutex_sdl2;
extern struct hl_sdl2 *hl_sdl2;

void hl_sdl2_init();
void hl_sdl2_destroy();
void *hl_sdl2_poll();
void hl_sdl2_inject(int id, uint8_t type, uint16_t code, int16_t value);

#endif
