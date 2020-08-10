#ifndef __util
#define __util

#include <dirent.h>

#define panic(fmt, ...) do {fprintf(stderr, fmt, __VA_ARGS__); exit(1);} while(0)

char *fread_till_end(const char *fname);
int nothidden(const struct dirent *file);

#endif
