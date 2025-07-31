# Mini Shell 🐚

A custom command-line shell implementation supporting basic Unix commands, I/O redirection, and piping functionality.

## Features
- **Command Execution**: Run standard Unix commands (`ls`, `cat`, `pwd`, etc.)
- **I/O Redirection**: Input (`<`) and output (`>`) redirection support
- **Piping**: Connect commands using pipe operator (`|`)
- **Process Management**: Fork-based command execution
- **Built-in Commands**: Exit command for clean termination

## Compilation
```bash
gcc -o mini_shell mini_shell.c
./mini_shell
```

## Usage Examples

### Basic Commands
```bash
MiniShell$ ls -la
MiniShell$ cat file.txt
MiniShell$ pwd
```

### I/O Redirection
```bash
MiniShell$ ls > output.txt
MiniShell$ cat < input.txt
MiniShell$ sort < data.txt > sorted.txt
```

### Piping
```bash
MiniShell$ ls -l | grep txt
MiniShell$ cat file.txt | wc -l
MiniShell$ ps aux | grep shell
```

### Exit
```bash
MiniShell$ exit
```

## Technical Implementation
- **Process Creation**: Uses `fork()` and `execvp()` for command execution
- **File Descriptors**: `dup2()` for I/O redirection
- **Inter-Process Communication**: Anonymous pipes for command chaining
- **Memory Management**: Dynamic argument parsing and cleanup

## Limitations
- No background process support (`&`)
- No command history or tab completion
- No environment variable expansion
- Single pipe support only