#pragma once 
/**
 * Append buffer structure
 * Created to refresh screen faster as one prompt
 **/

typedef struct{
    char *bPoint;
    unsigned int size;
} appendBuffer;

void abAppend(appendBuffer *ab, const char *s, unsigned int len);
void abFree(appendBuffer *ab);