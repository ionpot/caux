#ifndef CHECK_H
#define CHECK_H

#include "dbg.h"
#include "def.h"

#include <errno.h>

#define CHECK(F, A, M, ...) if (A) {\
	F(M, ##__VA_ARGS__); errno = 0; goto error; }

#define check(A, M, ...) CHECK(log_e, A, M, ##__VA_ARGS__)
#define check_d(A, M, ...) CHECK(log_d, A, M, ##__VA_ARGS__)

#define not_nil(A, M, ...) check((A) == nil, M, ##__VA_ARGS__)
#define is_ok(A, M, ...) check((A) < 0, M, ##__VA_ARGS__)

#endif
