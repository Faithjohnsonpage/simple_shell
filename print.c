#include "shell.h"

char *trimWhitespaces(char *buffer);

/**
 * my_print - Custom implementation of printf to write to stdout.
 * @string: The string to be written to stdout.
 */

void my_print(const char *string)
{
	write(STDOUT_FILENO, string, _strlen(string));
	fflush(stdout);
}


/**
 * my_print_to_stderr - Writes a string to the standard error (stderr).
 * @string: The string to be written.
 *
 * Description: This function writes the given string to the standard error
 * output (stderr) without buffering. It ensures immediate visibility of the
 * output and maintains consistency across different parts of the program.
 */

void my_print_to_stderr(const char *string)
{
	write(STDERR_FILENO, string, _strlen(string));
	fflush(stderr);
}


/**
 * trimWhitespaces - Trim leading and trailing whitespaces from a string.
 * @buffer: The input string to be trimmed.
 *
 * Return: A pointer to the modified string.
 */

char *trimWhitespaces(char *buffer)
{
	char *t; /* t = trimmed_buffer */
	int l; /* l = length */

	t = buffer;

	/* Trim leading whitespaces */
	while (*t && (*t == ' ' || *t == '\t'))
		t++;

	l = _strlen(t);

	/* Trim trailing whitespaces */
	while (l > 0 && (t[l - 1] == ' ' || t[l - 1] == '\t' || t[l - 1] == '\n'))
	{
		t[l - 1] = '\0';
		l--;
	}

	return (t);
}
