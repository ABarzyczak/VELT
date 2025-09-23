#pragma once
/**
 * Set of definitions 
 **/
#define ERR -1

#define CURSOR_LOCATION "\x1b[%d;%dH"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"
#define RESET_CURSOR "\x1b[H"
#define ERASE_LINE "\x1b[K"
#define REFRESH "\x1b[2J\x1b[H"
#define NEWLINE "\r\n"
#define CTRL_KEY(k) ((k) & 0x1f)
#define FONT_CHANGE_WHITE "\x1b[7m"
#define FONT_RESET "\x1b[0m"
#define SPACE " "
#define TILDE "~"
#define TAB '\t'
#define NULL_TERMINATOR '\0'

#define ABUF_INIT {NULL, 0}

#define CURSOR_BUFFER_SIZE 32

#define TAB_SIZE 8
#define TAB_REPLACEMENT_OFFSET 1

#define STATUS_BAR 80
#define STATUS_BAR_AND_PROMPT_SPACE 2
#define STATUS_MESSAGE 80

#define MIDDLE_SCREEN_DIVISOR 2

#define TIME_SPAN 5

#define NEW_CHAR_AND_NULL_BYTE 2

#define QUIT_TIMES 1

#define SPACE_FOR_NULL_BYTE 1

#define MIN_ASCII_PRINTABLE_CHAR 32
#define MAX_ASCII_PRINTABLE_CHAR 126

#define PROMPT_BUF_SIZE 128