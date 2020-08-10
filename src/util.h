#ifndef __util
#define __util

#include <dirent.h>

char *fread_till_end(const char *fname);
int nothidden(const struct dirent *file);

#endif
