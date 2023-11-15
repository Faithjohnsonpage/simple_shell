#include "shell.h"

/**
 * prompt - Displays the shell prompt.
 */

void prompt(void)
{
	my_print("$ ");
}


/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 * Return: Pointer to the duplicated string.
 */

char *_strdup(const char *str)
{
	size_t length = _strlen(str);
	char *duplicate = (char *)malloc(length + 1);

	if (duplicate == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	_strcpy(duplicate, str);

	return (duplicate);
}


/**
 * _strlen - Calculates the length of a string.
 * @s: The input string.
 * Return: Length of the string.
 */

int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: Destination string.
 * @src: Source string.
 */

void _strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
