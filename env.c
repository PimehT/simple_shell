#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: name of the variable
 *
 * Return: pointer to variable
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = _strlen(name);

	if (!environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
	}

	return (NULL);
}

/**
 * _setenv - set a custom environment variable
 * @name: variable added/overwritten to the environment
 * @value: value of the variable @name
 * @overwrite: check if to overwrite or not
 *
 * Return: 0 on success
*/
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_val = _getenv(name);
	char *new_env_var = NULL;
	size_t len;

	/* Check if the variable already exists */
	if (env_val != NULL)
	{
		/* If overwrite is zero, we leave the variable as is */
		if (overwrite == 0)
			return (0);

		/* Else, remove the existing variable */
		_unsetenv(name);
	}

	/* Add new environment variable */
	len = _strlen(name) + _strlen(value) + 2; /* +2 for '=' and '\0' */
	new_env_var = malloc(len * sizeof(char));

	if (!new_env_var)
		return (-1);
	_strcpy(new_env_var, name);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);

	_putenv(new_env_var);

	return (0);
}

/**
 * _putenv - adds or changes the value of environment variables
 * @string: remove string in the form of "name=value"
 *
 * Return: 0 on success, otherwise non zero value
*/
int _putenv(char *string)
{
	char *name, *value;
	char **new_environ;
	int i, len;

	/* Splitting the string into name and value */
	name = _strtok(string, "=");
	value = _strtok(NULL, "");

	if (!name || !value)
		return (-1);

	len = _strlen(name);

	/* Check if the variable already exists in the environment */
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* Modify the existing variable */
			environ[i] = string;
			return (0);
		}
	}

	/* If it doesn't exist, add a new one */
	new_environ = _realloc(environ, (i + 2) * sizeof(char *));
	if (!new_environ)
		return (-1);

	new_environ[i] = string;
	new_environ[i + 1] = NULL;

	environ = new_environ;

	return (0);
}

/**
 * _unsetenv - remove an environment variable
 * @name: points to the string to be removed
 *
 * Return: 0 on success, otherwise -1
*/
int _unsetenv(const char *name)
{
	int i = 0;
	int len = 0;

	if (name == NULL || *name == '\0' || _strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	len = _strlen(name);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* Remove this environment variable by shifting others down */
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

