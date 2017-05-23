#ifndef NUM_H
#define NUM_H

#define ASC(x, y, z) (((x) <= (y)) && ((y) <= (z)))
#define KiB(x) ((x) * 1024)
#define MiB(x) (KiB(x) * 1024)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#endif
