#include "shell.h"
/**
 * get_input - Gets a command from standard input.
 * @input: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_input(char *input, int *exe_ret) {
  char *prompt = "$ ";
  size_t n = 0;
  ssize_t num_chars, bytes_written;

  if (input)
    free(input);

  num_chars = _getline(&input, &n, STDIN_FILENO);
  if (num_chars == -1)
    return (NULL);
  if (num_chars == 1) {
    if (isatty(STDIN_FILENO)) {
      bytes_written = write(STDOUT_FILENO, prompt, 2);
      if (bytes_written == -1) {
        perror("write error");
      }
    }
    return (get_input(input, exe_ret));
  }
  input[num_chars - 1] = '\0';
  return (input);
}

/**
 * process_args - Gets, calls, and runs the execution of a command.
 * @execution_return: The return value of the parent process' last executed
 * command.
 *
 * Return: If an end-of-file is read - END_FILE (-2).
 */
int process_args(int *execution_return) {
  int ret = 0, index;
  char **args, *input = NULL, **front;

  input = get_input(input, execution_return);
  if (!input)
    return (END_FILE);

  args = _strtok(input, " ");
  free(input);
  if (!args)
    return (ret);
  front = args;
  for (index = 0; args[index]; index++)
	{
		if (strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = execute_args(args, front, execution_return);
			args = &args[++index];
			index = 0;
		}
	}

  if (args)
    ret = execute_args(args, front, execution_return);
  return (ret);
}

/**
 * execute_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int execute_args(char **args, char **front, int *exe_ret) {
  int ret, i;

  *exe_ret = execute(args, front);
  ret = *exe_ret;
  for (i = 0; args[i]; i++)
    free(args[i]);
  return (ret);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front __attribute__((unused))) {
  pid_t child_pid;
  int status, flag = 0, ret = 0;
  char *command = args[0];
  
  child_pid = fork();
  if (child_pid == -1) {
    if (flag)
      free(command);
    perror("Error child:");
    return (1);
  }
  if (child_pid == 0) {
    execve(command, args, environ);
    if (errno == EACCES)
      ret = 1;
    free(args);
    exit(ret);
  } else {
    wait(&status);
    ret = WEXITSTATUS(status);
  }
 
  if (flag)
    free(command);
  return (ret);
}