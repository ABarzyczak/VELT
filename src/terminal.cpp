#include "../include/terminal.h"
#include "../include/output.h"
#include "../include/constants.h"
#include <windows.h>
#include <cstdio>
#include <cstdlib>

void enableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (!GetConsoleMode(hStdin, &mode)) die("enable_GetConsoleMode");
    atexit(disableRawMode);
    // Disable echo, no need to press enter
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);  //&= ~ is used to disable certain features by clearing specific bits to 0
    //Disable key combinations 
    mode &= ~(ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE);
    //Disable output processing 
    mode &= ~(ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
    if (!SetConsoleMode(hStdin, mode)) die("enable_SetConsoleMode");
}

void disableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (!GetConsoleMode(hStdin, &mode)) die("disable_GetConsoleMode");
    mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT );  //|= is used to enable certain features by setting specific bits to 1
    if (!SetConsoleMode(hStdin, mode)) die("disable_SetConsoleMode");
}

void die(const char* s) {
    refreshScreen();
    perror(s);
    exit(EXIT_FAILURE);
}

int getWindowSize(int *rows, int *cols) {
    const unsigned short int tempNum = 1;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return ERR;
    } else {
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + tempNum;
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + tempNum;
        return EXIT_SUCCESS;
    }
}