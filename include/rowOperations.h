#pragma once
#include "editor_config.h"
#include <string>
/**
 * Row operations 
 **/

void rowUpdate(editorRow *row);
void rowAppend(std::string s, size_t len);
char *rowsToString(size_t *bufLength);