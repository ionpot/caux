#include "byte.h"

#include <assert.h>

uint
byte_r(byte *buf, size_t size)
{
	assert(buf != nil);
	assert(size > 0);

	uint mul = 1;
	uint out = buf[--size];

	while (size > 0) {
		mul *= 256;
		out += buf[--size] * mul;
	}

	return out;
}

void
byte_w(byte *buf, size_t size, uint value)
{
	assert(buf != nil);
	assert(size > 0);

	buf[--size] = value % 256;

	while (size > 0) {
		value /= 256;

		buf[--size] = value % 256;
	}
}
