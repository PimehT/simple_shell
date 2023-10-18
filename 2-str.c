#include "shell.h"

/**
* _strchr - locates a character in a string
* @s: the string
* @c: the character
*
* Return: A pointer to the first occurrence of the character.
*/
char *_strchr(const char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return ((char *)(s + i));
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

/**
 * _strcmp - compares string 1 with string 2
 * @s1: first string
 * @s2: second string
 * Return: positive int if @s1 is greater,
 * negative int if @s2 is greater
 * and zero if @s1 and @s2 are equal
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
* _strncpy - function that copies a string
* @src: the source string
* @dest: the destination string
* @n: number of characters to copy
* Return: pointer to the destination string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, count;

	count = 0;
	while (src[count] != 0)
		count++;
	for (i = 0; src[i] && i < n; i++)
		dest[i] = src[i];
	for (i = count; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
* _memcpy - copies memory area
* @dest: destination memory area
* @src: source memory area
* @n: number of bytes to copy
*
* Return: pointer to the destination memory area
*/
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}

/**
* _realloc - reallocates a memory block using malloc() and free()
* @ptr: original memory block
* @new_size: new size of the block
*
* Return: pointer to the new block
*/
void *_realloc(void *ptr, size_t new_size)
{
	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		void *new_ptr = malloc(new_size);

		if (new_ptr == NULL)
		{
			return (NULL);
		}
		else
		{
			_memcpy(new_ptr, ptr, new_size);
			free(ptr);
			return (new_ptr);
		}
	}
}
