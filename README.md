# VELT

A lightweight terminal-based text editor built in C++ for Windows and Linux, featuring Vim-style navigation, efficient ANSI escape rendering, and a modular codebase.

## Features

- **Cross-platform**: Runs on Windows and Linux terminals
- **File loading and saving**: Open and edit text files, save with `Ctrl+S`
- **Status bar**: Shows file name, line count, and modification state
- **Message bar**: Displays warnings, help, and status messages
- **Efficient screen rendering**: Uses an append buffer for fast updates
- **Modular architecture**: Clean code separation for easy extension

## Usage

### Build

1. Ensure you have a C++17 compiler (e.g., g++ on Linux, MinGW on Windows)
2. Run `make` in the project directory to build:
	 ```
	 make
	 ```
     
### Run

// To start the editor and open a file (or create if it doesn't exist):
```
make run
```
**Note:** Currently, the filename is hardcoded as `file.txt` in the Makefile's `run` command. To open a different file, you must edit the Makefile and change the argument in the `run` target. This is a temporary limitation and will be improved in the future.
// If no filename is given, the editor opens an empty buffer.

### Keybindings

- **Arrow keys**: Move cursor
- **Page Up/Down**: Move by pages
- **Ctrl+S**: Save changes
- **Ctrl+Q**: Quit (prompts if unsaved changes)

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request