#pragma once
#include "../include/editor_config.h"
/**
 * Input handling functions
 * Processes keyboard input and key combinations
 **/

int readKey();
void moveCursor(int key);
int cursorX_To_renderX(editorRow *row, int cX);
void insertChar(int c);
void deleteChar();
void defaultMode();
void insertMode();