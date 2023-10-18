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

	read_status = _getline(&line, &len, stdin);
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
	char *bufptr = *lineptr, *p;
	size_t size = *n;
	int c = _fgetc(stream);

	if (!lineptr || !stream || !n || c == EOF)
		return (-1);
	if (!bufptr)
	{
		bufptr = malloc(128);
		if (!bufptr)
			return (-1);
		size = 128;
	}

	for (p = bufptr; c != EOF; c = _fgetc(stream))
	{
		if ((size_t)(p - bufptr) >= (size - 1))
		{
			size += 128;
			bufptr = _realloc(bufptr, size);
			if (!bufptr)
				return (-1);
		}
		*p++ = c;
		if (c == '\n')
			break;
	}

	*p = '\0';
	*lineptr = bufptr;
	*n = size;
	return ((c == EOF && p == bufptr) ? -1 : (p - bufptr));
}
