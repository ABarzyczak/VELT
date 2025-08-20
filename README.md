# VELT

A lightweight terminal-based text editor built in C++ for Windows and Linux, featuring Vim-style navigation, efficient ANSI escape rendering, and a modular codebase.

## Features

- **Modal editing**: Vim-like modes (DEFAULT and INSERT) for navigation and text entry
- **Cross-platform**: Runs on Windows and Linux terminals
- **File loading and saving**: Open and edit text files, save with `Ctrl+S`
- **Status bar**: Shows file name, line count, and modification state
- **Message bar**: Displays warnings, help, and status messages
- **Efficient screen rendering**: Uses an append buffer for fast updates
- **Modular architecture**: Clean code separation for easy extension

## Usage

## Making VELT available globally

### Bash (Linux, WSL, Git Bash)
You can automate adding the `VELT/bin` directory to your PATH by running the provided Bash script:

```bash
bash add_bash.sh
```
This will append the correct path to your `~/.bashrc` file, making `velt` available in Bash terminals.

### Windows Command Prompt (cmd)
To use `velt` in Windows Command Prompt or PowerShell, you must manually add the `bin` folder to your user environment variables:

1. Open the Start menu and search for "Environment Variables".
2. Click "Edit the system environment variables".
3. In the System Properties window, click "Environment Variables".
4. Under "User variables", select `PATH` and click "Edit".
5. Click "New" and add `C:\Users\olekb\projects\VELT\bin`.
6. Click "OK" to save.

### Build

1. Ensure you have a C++17 compiler (e.g., g++ on Linux, MinGW on Windows)
2. Run `make` in the project directory to build:
	 ```
	 make
	 ```

### Run

After building, you can start VELT from the terminal:

**Bash (Linux, WSL, Git Bash):**
```bash
velt [filename]
```
If you added `VELT/bin` to your PATH, you can run `velt` from any directory. Otherwise, run it from the `bin` folder:
```bash
./bin/velt [filename]
```

**Windows Command Prompt or PowerShell:**
```
velt [filename]
```
If you added `VELT/bin` to your PATH, you can run `velt.exe` from any directory. Otherwise, run it from the `bin` folder:
```
bin\velt [filename]
```

Replace `[filename]` with the file you want to edit.

### Keybindings

- **Arrow keys**: Move cursor
- **Page Up/Down**: Move by pages
- **Ctrl+S**: Save changes
- **Ctrl+Q**: Quit (prompts if unsaved changes)
- **i**: Enter insert mode
- **ESC**: Return to default mode

#### Vim-like keybindings (in DEFAULT mode)
- **h**: Move cursor left
- **j**: Move cursor down
- **k**: Move cursor up
- **l**: Move cursor right
- **H**: Move to top of screen
- **M**: Move to middle of screen
- **L**: Move to bottom of screen

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request