#include "shell.h"

/**
 * search_path - search for the path of the executable command
 * @cmd: executable file to find
 *
 * Return: path to file
*/
char *search_path(char *cmd)
{
	char *path_var = NULL;
	char *path_copy = NULL;
	char *dir = NULL;
	char *executable_path = NULL;
	char *temp;

	path_var = _getenv("PATH");
	if (!path_var || _strlen(path_var) == 0)
		return (NULL);
	path_copy = _strdup(path_var);
	dir = _strtok(path_copy, ":");
	executable_path = malloc(512); /* assuming max length */

	while (dir)
	{
		temp = _strcat(dir, "/");
		_strcat(temp, cmd);

		if (_strlen(temp) < 512)
			_strcpy(executable_path, temp);

		/*  Check if the command exists and is executable in the current 'dir' */
		if (access(executable_path, X_OK) == 0)
		{
			free(path_copy);
			return (executable_path); /* Found the executable in PATH */
		}

		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	free(executable_path);
	return (NULL); /* Command not found in PATH */
}

