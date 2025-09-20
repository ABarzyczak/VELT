#include "../include/modes.h"
#include "../include/editor_config.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/constants.h"
#include "../include/rowOperations.h"
#include "../include/file_io.h"
#include "../include/terminal.h"
#include <windows.h>

void defaultMode()
{
    static int quitTimes = QUIT_TIMES;
    int c = readKey();
    switch (c) {
            case CTRL_KEY('q'):
            {
                if (E.dirty && quitTimes > 0) {
                    setStatusMessage("WARNING!!! File has unsaved changes. Press Ctrl-Q again to quit.");
                    quitTimes--;
                    return;
                }
                DWORD written;
                if (!WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), REFRESH, (DWORD)strlen(REFRESH), &written, NULL)) 
                    die("editorRefreshScreen_WriteConsoleA");
                exit(EXIT_SUCCESS);
                break;
            }
            case ARROW_DOWN:
            case ARROW_LEFT:
            case ARROW_RIGHT:
            case ARROW_UP:
                moveCursor(c);
                break;
            case SCREEN_BOTTOM:
            case SCREEN_TOP:
            {
                int pageSize = E.screenRows;
                while(pageSize--)
                    moveCursor(c == SCREEN_BOTTOM ? ARROW_UP : ARROW_DOWN);
                break;
            }
            case SCREEN_MIDDLE:
            {
                int middle = E.screenRows / MIDDLE_SCREEN_DIVISOR;
                while(middle--)
                    moveCursor(ARROW_DOWN);
                break;
            }
            case INSERTION:
                E.mode = INSERT_MODE;
                setStatusMessage("-- INSERT --");
                break;
            case CTRL_KEY('s'):
                editorSave();
                break;
        }
        
    quitTimes = QUIT_TIMES;
}

void insertMode()
{
    static int quitTimes = QUIT_TIMES;
    int c = readKey();
    switch (c) {
            case CTRL_KEY('q'):
            {
                if (E.dirty && quitTimes > 0) {
                    setStatusMessage("WARNING!!! File has unsaved changes. Press Ctrl-Q again to quit.");
                    quitTimes--;
                    return;
                }
                DWORD written;
                if (!WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), REFRESH, (DWORD)strlen(REFRESH), &written, NULL)) 
                    die("editorRefreshScreen_WriteConsoleA");
                exit(EXIT_SUCCESS);
                break;
            }
            case ARROW_DOWN:
            case ARROW_LEFT:
            case ARROW_RIGHT:
            case ARROW_UP:
                moveCursor(c);
                break;
            case CTRL_ARROW_LEFT:
            case CTRL_ARROW_RIGHT:
                while(E.cursorX > 0 && E.cursorX < E.screenCols && E.cursorY < E.fileRows) {
                    moveCursor(c == CTRL_ARROW_LEFT ? ARROW_LEFT : ARROW_RIGHT);
                    if (E.cursorX > 0 && E.cursorX < E.screenCols && E.cursorY < E.fileRows) 
                        if (E.row[E.cursorY].chars[E.cursorX - 1] == ' ') break;
                }
                break;
            case SCREEN_BOTTOM:
            case SCREEN_TOP:
            {
                int pageSize = E.screenRows;
                while(pageSize--)
                    moveCursor(c == SCREEN_BOTTOM ? ARROW_UP : ARROW_DOWN);
                break;
            }
            case SCREEN_MIDDLE:
            {
                int middle = E.screenRows / MIDDLE_SCREEN_DIVISOR;
                while(middle--)
                    moveCursor(ARROW_DOWN);
                break;
            }
            case CTRL_KEY('s'):
                editorSave();
                break;
            case ESC:
                E.mode = DEFAULT_MODE;
                setStatusMessage("");
                break;
            case BACKSPACE:
            case DELETE_KEY:
            case CTRL_KEY('h'):
                if (c == DELETE_KEY) moveCursor(ARROW_RIGHT);
                deleteChar();
                break;
            default:
                if (c >= MIN_ASCII_PRINTABLE_CHAR && c <= MAX_ASCII_PRINTABLE_CHAR)
                    insertChar(c);
                break;
        }
        
    quitTimes = QUIT_TIMES;
}

void searchMode()
{

}