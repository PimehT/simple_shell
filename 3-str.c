#include "shell.h"

/**
 * _puts - prints a string to the stdout
 * @str: the string to be printed
 * Return: the string
 */
void _puts(char *str)
{
	int i;
	int c;

	for (i = 0; *(str + i) != 0; i++)
	{
		c = *(str + i);
		_putchar(c);
	}
}

/**
 * _memset - fills memory with a constant byte
 * @s: memory area to be filled
 * @b: character to fill @s with
 * @n: number of bytes in @s to be filled
 *
 * Return: pointer to memory area @s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * _strpbrk - searches a string for any of a set of bytes
 * @s: the string checked
 * @accept: the set of bytes compared with
 *
 * Return: pointer to the byte in s that matches
 */
char *_strpbrk(char *s, char *accept)
{
	int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				return (s + i);
			}
		}
	}

	return (0);
}

/**
 * _strncmp - Compare two strings up to a maximum of n bytes.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * @n: The maximum number of bytes to compare.
 *
 * Return: An integer less than, equal to, or greater than 0 if str1 is found
 * respectively, to be less than, to match, or be greater than str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == '\0')
			return (0);
	}
	return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 * Return: integer
 */
int _atoi(char *s)
{
	int i = 0, num = 0, sign = 1;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + (s[i] - '0');
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
		}
		i++;
	}

	return (num * sign);
}
