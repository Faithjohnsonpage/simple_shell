#include "shell.h"

void process_input_interactive(shell_info *info, char *av[], char *builtin_commands[]);
void process_input_non_interactive(shell_info *info, char *av[]);

/**
 * process_input_non_interactive - Process non-interactive shell input.
 * @info: Shell information structure.
 * @av: Array of command line arguments.
 * @builtin_commands: Array of built-in commands.
 */

void process_input_non_interactive(shell_info *info, char *av[])
{
	char *buffer, *trimmed_buffer, *command;
	int num_commands, i;

	buffer = read_user_input_from_stdin();
	if (buffer == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (buffer[0] == '#' || buffer[0] == '\n')
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#')
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}

	trimmed_buffer = trimWhitespaces(buffer);

	if (_strlen(trimmed_buffer) > 0)
	{
		info->command_line = trimmed_buffer;
		tokenization_ins(info, &num_commands);

		for (i = 0; i < num_commands; ++i)
		{
			command = trimWhitespaces(info->argv[i]);
			handle_non_interactive(command, info, av);
			free(info->argv[i]);
		}
		free_aliases(info);
		free(buffer);
		free(info);
		exit(EXIT_SUCCESS);
	}
	else
	{
		free(buffer);
		free(info);
		exit(EXIT_SUCCESS);
	}
}

/**
 * process_input_interactive - Process interactive shell input.
 * @info: Shell information structure.
 * @av: Array of command line arguments.
 * @builtin_commands: Array of built-in commands.
 */

void process_input_interactive(shell_info *info, char *av[], char *builtin_commands[])
{
	char *buffer, *filepath;
	int status = 0, i, flag = 0;

	while (1)
	{
		flag = 0;

		prompt();

		buffer = read_user_input(info);

		if (buffer == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		if (buffer[0] == '\0')
		{
			free(buffer);
			continue;
		}

		if (buffer[0] == '#' || buffer[0] == '\n')
		{
			free(buffer);
			continue;
		}

		info->command_line = buffer;
		tokenization(info);

		/* check if the command is a builtin command and continue */
		for (i = 0; builtin_commands[i] != NULL; i++)
		{
			if (_strcmp(info->argv[0], builtin_commands[i]) == 0)
			{
				flag = 1;
				builtIn_Cmds(info);
				free_tokens(info);
				free_shell_info(info);
				break;
			}
		}

		if (flag == 1)
		{
			continue;
		}

		if (info->argv[0][0] == '/')
		{
			if (access(info->argv[0], X_OK) == 0)
			{
				info->full_path = strdup(info->argv[0]);
				execute_command(info, &status);
				free(info->full_path);
			}
			else
			{
				my_print_to_stderr(av[0]);
				my_print_to_stderr(": ");
				my_print_to_stderr(info->argv[0]);
				my_print_to_stderr(": not found\n");
			}
		}
		else
		{
			filepath = get_location(info);

			if (filepath == NULL)
			{
				my_print_to_stderr(av[0]);
				my_print_to_stderr(": ");
				my_print_to_stderr(info->argv[0]);
				my_print_to_stderr(": not found\n");
			}
			else
			{
				info->full_path = filepath;
				execute_command(info, &status);
				free(info->full_path);
			}
		}
		free_tokens(info);
		free(info->command_line);
	}
	free_aliases(info);
	free_shell_info(info);
}


/**
 * main - The entry point of the shell program.
 * @ac: Number of command line arguments.
 * @av: Array of command line arguments.
 * Return: Always 0.
 */

int main(int ac, char *av[])
{
	shell_info *info = NULL;
	char *builtin_commands[1024] = {"env", "exit", "cd", "alias", NULL};

	if (ac != 1)
	{
		my_print("Usage: ");
		my_print(av[0]);
		my_print("\n");
		exit(EXIT_FAILURE);
	}
	info = malloc(sizeof(shell_info));

	if (info == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	init_shell_info(info);
	signal(SIGINT, sigintHandler);

	if (isatty(STDIN_FILENO))
	{
		process_input_interactive(info, av, builtin_commands);
	}
	else
	{
		process_input_non_interactive(info, av);
	}

	if (info != NULL)
	{
		free(info);
	}
	return (0);
}
