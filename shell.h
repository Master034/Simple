#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_FLUSH -1
#define END_FILE -2
#define EXIT -3
#define MAX_COMMAND_LENGTH 100

extern char **environ;

int exec_file_commands(char *file_path, int *last_return);
int process_args(int *exe_ret);

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *str, char c);

int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

#endif