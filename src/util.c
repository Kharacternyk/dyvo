#include <stdlib.h>
#include <stdio.h>

#define FREAD_BUFFER_SIZE 1000

char *fread_till_end(const char *fname) {
    FILE *file = fopen(fname, "r");
    char *buffer = malloc(FREAD_BUFFER_SIZE);
    int readc, overhead = 0;
    while ((readc = fread(buffer + overhead,
                          sizeof(char),
                          FREAD_BUFFER_SIZE, file)) == FREAD_BUFFER_SIZE) {
        overhead += FREAD_BUFFER_SIZE;
        buffer = realloc(buffer, overhead + FREAD_BUFFER_SIZE);
    }
    buffer[overhead + readc] = '\0';
    fclose(file);
    return buffer;
}

