#include "shell.h"

/**
 * executeExitCommand - Handles the "exit" built-in command.
 * Frees memory and exits the shell with the specified status.
 * @info: Pointer to the shell_info structure.
 * @av: Array of command line arguments.
 */

void executeExitCommand_ins(shell_info *info, char *command, char *av[])
{
	char *args[1024], *token;
	int i = 0, j;
	int exit_status = EXIT_SUCCESS;

	token = strtok(command, " \t");
	while (token != NULL)
	{
		args[i] = _strdup(token);
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	/* Check if there is an argument provided after "exit" */
	if (args[1] != NULL)
	{
		exit_status = _atoi(args[1]);

		/* Check if the conversion was successful */
		if (exit_status < 0)
		{
			my_print_to_stderr(av[0]);
			my_print_to_stderr(": 1: ");
			my_print_to_stderr(args[0]);
			my_print_to_stderr(": Illegal number: ");
			my_print_to_stderr(args[1]);
			my_print_to_stderr("\n");

			/* Free memory and exit with a non-zero status */
			free(command);
			for (j = 0; args[j] != NULL; ++j)
			{
				free(args[j]);
			}
			free_aliases(info);
			free(info->command_line);

			free(info);
			exit(2);
		}
	}

	/*Free memory allocated for shell info and exit with the specified status*/
	free(command);
	for (j = 0; args[j] != NULL; ++j)
	{
		free(args[j]);
	}
	free_aliases(info);
	free(info->command_line);
	free(info);
	exit(exit_status);
}


/**
 * executeAliasCommand - Handles the "alias" built-in command.
 * Calls the function to handle alias-related operations.
 * @info: Pointer to the shell_info structure.
 * @command: The alias command to be processed.
 */

void executeAliasCommand_ins(shell_info *info, char *command)
{
	handle_alias_command_ins(info, command);
}





/**
 * handle_alias_command_ins - Handles the 'alias' shell command.
 * @info: Pointer to the shell_info structure.
 * @command: The alias command to be processed.
 */

void handle_alias_command_ins(shell_info *info, char *command)
{
	int i = 0, j;
	char *alias_name, *alias_value, *token;
	char *args[1024], *cmd_args[1024];

	token = strtok(command, " \t");
	while (token != NULL)
	{
		cmd_args[i] = _strdup(token);
		i++;
		token = strtok(NULL, " \t");
	}
	cmd_args[i] = NULL;

	if (cmd_args[1] == NULL)
	{
		/* Print existing aliases */
		for (i = 0; i < info->alias_count; i++)
		{
			my_print(info->aliases[i].alias_name);
			my_print("='");
			my_print(info->aliases[i].command);
			my_print("'\n");
		}
	}
	else
	{
		/* Tokenize input into args */
		token = strtok(cmd_args[1], " ");
		i = 0;
		while (token != NULL)
		{
			args[i] = _strdup(token);
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		i = 0;
		while (args[i] != NULL)
		{
			/* Check if the token contains '=' */
			if (strchr(args[i], '=') != NULL)
			{
				alias_name = strtok(args[i], "=");
				alias_value = strtok(NULL, "'");
				add_alias(info, alias_name, alias_value);
			}
			else
			{
				/* Check if the token matches an existing alias */
				for (j = 0; j < info->alias_count; j++)
				{
					if (_strcmp(args[i], info->aliases[j].alias_name) == 0)
					{
						my_print(info->aliases[j].alias_name);
						my_print("='");
						my_print(info->aliases[j].command);
						my_print("'\n");
						break;
					}
				}
			}

			/* Free memory allocated for the token */
			free(args[i]);
			i++;
		}
	}

	/* Free memory allocated for command tokens */
	for (i = 0; cmd_args[i] != NULL; ++i)
	{
		free(cmd_args[i]);
	}
}


/**
 * executeCdCommand_ins - Handles the "cd" built-in command.
 * Changes the current working directory.
 * @av: Array of command line arguments.
 */

void executeCdCommand_ins(char *command, char *av[])
{
	int i = 0, j;
	char *cwd, *token, *args[1024], *previous_dir;

	token = strtok(command, " \t");
	while (token != NULL)
	{
		args[i] = _strdup(token);
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (args[1] != NULL)
	{
		if (_strcmp(args[1], "-") == 0)
		{
			/* Handle 'cd -' logic to change to the previous directory */
			previous_dir = my_getenv("OLDPWD");
			if (previous_dir != NULL)
			{
				if (chdir(previous_dir) == -1)
				{
					perror("chdir");
				}
			}
			else
			{
				my_print_to_stderr(av[0]);
				my_print_to_stderr(": ");
				my_print_to_stderr("1: ");
				my_print_to_stderr(args[0]);
				my_print_to_stderr(": OLDPWD not set\n");
			}
		}
		else
		{
			if (chdir(args[1]) == -1)
			{
				my_print_to_stderr(av[0]);
				my_print_to_stderr(": ");
				my_print_to_stderr("1: ");
				my_print_to_stderr(args[0]);
				my_print_to_stderr(": can't cd to ");
				my_print_to_stderr(args[1]);
				my_print_to_stderr("\n");
			}
		}
	}
	else
	{
		if (chdir(my_getenv("HOME")) == -1)
		{
			perror("chdir");
		}
	}

	/* Update PWD and OLDPWD environment variables */
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		setenv("OLDPWD", my_getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
		free(cwd);
	}
	else
	{
		perror("getcwd");
	}

	/* Free allocated memory */
	for (j = 0; args[j] != NULL; ++j)
	{
		free(args[j]);
	}

	return;
}
