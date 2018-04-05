/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/input.h"

pthread_t t_sdl2;
pthread_mutex_t mutex_sdl2 = PTHREAD_MUTEX_INITIALIZER;
struct hl_sdl2 *hl_sdl2 = NULL;

void hl_sdl2_init() {
	if (SDL_Init(SDL_INIT_EVENTS|SDL_INIT_GAMECONTROLLER|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC) != 0){
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return;
	}

	/* Spawn off a thread to handle SDL2 polling. */
	pthread_create(&t_sdl2, NULL, hl_sdl2_poll, NULL);
}

void *hl_sdl2_poll() {
	SDL_Event event;

	SDL_CreateWindow("Nothing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0,0, 0);
	printf("SDL2 initialized.\n");
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			printf("Got SDL event type: %d\n", event.type);
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			default:
				break;
			}
			if (quit) {
				break;
			}
		}
	}
	SDL_Quit();
	printf("SDLs destroyed.\n");

	pthread_exit(NULL);

	return NULL;
}

void hl_sdl2_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}
