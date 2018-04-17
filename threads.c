/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>

#include "include/threads.h"

int __cdecl hl_thread_create(hl_thread_t *handle, void *func, void *args) {
#if defined(_WIN32)
	if (!(*handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, args, 0, NULL))) {
		return -1;
	}

	return 0;
#else
	return pthread_create(handle, NULL, func, args);
#endif
}

void __cdecl hl_thread_destroy(hl_thread_t handle) {
#if defined(_WIN32)
	CloseHandle(handle);
#else
	pthread_exit(NULL);
#endif
}

int __cdecl hl_thread_join(hl_thread_t handle) {
#if defined(_WIN32)
	switch(WaitForSingleObject(handle, INFINITE)) {
	case WAIT_OBJECT_0:
		return 0;
	default:
		return -1;
	}
#else
	return pthread_join(handle, NULL);
#endif
}

void __cdecl hl_thread_exit(void) {
#if defined(_WIN32)
	WORD ret = 0;
	ExitThread(ret);
#else
	pthread_exit(NULL);
#endif
}

int __cdecl hl_mutex_lock(hl_mutex_t *handle) {
#if defined(_WIN32)
	DWORD result = WaitForSingleObject(*handle, INFINITE);
	switch (result) {
	case WAIT_OBJECT_0:
		return 0;
	default:
		return 1;
	}
#else
	return pthread_mutex_lock(handle);
#endif
}

int __cdecl hl_mutex_unlock(hl_mutex_t *handle) {
#if defined(_WIN32)
	if (ReleaseMutex(*handle)) {
		return 0;
	}
	return 1;
#else
	return pthread_mutex_unlock(handle);
#endif
}

void hl_mutex_create(hl_mutex_t *handle) {
#if defined(_WIN32)
	*handle = CreateMutex(NULL, FALSE, NULL);
#else
	pthread_mutex_init(handle, NULL);
#endif
}

