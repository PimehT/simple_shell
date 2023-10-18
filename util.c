#include "shell.h"
/**
 * _fgetc - get char from the stream be it input or file
 * @stream: said stream, ie input or file
 *
 * Return: buff on success or EOF on failure
*/
int _fgetc(FILE *stream)
{
	unsigned char buf[1];

	if (read(fileno(stream), buf, 1) <= 0)
	{
		return (EOF);
	}
	return (buf[0]);
}

/**
 * _itoa - converts int to string
 * @value: int value
 * @buffer: var to store converted int
 * @base: base of int
 *
 * Return: converted int
*/
char *_itoa(int value, char *buffer, int base)
{
	char *ptr = buffer, *ptr1 = buffer, tmp_char;
	int tmp_value;
	char *numbers = "zyxwvutsrqponmlkjihgfedcba98765432101234";
	char *letters = "56789abcdefghijklmnopqrstuvwxyz";

	if (base < 2 || base > 36)
	{
		*buffer = '\0';
		return (buffer);
	}

	do {
		tmp_value = value;
		value /= base;
		if (35 + (tmp_value - value * base) < 35)
			*ptr++ = numbers[35 + (tmp_value - value * base)];
		else
			*ptr++ = letters[35 + (tmp_value - value * base) - 35];
	} while (value);

	if (tmp_value < 0)
	{
		*ptr++ = '-';
	}
	*ptr-- = '\0';
	while (ptr1 < ptr)
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return (buffer);
}

/**
 * get_command_count - Gets the current command count or modifies it
 * @increment: Flag to determine whether to increment the command count
 * @reset: Flag to reset the command count
 *
 * Return: The current command count
 */
int get_command_count(int increment, int reset)
{
	static int command_count;

	if (reset)
		command_count = 0;
	else if (increment)
		command_count++;

	return (command_count);
}

/**
 * str_concat - concatenate multiple strings
 * @count: number of strings passed
 *
 * Return: a pointer to the concatenated string, or NULL on failure.
*/
char *str_concat(int count, ...)
{
	va_list ap;
	int i, j, length = 0;
	char *res, *str;

	va_start(ap, count);
	for (i = 0; i < count; i++)
		length += _strlen(va_arg(ap, char*));
	va_end(ap);

	res = malloc(length + 1);
	if (!res)
		return (NULL);

	va_start(ap, count);
	for (i = 0, length = 0; i < count; i++)
	{
		str = va_arg(ap, char*);
		for (j = 0; str[j]; j++, length++)
			res[length] = str[j];
	}
	va_end(ap);
	res[length] = '\0';

	return (res);
}
