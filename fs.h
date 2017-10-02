#ifndef FS_H
#define FS_H

typedef (int)(*fs_read_cb)(Str *, void *);

void fs_read(char *path, int size, fs_read_cb, void *);

#endif
