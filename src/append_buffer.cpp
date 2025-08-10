#include "../include/constants.h"
#include "../include/append_buffer.h"
#include "../include/terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abAppend(appendBuffer *ab, const char *s, unsigned int len) {

    ab->bPoint = static_cast<char*>(realloc(ab->bPoint, ab->size + len));

    if (ab->bPoint == NULL)
        die("realloc failed");

    memcpy(&ab->bPoint[ab->size], s, len);
    ab->size += len;
}

void abFree(appendBuffer *ab) {
    free(ab->bPoint);
    ab->bPoint = NULL;
    ab->size = 0;
}