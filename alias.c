#include "shell.h"

/**
 * add_alias - Adds a new alias to the shell.
 * @info: Pointer to the shell_info structure.
 * @alias_name: Name of the alias.
 * @command: Command associated with the alias.
 */

void add_alias(shell_info *info, const char *alias_name, const char *command)
{
	int i;

	if (info->alias_count < MAX_ALIASES)
	{
		/* Check if the alias already exists and update it */
		for (i = 0; i < info->alias_count; i++)
		{
			if (_strcmp(alias_name, info->aliases[i].alias_name) == 0)
			{
				free(info->aliases[i].command);
				info->aliases[i].command = _strdup(command);
				return;
			}
		}
		info->aliases[info->alias_count].alias_name = _strdup(alias_name);
		info->aliases[info->alias_count].command = _strdup(command);
		info->alias_count++;
	}
	else
	{
		my_print("Error: Maximum number of aliases reached.\n");
	}
}

/**
 * free_aliases - Frees the allocated memory inside aliases.
 * @info: Pointer to the shell_info struct.
 */

void free_aliases(shell_info *info)
{
	int i;

	for (i = 0; i < info->alias_count; ++i)
	{
		free(info->aliases[i].alias_name);
		free(info->aliases[i].command);
		info->aliases[i].alias_name = NULL;
		info->aliases[i].command = NULL;
	}

	info->alias_count = 0; /* Reset alias count */
}



/**
 * handle_alias_command - Handles the 'alias' shell command.
 * @info: Pointer to the shell_info structure.
 */

void handle_alias_command(shell_info *info)
{
	int i, j;
	char *alias_name, *alias_value;

	if (info->argv[1] == NULL)
	{
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
		for (i = 1; info->argv[i] != NULL; i++)
		{
			alias_name = strtok(info->argv[i], "=");
			alias_value = strtok(NULL, "'");
			if (alias_value != NULL)
			{
				add_alias(info, alias_name, alias_value);
			}
			else
			{
			for (j = 0; j < info->alias_count; j++)
			{
				if (_strcmp(alias_name, info->aliases[j].alias_name) == 0)
				{
					my_print(info->aliases[j].alias_name);
					my_print("='");
					my_print(info->aliases[j].command);
					my_print("'\n");
					break;				}
				}
			}
		}
	}
}
