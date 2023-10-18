#include "shell.h"

/**
 * cmd_exit - function to exit the shell program
 * @args: command arguments
 *
 * Return: 1 on success
*/
int cmd_exit(char **args)
{
	int status = 0;

	if (args[1]) /* If there's an argument to exit, use it as the status. */
		status = _atoi(args[1]);
	exit(status);
	return (1);
}

/**
 * get_last_status - to get last exit status
 *
 * Return: status
 */
int get_last_status(void)
{
	return (execute(NULL));
}

/**
 * cmd_env - func to print the environment variables
 * @args: command arguments
 *
 * Return: 1 on success
*/
int cmd_env(char **args)
{
	int i, j, count = 0;
	char *temp;

	(void)args;

	/* Counting the number of environment variables */
	while (environ[count])
		count++;

	/* Bubble sort to order the environ variable */
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (_strcmp(environ[j], environ[j + 1]) > 0)
			{
				temp = environ[j];
				environ[j] = environ[j + 1];
				environ[j + 1] = temp;
			}
		}
	}

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * cmd_setenv - func to set custom environment variable
 * @args: command arguments
 *
 * Return: 0 on success
*/
int cmd_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: Usage: setenv VARIABLE VALUE\n", 36);
		return (1);
	}

	/* Attempt to set or overwrite the variable */
	if (_setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}

/**
 * cmd_unsetenv - func to unset the environment variable
 * @args: command arguments
 *
 * Return: 0 on success
*/
int cmd_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: Usage: unsetenv VARIABLE\n", 34);
		return (1);
	}

	/* Attempt to remove the variable */
	if (_unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (1);
	}

	return (0);
}
