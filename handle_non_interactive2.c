#include "shell.h"

/**
 * handle_non_interactive - Handles non-interactive mode based on command.
 *
 * @command: The command to be executed.
 * @info: Pointer to the shell_info structure.
 * @av: Array of command line arguments.
 */

void handle_non_interactive(char *command, shell_info *info, char *av[])
{
	char *cmd_path, *args[1024], *token;
	int i = 0, j;

	if (is_builtin_command(command))
	{
		/* handle built-in commands */
		handle_builtin_commands(command, info, av);
	}
	else if (command[0] == '/')
	{
		execute_command_ins(command, av);
	}
	else
	{
		token = strtok(command, " \t");
		while (token != NULL)
		{
			args[i] = _strdup(token);
			i++;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		/* Check if the command is an alias */
		if (is_alias(info, args[0]))
		{
			/* Expand and execute the alias */
			expand_and_execute_alias(info, args);
		}
		else
		{
			cmd_path = get_location_ins(args[0]);

			if (cmd_path == NULL)
			{
				my_print_to_stderr(av[0]);
				my_print_to_stderr(": ");
				my_print_to_stderr(args[0]);
				my_print_to_stderr(": not found\n");
			}
			else
			{
				info->full_path = cmd_path;
				execute_cmd_from_paths(info, args);
				free(info->full_path);
			}
		}
		for (j = 0; args[j] != NULL; ++j)
		{
			free(args[j]);
		}
	}
}


/**
 * is_builtin_command - Checks if the given command is a built-in command.
 *
 * @command: The command to be checked.
 *
 * Return: 1 if the command is built-in, 0 otherwise.
 */

int is_builtin_command(char *command)
{
	char *builtin_commands[] = {"env", "exit", "cd", "alias", NULL};
	int i;

	for (i = 0; builtin_commands[i] != NULL; i++)
	{
		if (_strcmp(command, builtin_commands[i]) == 0)
		{
			return 1;  /* It is a built-in command */
		}
	}

	return 0;  /* It is not a built-in command */
}


/**
 * handle_builtin_commands - Executes the appropriate built-in commands.
 *
 * @command: The built-in command to be executed.
 * @info: Pointer to the shell_info structure.
 * @av: Array of command line arguments.
 */

void handle_builtin_commands(char *command, shell_info *info, char *av[])
{
	if (_strcmp(command, "exit") == 0)
	{
		executeExitCommand_ins(info, command, av);
	}
	else if (_strcmp(command, "env") == 0)
	{
		executeEnvCommand();
		return;
	}
	else if (_strcmp(command, "cd") == 0)
	{
		executeCdCommand_ins(command, av);
		return;
	}
	else if (_strcmp(command, "alias") == 0)
	{
		executeAliasCommand_ins(info, command);
		return;
	}
}

/**
 * is_alias - Checks if a given command is an alias.
 * @info: Pointer to the shell_info structure.
 * @command: Command to check.
 * Return: 1 if the command is an alias, 0 otherwise.
 */

int is_alias(shell_info *info, char *command)
{
	int i;

	for (i = 0; i < info->alias_count; ++i)
	{
		if (_strcmp(info->aliases[i].alias_name, command) == 0)
		{
			return (1); /* The command is an alias */
		}
	}

	return (0); /* The command is not an alias */
}

/**
 * expand_and_execute_alias - Expands and executes the specified alias.
 * @info: Pointer to the shell_info structure.
 * @args: Array of strings containing the alias name and its arguments.
 * @av: Array of strings containing the program name and its arguments.
 */

void expand_and_execute_alias(shell_info *info, char *args[])
{
	int i;
	char *expanded_command = NULL;

	/* Find the alias in the list */
	for (i = 0; i < info->alias_count; ++i)
	{
		if (_strcmp(info->aliases[i].alias_name, args[0]) == 0)
		{
			/* Expand the alias with its associated command */
			expanded_command = _strdup(info->aliases[i].command);
			break;
		}
	}

	if (expanded_command != NULL)
	{
		/* Execute the expanded command */
		execute_command_alias(expanded_command, args);
		free(expanded_command);
	}
	else
	{
		my_print_to_stderr("Alias expansion failed: Alias not found\n");
	}
}

