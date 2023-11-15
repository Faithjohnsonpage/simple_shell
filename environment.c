#include "shell.h"

/**
 * env_node - Creates a new node for the environment linked list.
 * @filepath: Path to be stored in the new node.
 * @info: Pointer to the shell_info structure.
 * Return: Pointer to the new node.
 */

Node *env_node(char *filepath, shell_info *info)
{
	Node *new_node = malloc(sizeof(Node));

	if (new_node == NULL)
	{
		perror("malloc");
		free_tokens(info);
		free(info->command_line);
		free(info);
		exit(EXIT_FAILURE);
	}
	new_node->str = _strdup(filepath);
	new_node->next = info->env;
	info->env = new_node;
	return (info->env);
}

/**
 * my_getenv - Gets the value of an environment variable.
 * @name: Name of the environment variable.
 * Return: Pointer to the value of the environment variable.
 */

char *my_getenv(const char *name)
{
	int i;
	size_t name_len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}

	return (NULL);
}

/**
 * get_location - Gets the environment path for command execution.
 * @info: Pointer to the shell_info structure.
 * Return: Path to the environment variable or NULL if not found.
 */

char *get_location(shell_info *info)
{
	char *path;

	path = my_getenv("PATH");

	if (path)
	{
		path = location(path, info);
		return (path);
	}
	return (NULL);
}


/**
 * location - Locates a command in the given path.
 * @path: Path to search for the command.
 * @info: Pointer to the shell_info structure.
 * Return: Path to the located command, or NULL if not found.
 */

char *location(char *path, shell_info *info)
{
	char *token;
	char *full_path, *path_copy;

	path_copy = _strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(_strlen(token) + _strlen(info->argv[0]) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, info->argv[0]);
		_strcat(full_path, "\0");

		if (access(full_path, X_OK) == 0)
		{
			env_node(full_path, info);
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
