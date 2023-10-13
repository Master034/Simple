#include "shell.h"

void *_realloc(void *o_pointer, unsigned int o_size, unsigned int n_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @o_pointer: A pointer to the memory previously allocated.
 * @o_size: The size in bytes of the allocated space for ptr.
 * @n_size: The size in bytes for the new memory block.
 *
 * Return: If n_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *o_pointer, unsigned int o_size, unsigned int n_size) {
  unsigned int index;
  void *buffer;
  char *temp, *filler;

  if (n_size == o_size)
    return (o_pointer);

  if (o_pointer == NULL) {
    buffer = malloc(n_size);
    if (buffer == NULL)
      return (NULL);
    return (buffer);
  }

  if (n_size == 0 && o_pointer != NULL) {
    free(o_pointer);
    return (NULL);
  }

  temp = o_pointer;
  buffer = malloc(sizeof(*temp) * n_size);
  if (buffer == NULL) {
    free(o_pointer);
    return (NULL);
  }

  filler = buffer;

  for (index = 0; index < o_size && index < n_size; index++)
    filler[index] = *temp++;

  free(o_pointer);
  return (buffer);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b) {
  if (*lineptr == NULL) {
    if (b > 120)
      *n = b;
    else
      *n = 120;
    *lineptr = buffer;
  } else if (*n < b) {
    if (b > 120)
      *n = b;
    else
      *n = 120;
    *lineptr = buffer;
  } else {
    strcpy(*lineptr, buffer);
    free(buffer);
  }
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
  static ssize_t input;
  ssize_t ret;
  char c = 'x', *buffer;
  int r = -1;

  if (input == 0)
    fflush(stream);
  else
    return (-1);
  input = 0;

  buffer = malloc(sizeof(char) * 120);
  if (!buffer)
    return (-1);

  while (c != '\n') {
    r = read(STDIN_FILENO, &c, 1);
    if (r == -1 || (r == 0 && input == 0)) {
      free(buffer);
      return (-1);
    }
    if (r == 0 && input != 0) {
      input++;
      break;
    }

    if (input >= 120)
      buffer = _realloc(buffer, input, input + 1);

    buffer[input] = c;
    input++;
  }
  buffer[input] = '\0';

  assign_lineptr(lineptr, n, buffer, input);

  ret = input;
  if (r != 0)
    input = 0;
  return (ret);
}
