#ifndef SHELL_H
#define SHELL_H
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_FLUSH -1
#define END_FILE -2
#define EXIT -3
#define MAX_COMMAND_LENGTH 100

extern char **environ;

int process_args(int *execution_return);
char *get_input(char *input, int *exe_ret);
int execute_args(char **args, char **front, int *exe_ret);
int execute(char **args, char **front __attribute__((unused)));
void *_realloc(void *o_pointer, unsigned int o_size, unsigned int n_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *str, char c);

int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif