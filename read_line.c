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
	char *bufptr = NULL;
	char *p = NULL;
	size_t size;
	int c;

	if (lineptr == NULL || stream == NULL || n == NULL)
		return (-1);

	bufptr = *lineptr;
	size = *n;
	c = _fgetc(stream);
	if (c == EOF)
		return (-1);
	if (bufptr == NULL)
	{
		bufptr = malloc(128);
		if (bufptr == NULL)
			return (-1);
		size = 128;
	}
	p = bufptr;
	while (c != EOF)
	{
		if ((size_t)(p - bufptr) >= (size - 1))
		{
			size = size + 128;
			bufptr = _realloc(bufptr, size);
			if (bufptr == NULL)
				return (-1);
		}
		*p++ = c;
		if (c == '\n')
			break;
		c = _fgetc(stream);
	}
	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return (p - bufptr - 1);
}
