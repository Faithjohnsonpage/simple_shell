#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_ARG_COUNT 1024
#define MAX_ALIASES 1024

/**
 * struct Node - Structure for a linked list node.
 * @str: String data stored in the node.
 * @next: Pointer to the next node in the list.
 */

typedef struct Node
{
	char *str;
	struct Node *next;
} Node;

/**
 * struct Aliases - Structure to store alias information.
 * @alias_name: Name of the alias.
 * @command: Command associated with the alias.
 */

typedef struct Aliases
{
	char *alias_name;
	char *command;
} Aliases;

/**
 * struct shell_info - Structure to hold shell-related information.
 * @command_line: Raw command line input from the user.
 * @full_path: The 'PATH' variable of shell the environ
 * @argv: Array of pointers to command arguments.
 * @env: Linked list to store environment variables.
 * @aliases: Array of Aliases structures to store user-defined aliases.
 * @alias_count: Number of defined aliases.
 * @exit_status: Exit status of the last executed command.
 */

typedef struct shell_info
{
	char *command_line;
	char *full_path;
	char *argv[MAX_ARG_COUNT];
	Node *env;
	Aliases aliases[MAX_ALIASES];
	int alias_count;
	int exit_status;
} shell_info;

extern char **environ;

void prompt(void);
void my_print(const char *string);
void my_print_to_stderr(const char *string);
char* trimWhitespaces(char *buffer);
char *_strdup(const char *str);
int _strlen(const char *s);
int _atoi(const char *str);
void _strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
void _strcat(char *dest, const char *src);
char *_itoa(int num, char *str, int base);
int _strncmp(const char *s1, const char *s2, size_t n);
void init_shell_info(shell_info *info);
char *read_user_input(shell_info *info);
char *read_user_input_from_stdin();
void tokenization(shell_info *info);
void tokenization_ins(shell_info *info, int *num_commands);
void executeEnvCommand();
void executeExitCommand(shell_info *info);
void executeAliasCommand(shell_info *info);
void executeCdCommand(shell_info *info);
void builtIn_Cmds(shell_info *info);
void execute_command(shell_info *info, int *status);
void execute_command_ins(char *command, char *av[]);
void execute_cmd_from_paths(shell_info *info, char *args[]);
void execute_command_alias(char *command, char *args[]);
Node *env_node(char *filepath, shell_info *info);
char *my_getenv(const char *name);
char *location(char *path, shell_info *info);
char *get_location(shell_info *info);
char *location_ins(char *path, char *command);
char *get_location_ins(char *command);
void executeExitCommand_ins(shell_info *info, char *command, char *av[]);
void executeAliasCommand_ins(shell_info *info, char *command);
void handle_alias_command_ins(shell_info *info, char *command);
void executeCdCommand_ins(char *command, char *av[]);
void free_shell_info(shell_info *info);
void free_tokens(shell_info *info);
void free_env_node(shell_info *info);
void free_cmd_paths(char **cmd_paths);
void sigintHandler(int signum);
void conditional_handling(shell_info *info, int *status);
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
void handle_alias_command(shell_info *info);
void add_alias(shell_info *info, const char *alias_name, const char *command);
void free_aliases(shell_info *info);
int is_alias(shell_info *info, char *command);
void variable_replacement(shell_info *info, char *command_line);
void expand_and_execute_alias(shell_info *info, char *args[]);
void handle_non_interactive(char *command, shell_info *info, char *av[]);
int is_builtin_command(char *command);
void handle_builtin_commands(char *command, shell_info *info, char *av[]);


#endif /* SHELL_H */
