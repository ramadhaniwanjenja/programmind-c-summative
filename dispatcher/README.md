# Dynamic Function Dispatcher 🔄

A runtime function selection system using function pointers and dynamic memory allocation for file operations.

## Features
- **Dynamic Function Selection**: Runtime function execution using function pointers
- **File Operations**: Add data, count lines/characters, case conversion
- **Memory Management**: Dynamic allocation using `malloc()` and `free()`
- **Menu-Driven Interface**: User-friendly selection system
- **Error Handling**: Robust file and memory error management

## Compilation & Usage
```bash
gcc -o dispatcher dispatcher.c
./dispatcher
```

## Available Operations
```
===== 📁 Dynamic Function Dispatcher =====
1. Add Data to File
2. Count Lines
3. Count Characters
4. Convert to UPPERCASE
5. Convert to lowercase
6. Exit
```

## Core Components

### Function Pointer Structure
```c
typedef struct {
    char *name;
    FunctionHandler handler;
} MenuOption;
```

### Dynamic Menu System
```c
MenuOption *menu = malloc(6 * sizeof(MenuOption));
menu[0] = (MenuOption){"Add Data to File", add_data};
menu[1] = (MenuOption){"Count Lines", count_lines};
// ... additional menu items
```

## File Operations

### Data Addition
- Appends user input to `data.txt`
- Dynamic buffer allocation (1024 bytes)
- Automatic memory cleanup

### Statistics
- **Line Count**: Counts newline characters
- **Character Count**: Total character count including whitespace

### Case Conversion
- **Uppercase**: Converts entire file content to uppercase
- **Lowercase**: Converts entire file content to lowercase
- In-place file modification

## Technical Implementation
- **Function Pointers**: `typedef void (*FunctionHandler)()`
- **Dynamic Memory**: Runtime allocation for menu and buffers
- **File I/O**: Text and binary file operations
- **Memory Safety**: Proper allocation/deallocation patterns

## Target File
- **Default**: `data.txt` (automatically created if not exists)
- **Operations**: All functions operate on this single file