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

#if defined(__cplusplus)
extern "C" {
#endif

int hl_thread_create(hl_thread_t *thread, void *func, void *args) {
#if defined(_WIN32)
	if (!(*thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, args, 0, NULL))) {
		return -1;
	}

	return 0;
#else
	return pthread_create(thread, NULL, func, args);
#endif
}

void hl_thread_destroy(hl_thread_t thread) {
#if defined(_WIN32)
	CloseHandle(thread);
#else
	pthread_exit(NULL);
#endif
}

int hl_thread_join(hl_thread_t thread) {
#if defined(_WIN32)
	switch (WaitForSingleObject(thread, INFINITE)) {
	case WAIT_OBJECT_0:
		return 0;
	default:
		return -1;
	}
#else
	return pthread_join(thread, NULL);
#endif
}

void hl_thread_exit(void) {
#if defined(_WIN32)
	WORD ret = 0;
	ExitThread(ret);
#else
	pthread_exit(NULL);
#endif
}

int hl_mutex_lock(hl_mutex_t *mutex) {
#if defined(_WIN32)
	DWORD result = WaitForSingleObject(*mutex, INFINITE);
	switch (result) {
	case WAIT_OBJECT_0:
		return 0;
	default:
		return 1;
	}
#else
	return pthread_mutex_lock(mutex);
#endif
}

int hl_mutex_unlock(hl_mutex_t *mutex) {
#if defined(_WIN32)
	if (ReleaseMutex(*mutex)) {
		return 0;
	}
	return 1;
#else
	return pthread_mutex_unlock(mutex);
#endif
}

void hl_mutex_create(hl_mutex_t *mutex) {
#if defined(_WIN32)
	*mutex = CreateMutex(NULL, FALSE, NULL);
#else
	pthread_mutex_init(mutex, NULL);
#endif
}

int hl_condlock_lock(hl_condlock_t *condlock) {
#if defined(_WIN32)
	EnterCriticalSection(condlock);
	return 0;
#else
	return hl_mutex_lock(condlock);
#endif
}

int hl_condlock_unlock(hl_condlock_t *condlock) {
#if defined(_WIN32)
	LeaveCriticalSection(condlock);
	return 0;
#else
	return hl_mutex_unlock(condlock);
#endif
}

void hl_condlock_create(hl_condlock_t *condlock) {
#if defined(_WIN32)
	InitializeCriticalSection(condlock);
#else
	hl_mutex_create(condlock);
#endif
}

int hl_cond_create(hl_cond_t *cond) {
#if defined(_WIN32)
	InitializeConditionVariable(cond);
	return 0;
#else
	return pthread_cond_init(cond, NULL);
#endif
}

int hl_cond_wait(hl_cond_t *cond, hl_condlock_t *condlock) {
#if defined(_WIN32)
	SleepConditionVariableCS(cond, condlock, INFINITE);
	return 0;
#else
	return pthread_cond_wait(cond, condlock);
#endif
}

int hl_cond_signal(hl_cond_t *cond) {
#if defined(_WIN32)
	WakeConditionVariable(cond);
	return 0;
#else
	return pthread_cond_signal(cond);
#endif
}

#if defined(__cplusplus)
}
#endif
