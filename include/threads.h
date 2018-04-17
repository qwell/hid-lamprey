/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_THREADS_H
#define LAMPREY_THREADS_H

#if defined(_WIN32)
#include <windows.h>
typedef HANDLE hl_thread_t;
typedef HANDLE hl_mutex_t;
typedef DWORD HL_THREAD_FUNC;
#else
#include <pthread.h>
typedef pthread_t hl_thread_t;
typedef pthread_mutex_t hl_mutex_t;
typedef void *HL_THREAD_FUNC;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

int hl_thread_create(hl_thread_t *handle, void *func, void *args);
void hl_thread_destroy(hl_thread_t handle);
int hl_thread_join(hl_thread_t handle);
void hl_thread_exit();

void hl_mutex_create(hl_mutex_t *handle);
int hl_mutex_lock(hl_mutex_t *handle);
int hl_mutex_unlock(hl_mutex_t *handle);

#if defined(__cplusplus)
}
#endif

#endif
