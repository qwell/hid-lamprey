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

#if defined(_WIN32)
VOID CALLBACK threadalert(ULONG_PTR ptr) {
	return;
}
BOOL WINAPI ctrlhandler(DWORD type) {
	HANDLE curthread;

	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &curthread, GENERIC_ALL, FALSE, 0);
	QueueUserAPC(threadalert, curthread, 0);

	return TRUE;
}
#endif

int hl_thread_create(HL_THREAD *handle, void *func, void *args) {
#if defined(_WIN32)
printf("w_threads\n");
	if (!(*handle = CreateThread(NULL, 0, func, args, 0, NULL))) {
		return -1;
	}

	SetConsoleCtrlHandler(ctrlhandler, TRUE);

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

HL_THREAD t_test;

HL_THREAD_FUNC threadtest_func(void *arg) {
	printf("threadtest1: %s\n", (char *)arg);
#if defined(_WIN32)
	SleepEx(6000, TRUE);
#else
	sleep(6);
#endif
	printf("threadtest2: %s\n", (char *)arg);
	return 0;
}

int threadtest_init() {
	char *arg = "Test";
	if (hl_thread_create(&t_test, threadtest_func, arg)) {
		printf("Failed to create thread.\n");
		return -1;
	}

	return 0;
}

void threadtest_destroy() {
	if (t_test) {
		hl_thread_destroy(t_test);
	}
}
