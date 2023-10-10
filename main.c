#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char *av)
{
	char *arguments, *token, *prompt = "$ ", *new_l = "\n";
	int status, ret, retn;
	int *execution_return = &retn ;

    if (ac != 1)
	{
		ret = proc_file_commands(av[1], execution_return);
		return (*execution_return);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_FILE && ret != EXIT)
        ret = process_args(execution_return);
		return (*execution_return);
	}
    while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = process_args(execution_return);
		if (ret == END_FILE || ret == EXIT)
		{
			if (ret == END_FILE)
				write(STDOUT_FILENO, new_l, 1);
		}
	}

	return (*execution_return);
}