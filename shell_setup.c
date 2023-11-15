#include "shell.h"

/**
 * init_shell_info - Initializes the shell_info structure.
 * @info: Pointer to the shell_info structure.
 */

void init_shell_info(shell_info *info)
{
	int i;

	info->command_line = NULL;
	info->full_path = NULL;
	for (i = 0; i < MAX_ARG_COUNT; ++i)
	{
		info->argv[i] = NULL;
	}
	info->env = NULL;

	info->alias_count = 0;
	info->exit_status = 0;
	for (i = 0; i < MAX_ALIASES; i++)
	{
		info->aliases[i].alias_name = NULL;
		info->aliases[i].command = NULL;
	}
}

/**
 * read_user_input - Reads input from the user.
 * @info: Pointer to the shell_info structure.
 * Return: Pointer to the input string.
 */

char *read_user_input(shell_info *info)
{
	ssize_t num_of_chars = 0;
	size_t buffer_size = 0;
	char *buffer = NULL;

	num_of_chars = getline(&buffer, &buffer_size, stdin);

	if (num_of_chars == -1)
	{
		if (feof(stdin))
		{
			my_print("\n");
			free(buffer);
			free_env_node(info);
			free_tokens(info);
			free_aliases(info);
			free(info);
			exit(EXIT_SUCCESS);
		}
		perror("getline");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	if (num_of_chars > 0 && buffer[num_of_chars - 1] == '\n')
	{
		buffer[num_of_chars - 1] = '\0';
	}

	return (buffer);
}

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C) in the shell.
 * @signum: Signal number.
 */

void sigintHandler(int signum)
{
	/* Shell received SIGINT (Ctrl + C) */
	(void) signum;
	my_print("\n");

	/* Reset the prompt and allow the user to input a new command */
	prompt();
	fflush(stdout);
}

/**
 * tokenization - Tokenizes the command line input.
 * @info: Pointer to the shell_info structure.
 */

void tokenization(shell_info *info)
{
	char *token, *command_copy;
	int i = 0;

	command_copy = _strdup(info->command_line);
	token = strtok(command_copy, " \t;\n");
	if (token != NULL && _strcmp(token, "alias") == 0)
	{
		info->argv[i] = _strdup(token);
		i++;
		token = strtok(NULL, "");
		if (token != NULL)
		{
			info->argv[i] = _strdup(token);
		}
		i++;
		info->argv[i] = NULL;
		free(command_copy);
		return;
	}
	else
	{
		while (token != NULL && i < MAX_ARG_COUNT - 1)
		{
			if (info->argv[i] != NULL)
			{
				free(info->argv[i]);
			}
			info->argv[i] = _strdup(token);
			i++;
			token = strtok(NULL, " \t;\n");
		}
	}
	info->argv[i] = NULL;

	free(command_copy);
}
