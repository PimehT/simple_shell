#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

extern char **environ;
extern int errno;

/**
 * struct BuiltIn - struct of different builtin and their struct
 * @name: name of builtin command
 * @func: corresponding function to execute
 *
 * Description: struct of different builtins and their functions
*/
typedef struct BuiltIn
{
	char *name;
	int (*func)(char **args);
} BuiltIn;


/* Function Prototypes */
char *read_line(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

char **split_line(char *line);
char *_strtok(char *str, const char *delim);

char *search_path(char *cmd);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _putenv(char *string);
int _unsetenv(const char *name);

int execute(char **args);
int handle_builtins(char **args);
int cmd_exit(char **args);
int get_last_status(void);
int cmd_env(char **args);
int cmd_setenv(char **args);
int cmd_unsetenv(char **args);

char *_strchr(const char *s, char c);
int _strcmp(const char *s1, const char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int new_size);
int _putchar(char c);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
void _puts(char *str);
char *_memset(char *s, char b, unsigned int n);
char *_strpbrk(char *s, char *accept);
int _strncmp(const char *str1, const char *str2, size_t n);
int _atoi(char *s);

void handle_error(char *err);
void print_err(char *shell_name, int line_num, char *err);
void handle_command_error(char *shell_name, char *err);
void custom_error(const char *prog_name, const char *command,
		const char *message);

int _fgetc(FILE *stream);
char *_itoa(int value, char *buffer, int base);
int get_command_count(int increment, int reset);


#endif /* SHELL_H */
