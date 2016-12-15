#ifndef DBG_H
#define DBG_H

#include "def.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifndef NDEBUG
#define DEBUG
#endif

#define DBG_ERRSTR strerror(errno)

#define DBG_PRINT(T, M, ...) (errno\
	? fprintf(stderr, "[%s][%s:%d][%s] " M "\n",\
		T, __FILE__, __LINE__, DBG_ERRSTR, ##__VA_ARGS__)\
	: fprintf(stderr, "[%s][%s:%d] " M "\n",\
		T, __FILE__, __LINE__, ##__VA_ARGS__))

#define NDBG_PRINT(T, M, ...) (errno\
	? fprintf(stderr, "[%s][%s] " M "\n",\
		T, DBG_ERRSTR, ##__VA_ARGS__)\
	: fprintf(stderr, "[%s] " M "\n",\
		T, ##__VA_ARGS__))

#ifdef NDEBUG
#define log_d(M, ...)
#define log_i(M, ...) NDBG_PRINT("I", M, ##__VA_ARGS__)
#define log_w(M, ...) NDBG_PRINT("W", M, ##__VA_ARGS__)
#define log_e(M, ...) NDBG_PRINT("E", M, ##__VA_ARGS__)
#else
#define log_d(M, ...) DBG_PRINT("D", M, ##__VA_ARGS__)
#define log_i(M, ...) DBG_PRINT("I", M, ##__VA_ARGS__)
#define log_w(M, ...) DBG_PRINT("W", M, ##__VA_ARGS__)
#define log_e(M, ...) DBG_PRINT("E", M, ##__VA_ARGS__)
#endif

#endif
