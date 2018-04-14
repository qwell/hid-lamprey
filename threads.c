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

int hl_thread_create(HL_THREAD *handle, void *func, void *args) {
#if defined(_WIN32)
printf("w_threads\n");
	if (!(*handle = CreateThread(NULL, 0, func, args, 0, NULL))) {
		return -1;
	}

	return 0;
#else
printf("p_threads\n");
	return pthread_create(handle, NULL, func, args);
#endif
}

void hl_thread_destroy(HL_THREAD handle) {
#if defined(_WIN32)
	CloseHandle(handle);
#else
	pthread_exit(NULL);
#endif
}

int hl_thread_join(HL_THREAD handle) {
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

int hl_mutex_lock(HL_MUTEX *handle) {
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

int hl_mutex_unlock(HL_MUTEX *handle) {
#if defined(_WIN32)
	if (ReleaseMutex(*handle)) {
		return 0;
	}
	return 1;
#else
	return pthread_mutex_unlock(handle);
#endif
}

void hl_mutex_create(HL_MUTEX *handle) {
#if defined(_WIN32)
	*handle = CreateMutex(NULL, FALSE, NULL);
#else
	*handle = PTHREAD_MUTEX_INITIALIZER;
#endif
}

HL_THREAD t_test;
HL_THREAD t_test2;
HL_MUTEX t_mutex_test;

HL_THREAD_FUNC threadtest_func(void *arg) {
	hl_mutex_lock(&t_mutex_test);
	printf("threadtest1: %s\n", (char *)arg);
#if defined(_WIN32)
	SleepEx(3000, TRUE);
#else
	sleep(3);
#endif
	printf("threadtest2: %s\n", (char *)arg);
	hl_mutex_unlock(&t_mutex_test);
	return 0;
}

int threadtest_init() {
	char *arg = "Test";
	hl_mutex_create(&t_mutex_test);
	if (hl_thread_create(&t_test, threadtest_func, arg)) {
		printf("Failed to create thread.\n");
		return -1;
	}
	if (hl_thread_create(&t_test2, threadtest_func, arg)) {
		printf("Failed to create thread.\n");
		return -1;
	}

	return 0;
}

void threadtest_destroy() {
	if (t_test) {
		hl_thread_destroy(t_test);
	}
	if (t_test2) {
		hl_thread_destroy(t_test2);
	}
}
