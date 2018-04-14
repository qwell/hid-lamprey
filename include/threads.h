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

#include "lamprey.h"

#if defined(_WIN32)

#include <windows.h>
typedef HANDLE HL_THREAD;
typedef DWORD WINAPI HL_THREAD_FUNC;

#else

#include <pthread.h>
typedef pthread_t HL_THREAD;
typedef void *HL_THREAD_FUNC;

#endif

int hl_thread_create(HL_THREAD *handle, void *func, void *args);
void hl_thread_destroy(HL_THREAD handle);
int hl_thread_join(HL_THREAD handle);

extern HL_THREAD t_test;

int threadtest_init();
void threadtest_destroy();

#endif
