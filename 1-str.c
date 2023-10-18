#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - returns the length of a string
 * @s: string to be checked
 * Return: length of string
 */
int _strlen(const char *s)
{
	int length;

	length = 0;
	while (s[length] != 0)
		length++;
	return (length);
}


/**
 * _strcat - appends the source string to the destination string
 * overwriting the terminating null byte (\0)
 * @src: source string
 * @dest: destination string
 * Return: pointer to the resulting dest
 */
char *_strcat(char *dest, const char *src)
{
	int i, count;

	count = 0;
	while (dest[count] != 0)
		count++;
	for (i = 0; src[i]; i++)
		dest[count++] = src[i];

	return (dest);
}

/**
 * _strdup - creates copy of string in new allocated memory
 * @str: source string
 *
 * Return: pointer of string copy
 */
char *_strdup(const char *str)
{
	int len = _strlen(str);
	char *str1 = NULL;

	if (str == NULL)
		return (NULL);

	str1 = (char *)malloc((len + 1) * sizeof(char));
	if (str1 == NULL)
		return (NULL);

	_strcpy(str1, str);
	return (str1);
}

/**
 * _strcpy - copies string pointed to by src, to buffer
 * @src: source string
 * @dest: buffer ie. the destination of copied string
 * Return: pointer to buffer
 */
char *_strcpy(char *dest, const char *src)
{
	int i, c, c1;

	c = 0;
	while (*(src + c) != '\0')
		c++;
	c1 = c + 1;
	for (i = 0; i < c1; i++)
		*(dest + i) = *(src + i);
	return (dest);
}

