#include "shell.h"

/**
 * handle_error - print the error message if command not found
 * @err: the command that is not found
 *
 * Return: void
*/
void handle_error(char *err)
{
	int line_num = get_command_count(0, 0);

	write(STDERR_FILENO, err, _strlen(err));
	print_err("./hsh", line_num, err);
}

/**
 * print_err - print if the file is not found
 * @shell_name: ./hsh
 * @line_num: the line number of the code
 * @err: error number
 *
 * Return: void
*/
void print_err(char *shell_name, int line_num, char *err)
{
	char buffer[100];
	int len;

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);

	_itoa(line_num, buffer, 10);
	len = _strlen(buffer);
	write(STDERR_FILENO, buffer, len);
	write(STDERR_FILENO, ": ", 2);

	write(STDERR_FILENO, err, _strlen(err));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * handle_command_error - print the error message based on the given error code
 * @prog_name: ./hsh
 * @command: command with error
 * @error_code: specific error code (if set, use this over errno)
 *
 * Return: the exit status associated with the error
 */
int handle_command_error(char *prog_name, char *command, int error_code)
{
	int exit_status = EXIT_FAILURE;

	if (error_code == 0)
		error_code = errno;

	switch (error_code)
	{
		case ENOENT:
			fprintf(stderr, "%s: %s: command not found\n", prog_name, command);
			exit_status = 127;
			break;
		case EACCES:
			fprintf(stderr, "%s: %s: Permission denied\n", prog_name, command);
			exit_status = 126;
			break;
		default:
			perror(prog_name);
			break;
	}

	return (exit_status);
}

/**
 * custom_error - Displays a formatted error message.
 * @prog_name: Name of the program causing the error.
 * @command: The command or function causing the error.
 * @message: A custom message to describe the error.
 *
 * Return: void
 */
void custom_error(const char *prog_name, const char *command,
		const char *message)
{
	char line_num[12];  /* Enough for most integers */
	int count = get_command_count(0, 0);

	_itoa(count, line_num, 10);

	write(STDERR_FILENO, prog_name, _strlen(prog_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, line_num, _strlen(line_num));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
}
