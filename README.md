# My Custom Simple Shell

This is a simple shell implemented in the C language.

## About

A shell is a command-line interface enabling users to interact with an operating system by entering commands. It interprets and executes these commands,supports scripting, and allows users to control the environment and manage processes. Common shells include Bash, sh, csh, and zsh, each with unique features for system management and customization.

## Compilation

This simple shell is compiled with:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Output
This program has the exact same output as sh as well as the exact same error output. The only difference is when it prints an error, the name of the program is equivalent to argv[0].

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
```

Error with our program:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```

## Testing
Our shell works like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

Examples:
```
$ /bin/pwd
/home/ermac/simple_shell
```

```
$ ls -al
total 116
drwxr-xr-x 3 ermac ermac  4096 Nov 14 22:57 .
drwxr-x--- 8 ermac ermac  4096 Nov 14 22:57 ..
drwxr-xr-x 7 ermac ermac  4096 Oct 31 11:00 .git
-rw-r--r-- 1 ermac ermac   107 Oct 24 18:55 AUTHORS
-rw-r--r-- 1 ermac ermac  1476 Nov 14 22:57 README.md
-rw-r--r-- 1 ermac ermac  2277 Nov 14 01:45 alias.c
-rw-r--r-- 1 ermac ermac  2300 Nov 13 17:28 built-in_cmds.c
-rw-r--r-- 1 ermac ermac  5006 Nov 14 22:23 builtin_non_interactive.c
-rw-r--r-- 1 ermac ermac  1010 Nov  9 14:17 custom_func.c
-rw-r--r-- 1 ermac ermac  3019 Nov 13 15:19 custom_func2.c
-rw-r--r-- 1 ermac ermac  2351 Nov  5 18:53 environment.c
-rw-r--r-- 1 ermac ermac  2589 Nov 14 22:25 execute_commands.c
-rw-r--r-- 1 ermac ermac  1953 Nov 10 02:21 free.c
-rw-r--r-- 1 ermac ermac  4786 Nov 12 15:05 handle_non_interactive.c
-rw-r--r-- 1 ermac ermac  3794 Nov 14 12:09 handle_non_interactive2.c
-rwxr-xr-x 1 ermac ermac 31912 Nov 14 22:31 hsh
-rw-r--r-- 1 ermac ermac  1391 Nov 13 18:13 print.c
-rw-r--r-- 1 ermac ermac  3871 Nov 14 22:29 shell.c
-rw-r--r-- 1 ermac ermac  3987 Nov 14 12:12 shell.h
-rw-r--r-- 1 ermac ermac  2367 Nov 14 22:30 shell_setup.c
```

```
$ ls
AUTHORS    alias.c          builtin_non_interactive.c  custom_func2.c  execute_commands.c  handle_non_interactive.c   hsh      shell.c  shell_setup.c
README.md  built-in_cmds.c  custom_func.c              environment.c   free.c              handle_non_interactive2.c  print.c  shell.h
```

```
$ lf
./hsh: lf: not found
```

## Author:
Faith Johnson (ermac_4life@yahoo.com)
