#include "shell.h"

/**
 * split_line - splits the input string into arguments
 * @line: input string
 *
 * Return: array of strings of user input
*/
char **split_line(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char **tmp = NULL;
	char *token;

	if (!tokens)
	{
		handle_error("Allocation error");
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		/* Resize tokens if we reach bufsize. */
		if (position >= bufsize)
		{
			bufsize *= 2;
			tmp = _realloc(tokens, bufsize * sizeof(char *));
			if (!tmp)
			{
				free(tokens);
				handle_error("Allocation error");
				exit(EXIT_FAILURE);
			}
			tokens = tmp;
		}

		token = _strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * _strtok - splits a string by its delimiters
 * @str: string to split into arrays
 * @delim: the char indicating what point to breadk the sttring
 *
 * Return: broken string
*/
char *_strtok(char *str, const char *delim)
{
	static char *s_next;
	char *token_start;

	if (str)
		s_next = str;

	if (!s_next || !*s_next)
		return (NULL);

	while (*s_next && _strchr(delim, *s_next))
		s_next++;

	token_start = s_next;

	while (*s_next && !_strchr(delim, *s_next))
		s_next++;

	if (*s_next)
	{
		*s_next = '\0';
		s_next++;
	}

	if (!*token_start)  /* If the token is empty, get the next one. */
		return (_strtok(NULL, delim));

	return (token_start);
}

