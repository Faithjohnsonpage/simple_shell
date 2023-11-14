#include "shell.h"

/**
 * execute_command - Executes a command.
 * @info: Pointer to the shell_info structure.
 * @status: Pointer to the exit status of the command.
 */

void execute_command(shell_info *info, int *status)
{
	pid_t child_pid;
	int child_status;
	char *cmd_path;
	char **args;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		free_tokens(info);
		free_shell_info(info);
		free(info->full_path);
		free_aliases(info);
		free(info);
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{ /* Child process */
		args = info->argv;
		cmd_path = info->full_path;
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free_tokens(info);
			free_shell_info(info);
			free(info->full_path);
			free_aliases(info);
			free(info);
			exit(EXIT_FAILURE);
		}
	}
	else
	{ /* Parent process */
		/* Wait for the child process to complete */
		if (waitpid(child_pid, &child_status, 0) == -1)
		{
			perror("waitpid");
			free_tokens(info);
			free_shell_info(info);
			free(info->full_path);
			free_aliases(info);
			free(info);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(child_status))
		{/* Update the exit status */
			*status = WEXITSTATUS(child_status);
		}
		else
		{
			*status = EXIT_FAILURE;
		}
	}
}



/**
 * execute_cmd_from_paths - Executes commands from an array of paths.
 * @cmd_paths: Array of command paths.
 * @num_commands: Number of commands in cmd_paths.
 */

void execute_cmd_from_paths(shell_info *info, char *args[])
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(info->full_path, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

}


/**
 * execute_command_alias - Executes the specified command with arguments.
 * @command: Command to be executed.
 * @args: Array of strings containing the command and its arguments.
 */

void execute_command_alias(char *command, char *args[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* Child process */
		if (access(command, X_OK) == 0)
		{
			/* Check if the command is executable */
			execve(command, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}
