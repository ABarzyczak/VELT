#pragma once
#include "../include/editor_config.h"
/**
 * Input handling functions
 * Processes keyboard input and key combinations
 **/

enum editorKey {
    ESC = 27,
    BACKSPACE = 127,
    ARROW_LEFT = 1000,  // It's set to high number to avoid conflict with ASCII characters
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    CTRL_ARROW_LEFT,
    CTRL_ARROW_RIGHT,
    SCREEN_BOTTOM,
    SCREEN_TOP,
    SCREEN_MIDDLE,
    DELETE_KEY,
    ENTER_KEY,
    INSERTION           // Insert mode
};

int readKey();
void processKeypress();
void moveCursor(int key);
int cursorX_To_renderX(editorRow *row, int cX);
void insertChar(int c);
void rowAppendString(editorRow *row, char *s, size_t len);
void deleteChar();
void deleteRow(int at);