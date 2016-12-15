#ifndef DEF_H
#define DEF_H

#include <stddef.h>

#define nil NULL

#define ASC(x, y, z) (((x) <= (y)) && ((y) <= (z)))
#define KiB(x) ((x) * 1024)
#define MiB(x) (KiB(x) * 1024)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define WRAP(x) do { x } while (0)

typedef unsigned char byte;

#endif
