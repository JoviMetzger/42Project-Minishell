# 🔥 MiniS*hell* 🔥

Welcome to MiniShell! This repository contains a simplified shell, inspired by bash. <br> 
🌸 Created in collaboration with [Yixin Zhang](https://github.com/yixin1230) 🌸

## Table of Contents

- [About](#About)
   - [Functions *(only rl_functions)*](#Functions)
   - [Buildin](#Buildin)
   - [Signals](#Signals)
   - [Prompt](#Prompt)
   - [Installing readline](#Installing-readline)
   - [Test for Leaks](#Test-for-Leaks)
- [Installation](#Installation)
- [Testing](#Testing)
- [Resources](#Resources)

## 🌱About 
Minishell should work like bash. Not everything should work like bash I mean it is **"mini"** shell, but a few things should be taken care of, like:
- Having a prompt.
- Handle `'` *(single quote)* and `"` *(double quote)*. Double quote should handle `$`*(dollar sign)*, but no need to handle the other metacharacters (`|`, `&`, `(`, `)`, `;`).
- Handle redirections `<` *(input)*, `>` *(output)*, `<<` *(append)*, `>>` *(here_doc)*.
- Handle pipes `|` *(adding syntax error check)*.
- Handle environment variables *(ex. $PATH)*.
- Handle `$?` *(exit status)*. 
- Handle signals, `ctrl-C` *(displays a new prompt on a new line)*, `ctrl-D` *(exits the shell)*, `ctrl-\` *(does nothing)*.
- Have builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## 🌱Functions
Finding information about the ***'rl_' functions*** is difficult. [Readline(3)](https://man7.org/linux/man-pages/man3/readline.3.html) has some, but not all of them, so here are the basics of what those functions do. <br>
- `readline`: Reads a line of input from the user, providing basic line editing capabilities such as cursor movement, deletion, and history retrieval.
- `rl_clear_history`: Clears the history of previously entered lines in the readline library.
- `rl_on_new_line`: Notifies the readline library that a new line has been created, typically used after outputting a newline character.
- `rl_replace_line`: Replaces the current input line in the readline library with a new line of text.
- `rl_redisplay`: Forces the readline library to redraw the current input line, updating any changes made to it.
- `add_history`: Adds a line of text to the history list in the readline library, allowing for retrieval and editing of previously entered lines.

## 🌱Buildin
The order of built-in commands like *export, cd, unset, and exit* matters <br> 
because these commands have immediate and direct effects on the shell's environment or behavior. <br> 
Placing them before child commands ensures that their effects are applied before the child commands are executed. <br> 
**They don't work in a child process.**  <br>
| Command | Description | Considerations |
| ------- | ----------- | -------------- |
| `echo`  | Prints text or a string to the standard output. The `-n` option prevents adding a newline to the output. | 🔸 The behavior of `-n`, `-nnnn`, and `-n -n` should all be the same. |
| `cd`    | Changes the current directory to the specified location. |  |
| `pwd`   | The `pwd` command stands for *"print working directory"*. It prints the absolute path of the current working directory. |  |
| `export`| Allows you to define variables that can be accessed by other processes or programs. When you use the `export` command followed by a variable assignment, it sets the value of the variable and marks it for export to the environment. | **Exported variables have specific rules:** 🔸 The first letter of the variable can only start with *uppercase* and *lowercase* letters or with an *underscore* `_`.  🔸 The rest of the variable name can only contain *uppercase* and *lowercase* letters, *underscores*, and *numbers*; anything else will result in an error. 🔸 Only the `export` command prints `declare x-` in front of each variable. |
| `unset` | Allows you to remove a variable from the environment or unset its value. When you run the `unset` command followed by a variable name, it removes the variable from the environment or unsets its value. | **Variable names in `unset` must follow these rules:** 🔸 The first letter of the variable can only start with *uppercase* and *lowercase* letters or with an *underscore* `_`.  🔸 The rest of the variable name can only contain *uppercase* and *lowercase* letters, *underscores*, and *numbers*; anything else will result in an error. |
| `env`   | When used without any options or arguments, it lists all the environment variables and their values. | |
| `exit`  | When you run the `exit` command without any options, it immediately terminates the current shell and returns control to the parent shell or the operating system. | 🔸 The maximum exit value is that of a *long long int*. 🔸 It doesn't exit if given more than one argument, e.g., `exit 1 2`; it displays an error message. 🔸 It does exit with a non-numeric value, e.g., `exit hello`, but displays an error message. 🔸 If you exit with only `exit`, it will show the exit code of the previous command. |

❗**NOTE**: All variables are added to the environment. <br>
When you use the `export` command, it displays the entire environment, including all variables. <br>
In contrast, the `env` command selectively lists only those variables that have a value assigned to them `name=value`.

## 🌱Signals
MiniShell handles signals as follows: <br>
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

## 🌱Prompt
It's important to keep the prompt inside the readline() function to avoid its disappearance when deleting a word. You can use a simple or fancy prompt with colors, but avoid separating it from readline(). <br> <br> 
**Simple Prompt**:
```C
input = readline("minishel ➡️ ");
``` 
**Fancy Prompt** *(using colours)*:
```C
prompt = display_prompt();
input = readline(prompt);
ft_free(prompt);
```
🚫 **NOT this!** 🚫
```C
display_prompt();
input = readline(NULL);
``` 
<br>

❗**NOTE**: Be aware that using colored prompts might have display issues with copy/paste or arrow keys <br>
***(Not your fault, it's readline problem)***. <br>
Reason for that is, because the colored prompts often include ANSI escape codes to define text colors or styles. When readline calculates cursor positions for text input, it may not accurately consider the extra characters introduced by these escape codes. Consequently, there can be discrepancies between the displayed cursor position and its actual location within the input text. This can lead to unexpected behavior when performing actions such as copying and pasting text or using arrow keys for navigation within the command line. <br>
🔆 ***However, the functionality of your application remains intact and everything will still work.*** 🔆


## 🌱Installing readline
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
❗**NOTE**: `-Wno-unused-command-line-argument` is used to 'mute' the warnings about the readline.

## 🌱Test for Leaks
You can test for memory leaks using either `valgrind` or `system("leaks -q minishell")`. <br>
**For systemleaks:** Test after each command to identify specific leaks. <br> In one terminal, run MiniShell, and in another, execute "leaks minishell" after each command. <br> <br>
**Terminal 1**: *cd into minishell folder*:
```bash
$ ./minishell
minishell ➡️ 
```
**Terminal 2**: *cd into minishell folder*:
```bash
$ leaks minishell
```

<br> **For valgrind:** It will automatically check for leaks after each command, alerting you if one is found. Upon exiting, it will provide a summary of all the information. <br>
**Execute** 
```bash
$ make && valgrind --leak-check=full ./minishell
minishell ➡️ 
```

## 🌱Installation

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

## 🌱Testing
You can find alot of tester for minishell, we used the 🔅 [MiniShell Tester](https://github.com/LucasKuhn/minishell_tester) 🔅 because it was the most easiest one to use. The testers README file provides clear instructions on installation and usage.

## 🌱Resources
- [42 Docs(MiniShell)](https://harm-smits.github.io/42docs/projects/minishell)
- [MiniShell-42 Explanation](https://cocalc.com/github/yabtaour/Minishell-42/blob/main/ReadMe.md)
- [An Overview of How the BASH Shell Works](https://medium.com/geekculture/an-overview-of-the-working-of-the-bash-shell-f063e7f09945)
- [Great README.md on MiniShell](https://github.com/maiadegraaf/minishell)
- [readline(3) - Linux Manual Page](https://man7.org/linux/man-pages/man3/readline.3.html)
- [Signals Explanation](https://btholt.github.io/complete-intro-to-linux-and-the-cli/signals-and-the-power-of-ctrl)
- [Signals MiniShell Document](https://www.studocu.com/en-us/document/auburn-university-at-montgomery/topics-in-spanish-american-culture-and-civilization/minishell-3-signal-handling-compressed/35995495)
