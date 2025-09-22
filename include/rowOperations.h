#pragma once
#include "editor_config.h"
#include <string>
/**
 * Row operations 
 **/

void rowUpdate(editorRow *row);
void rowInsert(int currentRow, std::string s, size_t len);
char *rowsToString(size_t *bufLength);