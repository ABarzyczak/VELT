#pragma once
#include "constants.h"
#include <cstddef>
#include <ctime>
/**
 * Global editor structure
 **/

typedef struct{
    int size;
    int renderSize;
    char *chars;
    char *render;
}editorRow;

enum editorMode {
	DEFAULT_MODE,
	INSERT_MODE
};

struct editorConfig {
    int cursorX, cursorY;           // cursor position in the file
    int renderX;                    // visual position of cursor in the row
    int screenRows, screenCols;     // display
    int rowOffset, colOffset;       // scrolling
    int fileRows;                   // number of rows in the file
    char *fileName;
    char statusMessage[STATUS_MESSAGE];
    int dirty;                      // file modified flag
    time_t statusMessageTime;
    editorRow *row;
    editorMode mode;
};

extern editorConfig E;