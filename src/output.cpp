#include "../include/output.h"
#include "../include/terminal.h"
#include "../include/editor_config.h"
#include "../include/constants.h"
#include "../include/append_buffer.h"
#include "../include/input.h"
#include <windows.h>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <ctime> 

void refreshScreen() {
    editorScroll();
    appendBuffer ab = ABUF_INIT;
    
    abAppend(&ab, HIDE_CURSOR, static_cast<DWORD>(strlen(HIDE_CURSOR)));
    abAppend(&ab, RESET_CURSOR, static_cast<DWORD>(strlen(RESET_CURSOR)));

    drawRows(&ab);
    drawStatusBar(&ab);
    drawMessageBar(&ab);

    char buf[CURSOR_BUFFER_SIZE];
    snprintf(buf, sizeof(buf), CURSOR_LOCATION, (E.cursorY - E.rowOffset) + ONE, (E.renderX - E.colOffset) + ONE);
    abAppend(&ab, buf, static_cast<DWORD>(strlen(buf)));

    abAppend(&ab, SHOW_CURSOR, static_cast<DWORD>(strlen(SHOW_CURSOR)));

    DWORD written;
    if (!WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), ab.bPoint, ab.size, &written, NULL)) {
        die("refreshScreen_WriteConsoleA");
    }

    abFree(&ab);
}

void drawRows(appendBuffer* ab) {    
    for (int i = 0; i < E.screenRows; i++) {
        int rowIndex = i + E.rowOffset;
        if (rowIndex >= E.fileRows) {
            if (E.fileRows == 0 && i == E.screenRows / WELCOME_ROW_DIVISOR) {
                char welcome[WELCOME_BUFFER_SIZE];
                int welcomeLen = snprintf(welcome, sizeof(welcome), 
                                        "Welcome to VELT version %s", VERSION);
                
                if (welcomeLen > E.screenCols)
                    welcome[E.screenCols] = '\0';

                int padding = (E.screenCols - welcomeLen) / WELCOME_PADDING;
                if (padding > 0) {
                    abAppend(ab, TILDE, static_cast<DWORD>(strlen(TILDE)));
                    padding--;
                }

                while (padding-- > 0)
                    abAppend(ab, " ", ONE);

                abAppend(ab, welcome, static_cast<DWORD>(strlen(welcome)));
            } else 
                abAppend(ab, TILDE, static_cast<DWORD>(strlen(TILDE)));
        } else { 
            int len = E.row[rowIndex].renderSize - E.colOffset;
            if (len < 0) 
                len = 0;
            
            if (len > E.screenCols) 
                len = E.screenCols;
            
            abAppend(ab, &E.row[rowIndex].render[E.colOffset], static_cast<DWORD>(len));
        }

        abAppend(ab, ERASE_LINE, static_cast<DWORD>(strlen(ERASE_LINE)));

        abAppend(ab, NEWLINE, static_cast<DWORD>(strlen(NEWLINE)));
        
    }
}

void drawStatusBar(appendBuffer *ab)
{
    abAppend(ab, FONT_CHANGE_WHITE, static_cast<DWORD>(strlen(FONT_CHANGE_WHITE)));

    char status[STATUS_BAR], rowStatus[STATUS_BAR];
    int statusLen = snprintf(status, sizeof(status), "%.25s - %d lines %s", E.fileName ? E.fileName : "[No name]", E.fileRows, E.dirty ? "(modified)" : "");
    if(statusLen > E.screenCols) statusLen = E.screenCols;

    abAppend(ab, status, statusLen);

    int rowStatusLen = snprintf(rowStatus, sizeof(rowStatus), "%d/%d", E.cursorY + ONE, E.fileRows);

    while(statusLen < E.screenCols)
    {
       if(E.screenCols - statusLen == rowStatusLen)
        {
            abAppend(ab, rowStatus, rowStatusLen);
            break;
        }else {
            abAppend(ab, SPACE, static_cast<DWORD>(strlen(SPACE)));
            statusLen++;
        }
    }

    abAppend(ab, FONT_RESET, static_cast<DWORD>(strlen(FONT_RESET)));

    abAppend(ab, NEWLINE, static_cast<DWORD>(strlen(NEWLINE)));
}

void drawMessageBar(appendBuffer *ab) {
    abAppend(ab, ERASE_LINE, static_cast<DWORD>(strlen(ERASE_LINE)));
    int msgLen = strlen(E.statusMessage);
    if (msgLen > E.screenCols) msgLen = E.screenCols;
    if (msgLen && time(NULL) - E.statusMessageTime < TIME_SPAN)
    abAppend(ab, E.statusMessage, msgLen);
}

void setStatusMessage(const char *fmt, ...) {
    va_list ap; // Argument pointer
    va_start(ap, fmt);
    vsnprintf(E.statusMessage, sizeof(E.statusMessage), fmt, ap);
    va_end(ap);
    E.statusMessageTime = time(NULL);
}

void editorScroll() {
    E.renderX = 0;
    if (E.cursorY < E.fileRows)
        E.renderX = cursorX_To_renderX(&E.row[E.cursorY], E.cursorX);   // Calculate renderX based on cursorX

    if (E.cursorY < 0)                                                  // Ensure cursorY is within valid bounds first
        E.cursorY = 0;

    if (E.cursorY >= E.fileRows && E.fileRows > 0)                      // Set cursorY to the last row if it exceeds fileRows
        E.cursorY = E.fileRows - ONE;

    if( E.renderX < E.colOffset )                                       // Handle horizontal scrolling
        E.colOffset = E.renderX;

    if (E.renderX >= E.colOffset + E.screenCols)                        // Scroll right if cursor moves right of visible area
        E.colOffset = E.renderX - E.screenCols + ONE;                   

    if (E.cursorX < E.colOffset)                                        // Scroll left if cursor moves left of visible area
        E.colOffset = E.cursorX;

    if (E.cursorX >= E.colOffset + E.screenCols)                        // Scroll right if cursor moves right of visible area
        E.colOffset = E.cursorX - E.screenCols + ONE;

    if (E.colOffset < 0)                                                // Ensure colOffset doesn't go negative
        E.colOffset = 0;

    if (E.cursorY >= E.rowOffset + E.screenRows)                        // Scroll down if cursor moves down of visible area
        E.rowOffset = E.cursorY - E.screenRows + ONE;

    if (E.rowOffset < 0)                                                // Ensure rowOffset doesn't go negative
        E.rowOffset = 0;

    if (E.fileRows > 0 && E.rowOffset > E.fileRows - E.screenRows)      // Ensure rowOffset doesn't go beyond file content
        E.rowOffset = E.fileRows - E.screenRows;
    
    if (E.cursorY < E.rowOffset)                                        // Handle vertical scrolling
        E.rowOffset = E.cursorY;
}