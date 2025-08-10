#pragma once
/**
 * Terminal management functions
 * Handles raw mode, window size, and low-level console operations
 **/

void enableRawMode();
void disableRawMode();
void die(const char* s);
int getWindowSize(int* rows, int* cols);