#include "shell.h"

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: 0 if strings are equal, non-zero otherwise.
 */

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 */

void _strcat(char *dest, const char *src)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';
}

/**
 * _itoa - Converts an integer to a string.
 * @num: Integer to be converted.
 * @str: Buffer to store the converted string.
 * @base: Base for the conversion (e.g., 10 for decimal).
 * Return: Pointer to the converted string.
 */

char *_itoa(int num, char *str, int base)
{
	int i = 0, rem, start, end, isNegative = 0;
	char temp;

	/* Handle 0 explicitly, otherwise empty string is printed */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	/* Handle negative numbers only if base is 10 */
	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}
	while (num != 0)
	{
		rem = num % base;
		if (rem > 9)
			str[i++] = (rem - 10) + 'a';
		else
			str[i++] = rem + '0';
		num = num / base;
	} /* Process individual digits */
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0';
	start = 0;
	end = i - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	} /* Reverse the string */
	return (str);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert.
 * Return: The integer value of the input string.
 */

int _atoi(const char *s)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = result * 10 + (s[i] - '0');
		}
		else
		{
			/* Handle the case where the argument is not a valid integer */
			return (-1);
		}
		i++;
	}

	return (result * sign);
}


/**
 * _strncmp - Compares two strings up to a given number of characters.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The maximum number of characters to compare.
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((int)(s1[i] - s2[i]));
		}
		i++;
	}

	if (i == n)
	{
		return (0);
	}

	if (s1[i] == '\0' && s2[i] == '\0')
	{
		return (0);
	}
	else if (s1[i] == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
