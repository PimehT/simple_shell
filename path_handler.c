#include "shell.h"

/**
 * search_path - search for the path of the executable command
 * @cmd: executable file to find
 *
 * Return: path to file
*/
char *search_path(char *cmd)
{
	char *path_var = _getenv("PATH");
	char *path_copy;
	char *dir;
	char *executable_path = NULL;
	char *temp;

	if (!path_var || _strlen(path_var) == 0)
		return (NULL);
	path_copy = _strdup(path_var);
	dir = _strtok(path_copy, ":");

	while (dir)
	{
		temp = malloc(_strlen(dir) + _strlen(cmd) + 2);
		if (!temp)
		{
			free(path_copy);
			return (NULL);
		}

		_memset(temp, 0, _strlen(dir) + _strlen(cmd) + 2);
		_strcpy(temp, dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (access(temp, X_OK) == 0)
		{
			executable_path = temp;
			break;
		}

		free(temp); /* Free memory if command is not found in current directory */
		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	return (executable_path);
}
