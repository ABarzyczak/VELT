#pragma once
#include "append_buffer.h"
/**
 * Output and screen rendering functions
 * Handles screen refresh, drawing, and display operations
 **/

void refreshScreen();
void drawRows(appendBuffer *ab);
void drawStatusBar(appendBuffer *ab);
void editorScroll();
void setStatusMessage(const char *fmt, ...);
void drawMessageBar(appendBuffer *ab);