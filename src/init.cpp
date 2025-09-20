#include "../include/init.h"
#include "../include/terminal.h"
#include "../include/editor_config.h"
#include "../include/constants.h"
#include "../include/rowOperations.h"
#include <cstdlib>

void initEditor() {
    E.statusMessage[0] = '\0';
    E.row = nullptr;
    E.fileRows = 0;
    E.mode = DEFAULT_MODE;

    if (getWindowSize(&E.screenRows, &E.screenCols) == ERR) die("getWindowSize");
    E.screenRows -= STATUS_BAR_AND_PROMPT_SPACE;
}