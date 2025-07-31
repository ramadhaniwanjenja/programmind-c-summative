#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CMD 1024
#define MAX_ARGS 100

// Parse a command into arguments
void parse_command(char *cmd, char **args) {
    int i = 0;
    char *token = strtok(cmd, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

// Execute a command with optional I/O redirection
void execute_command(char **args, char *infile, char *outfile) {
    pid_t pid = fork();
    if (pid == 0) {
        if (infile) {
            int fd_in = open(infile, O_RDONLY);
            if (fd_in < 0) {
                perror("Input redirection failed");
                exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (outfile) {
            int fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output redirection failed");
                exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
}

// Execute two commands connected by a pipe
void execute_pipe(char **args1, char **args2) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(args1[0], args1);
        perror("execvp pipe part 1 failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(args2[0], args2);
        perror("execvp pipe part 2 failed");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}

int main() {
    char input[MAX_CMD];
    char *args1[MAX_ARGS], *args2[MAX_ARGS];
    char *infile = NULL, *outfile = NULL;

    while (1) {
        printf("MiniShell$ ");
        fflush(stdout);
        if (!fgets(input, MAX_CMD, stdin)) break;

        if (strncmp(input, "exit", 4) == 0)
            break;

        infile = outfile = NULL;
        char *pipe_pos = strchr(input, '|');

        if (pipe_pos) {
            // Handle pipe
            *pipe_pos = '\0';
            char *cmd1 = input;
            char *cmd2 = pipe_pos + 1;

            parse_command(cmd1, args1);
            parse_command(cmd2, args2);
            if (args1[0] && args2[0])
                execute_pipe(args1, args2);
        } else {
            // Handle I/O redirection
            char *in_pos = strchr(input, '<');
            char *out_pos = strchr(input, '>');

            if (in_pos) {
                *in_pos = '\0';
                infile = strtok(in_pos + 1, " \t\n");
            }

            if (out_pos) {
                *out_pos = '\0';
                outfile = strtok(out_pos + 1, " \t\n");
            }

            parse_command(input, args1);
            if (args1[0])
                execute_command(args1, infile, outfile);
        }
    }

    return 0;
}
