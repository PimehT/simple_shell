#include "shell.h"

/**
 * execute - execute the user command
 * @args: user command
 *
 * Return: status of execution
*/
int execute(char **args)
{
	pid_t pid;
	int wstatus, status = handle_builtins(args);
	char *executable_path;

	if (status != -1)
		return (status);
	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], X_OK) != 0)
		{
			executable_path = search_path(args[0]);
			if (executable_path)
			{
				execve(executable_path, args, environ);
				free(executable_path);
			}
			else
			{
				handle_command_error("./hsh", args[0]);
			}
		}
		else
		{
			execve(args[0], args, environ);
		}
	}
	else if (pid < 0)
	{
		/* Forking error */
		perror("Error forking");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		waitpid(pid, &wstatus, 0);
		status = WIFEXITED(wstatus) ? WEXITSTATUS(wstatus) : -1;
	}
	return (status);
}
/**
 * handle_builtins - handle command if it is a builtin commadn
 * @args: input arguments
 *
 * Return: non negative number on success, otherwise -1
*/
int handle_builtins(char **args)
{
	int i;

	/* Array of built-in commands */
	BuiltIn builtins[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"setenv", cmd_setenv},
		{"unsetenv", cmd_unsetenv},
		{NULL, NULL}
	};

	/* Check if command is a built-in and execute it */
	for (i = 0; builtins[i].name; i++)
	{
		if (_strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args));
	}

	/*  If not a built-in */
	return (-1);
}
