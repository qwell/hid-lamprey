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
typedef CRITICAL_SECTION hl_condlock_t;
typedef CONDITION_VARIABLE hl_cond_t;
#else
#include <pthread.h>
typedef pthread_t hl_thread_t;
typedef pthread_mutex_t hl_mutex_t;
typedef hl_mutex_t hl_condlock_t;
typedef pthread_cond_t hl_cond_t;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

int hl_thread_create(hl_thread_t *thread, void *func, void *args);
void hl_thread_destroy(hl_thread_t thread);
int hl_thread_join(hl_thread_t thread);
void hl_thread_exit();

void hl_mutex_create(hl_mutex_t *mutex);
int hl_mutex_lock(hl_mutex_t *mutex);
int hl_mutex_unlock(hl_mutex_t *mutex);

void hl_condlock_create(hl_condlock_t *condlock);
int hl_condlock_lock(hl_condlock_t *condlock);
int hl_condlock_unlock(hl_condlock_t *condlock);

int hl_cond_create(hl_cond_t *cond);
int hl_cond_wait(hl_cond_t *cond, hl_condlock_t *condlock);
int hl_cond_signal(hl_cond_t *cond);

#if defined(__cplusplus)
}
#endif

#endif
