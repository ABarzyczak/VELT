#include "../include/file_io.h"
#include "../include/editor_config.h"
#include "../include/terminal.h"
#include "../include/input.h"
#include "../include/constants.h"
#include "../include/rowOperations.h"
#include "../include/output.h"
#include "../include/modes.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>

void editorOpen(char *filename) {

    if (E.fileName != nullptr)
        free(E.fileName);
    
    E.fileName = strdup(filename);

    std::fstream file(filename); 
    if (!file.good()) {
        file << "";
        return;
    }

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) 
        lineCount++;
    
    if (lineCount == 0) {
        file.close();
        return;
    }

    file.clear();
    file.seekg(0, std::ios::beg);   // Reset file stream to the beginning

    size_t lineLength = 0;

    while (std::getline(file, line)) {
        lineLength = line.length();
        rowInsert(E.fileRows, line.c_str(), lineLength);
    }

    E.fileRows = lineCount;
    file.close();

    if (E.fileRows == 0) {
        rowInsert(E.fileRows, "", 0);
    }

    E.dirty = 0;
}

void editorSave() {
    if(E.fileName == NULL)
    {
        E.fileName = promptMode(const_cast<char *>("Save as: %s (ESC to cancel)"));
        if(E.fileName == NULL)
        {
            E.mode = DEFAULT_MODE;
            setStatusMessage("Save aborted");
            return;
        }
    }

    size_t bufLength = 0;
    char *buffer = rowsToString(&bufLength);
    if (buffer == nullptr) {
        die("Failed to convert rows to string");
        return;
    }

    std::ofstream file(E.fileName);
    if (!file.is_open()) {
        free(buffer);
        die("Could not open file for writing");
        return;
    }

    file.write(buffer, bufLength);
    if (file.fail()) {
        free(buffer);
        file.close();
        E.dirty = 0;
        setStatusMessage("can't save! I/O error: %s", strerror(errno));
        return;
    }
    file.close();
    
    E.dirty = 0;
    free(buffer);
    setStatusMessage("data saved", bufLength);
}