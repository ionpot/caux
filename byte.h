#ifndef BYTE_H
#define BYTE_H

#include "def.h"

typedef unsigned char byte;

uint byte_r(byte *, size_t);
void byte_w(byte *, size_t, uint);

#endif
