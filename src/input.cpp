#include "../include/input.h"
#include "../include/terminal.h"
#include "../include/output.h"
#include "../include/editor_config.h"
#include "../include/constants.h"
#include "../include/rowOperations.h"
#include "../include/file_io.h"
#include "../include/modes.h"
#include <windows.h>
#include <cstdlib>
#include <cstring>

// enum editorKey {
//     ESC = 27,
//     BACKSPACE = 127,
//     ARROW_LEFT = 1000,  // It's set to high number to avoid conflict with ASCII characters
//     ARROW_RIGHT,
//     ARROW_UP,
//     ARROW_DOWN,
//     SCREEN_BOTTOM,
//     SCREEN_TOP,
//     SCREEN_MIDDLE,
//     DELETE_KEY,
//     INSERTION
// };

int readKey() {
    INPUT_RECORD inputRecord;   // Structure that contain various types of console events 
    DWORD read;
    
    while (true) {
        if (!ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &read))    // Only keyboard events
            die("ReadConsoleInput failed");
        
        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            WORD vkCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;
            char asciiChar = inputRecord.Event.KeyEvent.uChar.AsciiChar;
            
            switch (vkCode) {
                // Cursor movement
                case VK_UP: return ARROW_UP;
                case VK_DOWN: return ARROW_DOWN;
                case VK_LEFT: return ARROW_LEFT;
                case VK_RIGHT: return ARROW_RIGHT;

                case VK_PRIOR: return SCREEN_BOTTOM;    // Page up
                case VK_NEXT: return SCREEN_TOP;        // Page down

                case VK_DELETE: return DELETE_KEY;
                case VK_BACK: return BACKSPACE;

                default:
                    if(E.mode == DEFAULT_MODE && asciiChar >= MIN_ASCII_PRINTABLE_CHAR && asciiChar <= MAX_ASCII_PRINTABLE_CHAR) {
                        switch (asciiChar) {
                            case 'h': return ARROW_LEFT;
                            case 'j': return ARROW_DOWN;
                            case 'k': return ARROW_UP;
                            case 'l': return ARROW_RIGHT;
                            case 'H': return SCREEN_BOTTOM;
                            case 'M': return SCREEN_MIDDLE;
                            case 'L': return SCREEN_TOP;
                            case 'i': return INSERTION;
                            default:
                                if (asciiChar != 0) return asciiChar;
                        }
                    }
                if (asciiChar != 0) return asciiChar;
            }
        }
    }
}

void processKeypress()
{
    if (E.mode == DEFAULT_MODE) 
        defaultMode();
    else if (E.mode == INSERT_MODE) 
        insertMode();
}

void moveCursor(int key) {
    editorRow *row = (E.cursorY >= E.fileRows) ? NULL : &E.row[E.cursorY];

    switch (key) {
        case ARROW_LEFT:
            if( E.cursorX != 0 )
                E.cursorX--;
            else if( E.cursorY > 0 ) {
                E.cursorY--;
                E.cursorX = E.row[E.cursorY].size;  // Move to the end of the previous row
            }
            break;

        case ARROW_RIGHT: 
            if( row && E.cursorX < row->size )
                E.cursorX++;
            else if( row && E.cursorX == row->size ) {
                E.cursorY++;
                E.cursorX = 0;  // Move to the start of the next row
            }
            break;

        case ARROW_UP: 
            if( E.cursorY > 0 )
                E.cursorY--;
            break;
        
        case ARROW_DOWN:
            if( E.cursorY < E.fileRows - 1) 
                E.cursorY++;
            break;
    }

    row = (E.cursorY >= E.fileRows) ? NULL : &E.row[E.cursorY];
    int rowSize = (row) ? row->size : 0;
    if (E.cursorX > rowSize) 
        E.cursorX = rowSize;
} 

int cursorX_To_renderX(editorRow *row, int cX) {
    int rX = 0;
    for (int i = 0; i < cX; i++) {
        if (row->chars[i] == '\t')
            rX += (TAB_SIZE - 1) - (rX % TAB_SIZE);
        rX++;
    }
    return rX;
}

void insertChar(int c)
{
    if(E.cursorY == E.fileRows)
        rowAppend("", 0);

    editorRow *row = &E.row[E.cursorY];
    int at = E.cursorX;

    if (at < 0 || at > row->size) return;
    row->chars = static_cast<char*>(realloc(row->chars, row->size + NEW_CHAR_AND_NULL_BYTE));
    if (!row->chars) {
        die("rowInsertChar realloc failed");
        return;
    }
    memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);

    row->chars[at] = c;
    row->size++;

    rowUpdate(row);
    E.dirty++;
    E.cursorX++;
}

void deleteChar()
{
    if (E.cursorY == E.fileRows) return;

    editorRow * row = &E.row[E.cursorY];
    int at = E.cursorX - 1;

    if (E.cursorX > 0) {
        if (at < 0 || at >= row->size) return;
        memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
        row->size--;
        rowUpdate(row);
        E.dirty++;
        E.cursorX--;
    }
}