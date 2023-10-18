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
	char *path_copy = _strdup(path_var);
	char *dir = _strtok(path_copy, ":");
	char *executable_path = malloc(512); /* assuming a max path length */
	char *temp;

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

