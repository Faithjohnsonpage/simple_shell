#include "shell.h"

void execute_command_ins(char *command, char *av[]);
char *read_user_input_from_stdin();

/**
 * read_user_input_from_stdin - Reads a line of text from standard input.
 *
 * Return: A pointer to the input line or NULL on failure.
 */

char *read_user_input_from_stdin()
{
	size_t buffer_size = MAX_ARG_COUNT;
	char *cmd_buffer = malloc(buffer_size * sizeof(char));
	char *line = NULL;
	ssize_t num_of_chars;
	int is_continuation = 0;

	if (cmd_buffer == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	cmd_buffer[0] = '\0';

	while ((num_of_chars = getline(&line, &buffer_size, stdin)) != -1)
	{
		/* Remove newline character at the end */
		if (num_of_chars > 0 && line[num_of_chars - 1] == '\n')
		{
			line[num_of_chars - 1] = '\0';
			num_of_chars--;
		}

		/* Check for line continuation character '\' */
		if (num_of_chars > 0 && line[num_of_chars - 1] == '\\')
		{
			/* Remove the backslash for line continuation */
			line[num_of_chars - 1] = '\0';
			is_continuation = 1;
		}
		else
		{
			/* No line continuation, concatenate the line to cmd_buffer */
			strcat(cmd_buffer, line);
			if (is_continuation)
			{
				strcat(cmd_buffer, " ");
			}
			else
			{
				strcat(cmd_buffer, "\n");
			}
			is_continuation = 0;
		}
	}

	free(line);

	if (num_of_chars == -1 && !feof(stdin))
	{
		perror("getline");
		free(cmd_buffer);
		exit(EXIT_FAILURE);
	}

	return (cmd_buffer);
}




/**
 * tokenization_ins - Tokenizes the command line input.
 * @info: Pointer to the shell_info structure.
 * @num_commands: Pointer to an integer to store the number of commands found.
 */

void tokenization_ins(shell_info *info, int *num_commands)
{
	char *token;
	int i = 0;

	token = strtok(info->command_line, ";\n");
	while (token != NULL && i < MAX_ARG_COUNT - 1)
	{
		info->argv[i] = _strdup(token);

		/* Null-terminate the command string */
		info->argv[i][_strlen(info->argv[i])] = '\0';
		i++;
		token = strtok(NULL, ";\n");
	}
	info->argv[i] = NULL;

	*num_commands = i;
}

/**
 * execute_command_ins - Executes a series of commands in non-interactive mode.
 *
 * This function takes a shell_info structure containing command arguments and
 * executes each command in a separate child process using fork() and execve().
 * It waits for each child process to complete in the parent process.
 *
 * @command: The command to be executed.
 * @av: Array of strings containing the program name and its arguments.
 */

void execute_command_ins(char *command, char *av[])
{
	pid_t child_pid;
	int i = 0, j, child_status;
	char *args[1024];
	char *token;

	token = strtok(command, " \t");
	while (token != NULL)
	{
		args[i] = _strdup(token);
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (access(args[0], X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			/* Child process */
			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}

		}
		else
		{
			/* Parent process */
			if (waitpid(child_pid, &child_status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
		for (j = 0; args[j] != NULL; ++j)
		{
			free(args[j]);
		}
	}
	else
	{
		my_print_to_stderr(av[0]);
		my_print_to_stderr(": ");
		my_print_to_stderr("1: ");
		my_print_to_stderr(args[0]);
		my_print_to_stderr(": not found\n");
		exit(127);

	}

}


/**
 * get_location_ins - Gets the environment path for command execution
 * in non-interactive mode.
 * @command: The command to be executed.
 * Return: Array of command paths on success, NULL on failure.
 */

char *get_location_ins(char *command)
{
	char *path;

	path = my_getenv("PATH");
	if (path)
	{
		path = location_ins(path, command);
		return (path);
	}
	return (NULL);
}

/**
 * location_ins - Locates a command in the given path.
 * @path: Path to search for the command.
 * @command: The command to be searched.
 * Return: Full path to the located command, NULL if not found.
 */

char *location_ins(char *path, char *command)
{
	char *token;
	char *full_path, *path_copy;

	path_copy = _strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		_strcat(full_path, "\0");

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
