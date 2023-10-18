#include "shell.h"

/**
 * read_line - user input to be gotten and used
 *
 * Return: string of user input
*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_status;

	read_status = getline(&line, &len, stdin);
	if (read_status == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * _getline - function to get user input
 * @lineptr: where input is stored
 * @n: size of the string
 * @stream: source of user input
 *
 * Return: size of input on success, otherwise -1
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	const size_t initial_size = 100;
	char ch;
	char *tmp = NULL;
	size_t idx = 0;

	if (!*lineptr)
	{
		*lineptr = malloc(initial_size);
		if (!*lineptr)
			return (-1);
		*n = initial_size;
	}

	while ((ch = _fgetc(stream)) != EOF && ch != '\n')
	{
		(*lineptr)[idx++] = ch;
		if (idx == *n)
		{
			tmp = _realloc(*lineptr, *n * 2);
			if (!tmp)
			{
				free(*lineptr);
				return (-1);
			}
			*lineptr = tmp;
			*n *= 2;
		}
	}

	if (idx == 0 && ch == EOF)
		return (-1);

	(*lineptr)[idx] = '\0';

	return (idx);
}
