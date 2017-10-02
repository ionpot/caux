#ifndef ERR_H
#define ERR_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define ERR_STR strerror(errno)

#define err_write(M, ...) \
	fprintf(stderr, M, ##__VA_ARGS__)

#ifdef NDEBUG
#define DEBUG 0
#define err_print(T, M, ...) (errno\
	? err_write("[%s][%s] " M,\
		T, ERR_STR, ##__VA_ARGS__)\
	: err_write("[%s] " M,\
		T, ##__VA_ARGS__))
#else
#define DEBUG 1
#define err_print(T, M, ...) (errno\
	? err_write("[%s][%s:%d][%s] " M,\
		T, __FILE__, __LINE__, ERR_STR, ##__VA_ARGS__)\
	: err_write("[%s][%s:%d] " M,\
		T, __FILE__, __LINE__, ##__VA_ARGS__))
#endif

#define err_echo(T, M, ...) \
	err_print(T, M "\n", ##__VA_ARGS__)

#define log_i(M, ...) err_echo("I", M, ##__VA_ARGS__)
#define log_w(M, ...) err_echo("W", M, ##__VA_ARGS__)
#define log_e(M, ...) err_echo("E", M, ##__VA_ARGS__)

#define err_check(A, M, ...) if (A) {\
	log_e(M, ##__VA_ARGS__); errno = 0; goto error; }

#define err_nil(A, M, ...) \
	err_check((A) == nil, M, ##__VA_ARGS__)

#define err_ok(A, M, ...) \
	err_check((A) < 0, M, ##__VA_ARGS__)

#endif
