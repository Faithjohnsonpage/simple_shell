#include "shell.h"

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

char* trimWhitespaces(char *buffer)
{
	char *trimmed_buffer;
	int len;

	trimmed_buffer = buffer;

	/* Trim leading whitespaces */
	while (*trimmed_buffer && (*trimmed_buffer == ' ' || *trimmed_buffer == '\t')) {
		trimmed_buffer++;
	}

	len = strlen(trimmed_buffer);

	/* Trim trailing whitespaces */
	while (len > 0 && (trimmed_buffer[len - 1] == ' ' || trimmed_buffer[len - 1] == '\t' || trimmed_buffer[len - 1] == '\n'))
	{
		trimmed_buffer[len - 1] = '\0';
		len--;
	}

	return (trimmed_buffer);
}
