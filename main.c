#include "shell.h"

/**
 * main - entry point of the code
 *
 * Return: 0 on success
*/
int main(void)
{
	char *line;
	char **args;
	int i, exit_status = 0;

	errno = 0;

	while (1)
	{

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		if (line == NULL)
			break;
		args = split_line(line);
		if (args[0] != NULL)
		{
			get_command_count(1, 0);
			exit_status = execute(args);
		}
		for (i = 0; args[i] != NULL; i++)
			args[i] = NULL;

		free(args);
		free(line);
	}
	exit(exit_status);
}
