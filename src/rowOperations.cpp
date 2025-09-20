#include "rowOperations.h"
#include "../include/editor_config.h"
#include "../include/constants.h"
#include "../include/terminal.h"
#include <cstdlib>
#include <cstring>

void rowUpdate(editorRow *row) {
    int tabs = 0;

    for (int i = 0; i < row->size; i++)
        if (row->chars[i] == TAB) tabs++;

    char* newRender = static_cast<char*>(realloc(row->render, row->size + tabs * (TAB_SIZE - TAB_REPLACEMENT_OFFSET) + SPACE_FOR_NULL_BYTE));

    if (!newRender) {
        free(row->render);
        row->render = NULL;
        die("rowUpdate realloc failed");
        return;
    }
    row->render = newRender;

    int idx = 0;
    for (int i = 0; i < row->size; i++)
    {
        if (row->chars[i] == TAB) {
            row->render[idx++] = ' ';
            while (idx % TAB_SIZE != 0) row->render[idx++] = ' ';
        }
        else
            row->render[idx++] = row->chars[i];
    }
    row->render[idx] = '\0';
    row->renderSize = idx;
}

void rowAppend(std::string s, size_t len) {
    E.row = static_cast<editorRow*>(realloc(E.row, sizeof(editorRow) * (E.fileRows + 1)));
    if (!E.row) {
        die("rowAppend realloc failed");
        return;
    }
    
    int currentRow = E.fileRows;
    
    E.row[currentRow].size = len;
    E.row[currentRow].renderSize = 0;
    E.row[currentRow].chars = static_cast<char*>(malloc(len + SPACE_FOR_NULL_BYTE));
    if (!E.row[currentRow].chars) {
        die("rowAppend malloc failed");
        return;
    }
    if (len > 0) 
        memcpy(E.row[currentRow].chars, s.c_str(), len);
    E.row[currentRow].chars[len] = NULL_TERMINATOR;

    E.row[currentRow].render = static_cast<char*>(malloc(SPACE_FOR_NULL_BYTE));
    if (!E.row[currentRow].render) {
        die("rowAppend render malloc failed");
        return;
    }
    E.row[currentRow].render[0] = NULL_TERMINATOR;
    E.row[currentRow].renderSize = 0;

    rowUpdate(&E.row[currentRow]);
    E.fileRows++;

    E.dirty++;
}

char *rowsToString(size_t *bufLength) {     //When using this function, make sure to free the returned buffer
    size_t totalSize = 0;
    for (int i = 0; i < E.fileRows; i++) {
        totalSize += E.row[i].size;
        if (i < E.fileRows - 1)
            totalSize += strlen(NEWLINE);
    }

    if (bufLength) *bufLength = totalSize;

    char *buffer = static_cast<char*>(malloc(totalSize));
    if (!buffer) {
        die("rowsToString malloc failed");
        return NULL;
    }
    char *ptr = buffer;     // Moving pointer to track current position in buffer

    for (int i = 0; i < E.fileRows; i++) {
        memcpy(ptr, E.row[i].chars, E.row[i].size);
        ptr += E.row[i].size;
        if (i < E.fileRows - 1) { 
            *ptr = '\n';
            ptr++;
        }
    }
    
    return buffer;
}