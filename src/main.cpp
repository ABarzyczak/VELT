#include "../include/terminal.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/init.h"
#include "../include/file_io.h"
#include <cstdlib>

int main(int argc, char* argv[]) {
    enableRawMode();
    initEditor();

    if (argc >= 2) {
        editorOpen(argv[1]);
    }

    setStatusMessage("HELP: Ctrl-S = save | HELP: Ctrl-Q = quit");

    while (true) {
        refreshScreen();
        if (E.mode == DEFAULT_MODE) 
            defaultMode();
        else if (E.mode == INSERT_MODE) 
            insertMode();
    }

    return EXIT_SUCCESS;
}