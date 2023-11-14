#include "shell.h"

/**
 * free_cmd_paths - Frees the memory allocated for an array of command paths.
 * @cmd_paths: Pointer to the array of command paths to be freed.
 *
 * This function iterates through cmd_paths and frees each string element,
 * and then frees the cmd_paths array itself to prevent memory leaks.
 */

void free_cmd_paths(char **cmd_path)
{
	int i;

	if (cmd_path == NULL)
	{
		return;
	}

	/* Iterate through cmd_paths and free each string */
	for (i = 0; cmd_path[i] != NULL; ++i)
	{
		free(cmd_path[i]);
		cmd_path[i] = NULL;
	}

	/* Free the cmd_paths array itself */
	free(cmd_path);
}

/**
 * free_tokens - Frees the memory allocated for tokens in info->argv.
 * @info: Pointer to the shell_info structure.
 */

void free_tokens(shell_info *info)
{
	int i;

	for (i = 0; i < MAX_ARG_COUNT; ++i)
	{
		if (info->argv[i] != NULL)
		{
			free(info->argv[i]);
			info->argv[i] = NULL;
		}
	}
}


/**
 * free_shell_info - Frees memory allocated for the shell_info structure.
 * @info: Pointer to the shell_info structure.
 */

void free_shell_info(shell_info *info)
{
	Node *current, *temp;

	/* Free command_line */
	if (info->command_line != NULL)
	{
		free(info->command_line);
		info->command_line = NULL;
	}

	/* Free environment variables */
	current = info->env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
	}
	info->env = NULL;

	/* Reset exit status */
	info->exit_status = 0;
}


/**
 * free_env_node - Frees the linked list of environment variables.
 * @info: Pointer to the shell information struct.
 *
 */

void free_env_node(shell_info *info)
{
	Node *current, *temp;

	/* Free environment variables */
	current = info->env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
	}
	info->env = NULL;
}
