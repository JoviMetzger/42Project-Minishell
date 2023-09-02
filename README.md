# 🔥🔥 MiniS**hell**

Welcome to MiniShell! This repository contains a simplified shell, inspired by bash. <br> 
Created in collaboration with [Yixin Zhang](https://github.com/yixin1230).

## Table of Contents

- [About](#About)
   - [Functions](#Functions)
	- [Buildin](#Buildin)
      - [echo](#echo)
      - [cd](#cd)
      - [pwd](#pwd)
      - [export](#export)
      - [unset](#unset)
      - [env](#env)
      - [exit](#exit)
   - [Signals](#Signals)
   - [Prompt](#Prompt)
   - [Installing readline](#Installing-readline)
   - [Test for Leaks](#Test-for-Leaks)
- [Installation](#Installation)
- [Testing](#Testing)
- [Resources](#Resources)

## About 
Minishell should work like bash. Not everything should work like bash I mean it is **"mini"** shell, but a few things should be taken care of, like:
- Having a prompt.
- Handle `'` *(single quote)* and `"` *(double quote)*. Double quote should handle `$`*(dollar sign)*, but no need to handle the other metacharacters (`|`, `&`, `(`, `)`, `;`).
- Handle redirections `<` *(input)*, `>` *(output)*, `<<` *(append)*, `>>` *(here_doc)*.
- Handle pipes `|`.
- Handle environment variables *(ex. $PATH)*.
- Handle `$?` *(exit status)*. 
- Handle signals, `ctrl-C` *(displays a new prompt on a new line)*, `ctrl-D` *(exits the shell)*, `ctrl-\` *(does nothing)*.
- Have builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Functions
Finding information about the ***'rl_' functions*** is deficult. [Readline(3)](https://man7.org/linux/man-pages/man3/readline.3.html) has some, but not all of them, so here are the basics of what those functions do. I also added a few ohters that might be handy. <br>
- `readline`: Reads a line of input from the user, providing basic line editing capabilities such as cursor movement, deletion, and history retrieval.

- `rl_clear_history`: Clears the history of previously entered lines in the readline library.

- `rl_on_new_line`: Notifies the readline library that a new line has been created, typically used after outputting a newline character.

- `rl_replace_line`: Replaces the current input line in the readline library with a new line of text.

- `rl_redisplay`: Forces the readline library to redraw the current input line, updating any changes made to it.

- `add_history`: Adds a line of text to the history list in the readline library, allowing for retrieval and editing of previously entered lines.

- `access`: Checks whether a file or directory can be accessed with the specified permissions.

- `fork`: Creates a new process by duplicating the existing process, creating a child process that is an exact copy of the parent process.

- `wait`: Suspends the execution of the calling process until one of its child processes exits.

- `waitpid`: Suspends the execution of the calling process until a specific child process terminates or a signal is received.

- `signal`: Sets a function to handle a specific signal, allowing customization of the behavior when a signal is received.

- `sigaction`: Specifies the action to be taken when a specific signal occurs, providing more control and options than signal.

- `sigemptyset`: Initializes an empty signal set, which can be used to manage sets of signals.

- `sigaddset`: Adds a specific signal to a signal set.

- `kill`: Sends a signal to a specified process or process group.

- `getcwd`: Retrieves the current working directory.

- `chdir`: Changes the current working directory to the specified directory.

- `execve`: Executes a program, replacing the current process with a new program.

- `dup, dup2`: Duplicates a file descriptor, creating a new descriptor that refers to the same file or resource. dup2 allows specifying the desired file descriptor number.

- `pipe`: Creates a communication pipe, which can be used for inter-process communication.

- `opendir`: This function is used to open a directory, creating a directory stream. It takes a directory path as an argument and returns a pointer to the directory stream.

- `closedir`: This function is used to close a directory stream that was previously opened with opendir.

- `perror`: Prints a descriptive error message to the standard error stream (stderr), based on the value of the global errno variable.

- `getenv`: Retrieves the value of an environment variable specified by its name, returning a pointer to the corresponding value.

- `tcsetattr`: This function is used to set terminal attributes, specifically the parameters associated with a terminal interface (e.g., baud rate, line discipline, and control characters).

- `tcgetattr`: This function is used to get (retrieve) the current terminal attributes. You can use it to check the current configuration of a terminal.

## Buildin
❗The order of built-in commands like **export, cd, unset, and exit** matters because these commands have immediate and direct effects on the shell's environment or behavior. Placing them before child commands ensures that their effects are applied before the child commands are executed. **They don't work in a child process.**❗ <br>
| Command | Description |
|---|---|
| ### `echo` | Prints text or a string to the standard output. The `-n` option prevents adding a newline to the output. <br>
**Things to have in mind:** <br>
- *`-n`, `-nnnn`, `-n -n` should all behave the same.* |
| ### `cd` | Changes the current directory to the specified location. |
| ### `pwd` |  The pwd command stands for *"print working directory"*. <br>
Prints the absolute path of the current working directory. |
| ### `export` | It allows you to define variables that can be accessed by other processes or programs. <br>
When you use the export command followed by a variable assignment, it sets the value of the variable and marks it for export to the environment.<br>
**Things to have in mind:** *export variables have alot of egde-cases* <br>
- *first letter of the variable can only start with **uppercase** and **lowercase** letters or with **underscore** `_`,* <br>
- *the rest of the word can only have **uppercase**, **lowercase** letters, **underscore** and **numbers**, everything else will display an error,*
- *only `export` prints `declare x-` infront of each varable.* |
| ### `unset` | It allows you to remove a variable from the environment or unset its value. <br>
When you run the unset command followed by a variable name, it removes the variable from the environment or unsets its value.<br>
**Things to have in mind:** <br>
- *first letter of the variable can only start with **uppercase** and **lowercase** letters or with **underscore** `_`,* <br>
- *the rest of the word can only have **uppercase**, **lowercase** letters, **underscore** and **numbers**, everything else will display an error,* |
| ### `env` | When used without any options or arguments, it lists all the environment variables and their values. |
| ### `exit` | When you run the exit command without any options, it immediately terminates the current shell and returns control to the parent shell or the operating system. <br>
**Things to have in mind:** <br>
- *max of long long int,* <br>
- *doesn't exit if more than 1 argument `exit 1 2`, display error message,* <br>
- *does exit with non-numric value `exit hello`, but displays an error message,* <br>
- *if you exit only with `exit` it will show the exit code of the prevous command.* |

❗**NOTE**: Everything gets added to the enviromet. `export` prints the whole enviroment and `env` only prints the variables that have a value `name=value`.

## Signals
MiniShell handles signals as follows:
You need 3 different signal functions.
1. For the **main**:
   - `Ctrl-C`: Displays a new prompt, *exits with code 1*.
   - `Ctrl-\`: Has no effect.
2. For **here_doc** *(input redirection)*:
   - `Ctrl-C`: Displays the here_doc sign, *exits with code 1*.
   - `Ctrl-\`: Has no effect.
3. For **child processes** *(e.g., cat)*:
   - `Ctrl-C`: Exits the child process, displaying ^C, *exits with code 130*.
   - `Ctrl-\`: Exits the child process, displaying ^\Quit, *exits with code 131*. <br>
`Ctrl-C`: tells the terminal to send a ***SIGINT*** to the current foreground process. <br>
`Ctrl-\`: tells the terminal to send a ***SIGQUIT*** to the current foreground process. <br>
`Ctrl-D`: **is no signal**. Ctrl-D tells the terminal that it should register a EOF on standard input, which bash interprets as a desire to exit.
```bash
input = readline("minishell ➡️ ");
if (input == NULL)
{
   printf("exit\n");
   exit(0);
}
```
`exit status`: The value 130 and 131 are calculated by adding 128 to the signal number. <br>
In the case of SIGINT (signal number 2), by convention, the shell uses an exit status of 128 + signal number to indicate that the process was terminated due to a signal, adding 128 + (signal number 2) gives 130. <br>
In the case of SIGQUIT (signal number 3), adding 128 gives 131.

## Prompt
It's important to keep the prompt inside the readline() function to avoid its disappearance when deleting a word. You can use a simple or fancy prompt with colors, but avoid separating it from readline().  
- **simple prompt**
```C
input = readline("minishel ➡️ ");
``` 
- **fancy prompt** *(using colours)*
```C
prompt = display_prompt();
input = readline(prompt);
ft_free(prompt);
```
- 🚫 **NOT this!**
```C
display_prompt();
input = readline(NULL);
``` 
<br>

❗**NOTE**: Be aware that using colored prompts might have display issues with copy/paste or arrow keys ***(Not your fault, it's readline problem)***. <br>
Reason for that is, because the colored prompts often include ANSI escape codes to define text colors or styles. When readline calculates cursor positions for text input, it may not accurately consider the extra characters introduced by these escape codes. Consequently, there can be discrepancies between the displayed cursor position and its actual location within the input text. This can lead to unexpected behavior when performing actions such as copying and pasting text or using arrow keys for navigation within the command line. <br>
***However, the functionality of your application remains intact and everything will still work.***


## Installing readline
For readline to work you need to do a few things.
1. Install brew:
```bash
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```
2. Install readline:
```bash
brew install readline
```
3. Add into your Makefile: *Include these in your compiling*
```bash
INC_FILE = -I includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
Include  = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
mute     = -Wno-unused-command-line-argument
```
❗**NOTE**: `mute` is used to 'mute' the warnings about the readline.

## Test for Leaks
You can test for memory leaks using either `valgrind` or `system("leaks -q minishell")`. 
Test after each command to identify specific leaks. In one terminal, run MiniShell, and in another, execute leaks minishell after each command.
**Terminal 1**: *cd into minishell folder*;
```bash
$ ./minishell
minishell ➡️ 
```  
**Terminal 2**: *cd into minishell folder*;
```bash
$ leaks minishell
```

## Installation

1. Compile the program by running the following command:
```bash
$ make
```
2. Finally, execute the program using the following command: 
```bash
$ ./minishell
```
3. You in minishell now, so you can do any command:
```C
minishell ➡️  echo "Hello World"
```

## Testing
You can find alot of tester form minishell, we used the 🔆 [MiniShell Tester](https://github.com/LucasKuhn/minishell_tester) 🔆 because it was the most easiest one to use. The testers README file provides clear instructions on installation and usage.

## Resources
- [42 Docs(MiniShell)](https://harm-smits.github.io/42docs/projects/minishell)
- [An Overview of How the BASH Shell Works](https://medium.com/geekculture/an-overview-of-the-working-of-the-bash-shell-f063e7f09945)
- [Great README.md on MiniShell](https://github.com/maiadegraaf/minishell)
- [readline(3) - Linux Manual Page](https://man7.org/linux/man-pages/man3/readline.3.html)
- [Signals Explanation](https://btholt.github.io/complete-intro-to-linux-and-the-cli/signals-and-the-power-of-ctrl)
