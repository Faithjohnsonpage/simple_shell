#include "shell.h"

/**
 * executeEnvCommand - Handles the "env" built-in command.
 * Prints the environment variables.
 */

void executeEnvCommand(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		my_print(*env);
		my_print("\n");
	}
}

/**
 * executeExitCommand - Handles the "exit" built-in command.
 * Frees memory and exits the shell with the specified status.
 * @info: Pointer to the shell_info structure.
 */

void executeExitCommand(shell_info *info)
{
	int exit_status = EXIT_SUCCESS;

	/* Check if there is an argument provided after "exit" */
	if (info->argv[1] != NULL)
	{
		exit_status = _atoi(info->argv[1]);
	}

	/*Free memory allocated for shell info and exit with the specified status*/
	free_tokens(info);
	free_shell_info(info);
	free_aliases(info);
	free(info);
	exit(exit_status);
}

/**
 * executeAliasCommand - Handles the "alias" built-in command.
 * Calls the function to handle alias-related operations.
 * @info: Pointer to the shell_info structure.
 */

void executeAliasCommand(shell_info *info)
{
	handle_alias_command(info);
}


/**
 * executeCdCommand - Handles the "cd" built-in command.
 * Changes the current working directory.
 * @info: Pointer to the shell_info structure.
 */

void executeCdCommand(shell_info *info)
{
	char *cwd;

	if (info->argv[1] != NULL)
	{
		if (chdir(info->argv[1]) == -1)
		{
			perror("chdir");
		}
	}
	else
	{
		if (chdir(my_getenv("HOME")) == -1)
		{
			perror("chdir");
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		setenv("PWD", cwd, 1);
		free(cwd);
	}
	else
	{
		perror("getcwd");
	}
}


/**
 * builtIn_Cmds - Handles built-in shell commands.
 * @info: Pointer to the shell_info structure.
 */

void builtIn_Cmds(shell_info *info)
{
	/* Check if the first argument is NULL */
	if (info->argv[0] == NULL)
	{
		return;
	}
	/* Handle the "exit" command */
	else if (_strcmp(info->argv[0], "exit") == 0)
	{
		executeExitCommand(info);
	}
	/* Handle the "env" command */
	else if (_strcmp(info->argv[0], "env") == 0)
	{
		executeEnvCommand();
	}
	/* Handle the "cd" command */
	if (_strcmp(info->argv[0], "cd") == 0)
	{
		executeCdCommand(info);
	}
	/* Handle the "alias" command */
	else if (_strcmp(info->argv[0], "alias") == 0)
	{
		executeAliasCommand(info);
	}
	else
		return;
}
