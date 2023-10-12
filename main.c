#include "./shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main() {
  char *prompt = "$ ", *new_l = "\n";
  int ret = 0, retn;
  int *execution_return = &retn;
  ssize_t bytes_written;

  if (!isatty(STDIN_FILENO)) {
    while (ret != END_FILE && ret != EXIT)
      ret = process_args(execution_return);
    return (*execution_return);
  }
  while (1) {
    bytes_written = write(STDOUT_FILENO, prompt, 2);
    if (bytes_written == -1) {
      perror("write error");
    }
    ret = process_args(execution_return);
    if (ret == END_FILE || ret == EXIT) {
      if (ret == END_FILE) {
        bytes_written = write(STDOUT_FILENO, new_l, 1);
        if (bytes_written == -1) {
          perror("write error");
        }
      }
      exit(*execution_return);
    }
  }
  return (*execution_return);
}