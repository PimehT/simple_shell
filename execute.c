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
	struct stat st;

	if (status != -1)
		return (status);

	if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
		executable_path = args[0];
	else
	{
		executable_path = search_path(args[0]);
		if (!executable_path)
		{
			status = handle_command_error(args[0], args[0], ENOENT);
			return (status);
		}
	}

	pid = fork();
	if (pid == 0)
	{
		execve(executable_path, args, environ);
		status = handle_command_error(args[0], args[0], 0);
		exit(status);
	} else if (pid < 0)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	} else
	{
		waitpid(pid, &wstatus, 0);
		status = WIFEXITED(wstatus) ? WEXITSTATUS(wstatus) : -1;
	}

	if (executable_path != args[0])
		free(executable_path);  /* Only free if we allocated new memory */

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
