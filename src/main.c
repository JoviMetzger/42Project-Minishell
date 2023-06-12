/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/12 14:18:29 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_history *data;
    
(void)argc;
(void)argv;
    while (1)
    {
        display_prompt();
        input = readline(NULL);
        create_history(input, &data);
        if (input[0] != 0)
            ft_commands(&input, envp, data);
    }
    //free_history();
    return (0);
}






/*
Here is a step-by-step procedure to help you write a shell with the given guidelines:

Displaying a Prompt: (Jovi) (DONE)
Write a function to display a prompt, such as "$", to indicate that the shell is ready for a new command.
Use a loop to continuously display the prompt and wait for user input.

Working History: (Jovi)
Implement a data structure, such as an array or linked list, to store the command history.
Whenever a command is executed, add it to the history.
Implement a command to display the command history when the user enters a specific command (e.g., "history").

Searching and Launching Executables: (Jovi)
Parse the user input to extract the command and arguments.
Check if the command is a built-in command (e.g., echo, cd, pwd, etc.). If it is, execute the corresponding built-in function.
If the command is not a built-in, search for the executable file in the directories specified by the PATH environment variable.
Use the execvp system call to launch the executable.

Handling Quotes: (Jovi)
Implement a function to handle quotes (' and ").
If a single quote is encountered, read the input until another single quote is seen and treat everything in between as a quoted sequence.
If a double quote is encountered, read the input until another double quote is seen, but still expand variables (e.g., $VAR) within the quoted sequence except for metacharacters.

Implementing Redirections: (Jovi)
Identify and handle the redirection symbols (<, >, <<, >>) in the user input.
For input redirection (<), use dup2 to redirect the standard input from a file.
For output redirection (> and >>), use dup2 to redirect the standard output to a file. Use O_TRUNC for '>' and O_APPEND for '>>'.
For here documents (<<), read the input until a line containing the delimiter is seen, but do not update the history.

Implementing Pipes: (Yixin)
Identify and handle the pipe symbol (|) in the user input.
Split the user input into multiple commands based on the pipe symbol.
Use the pipe system call to create a pipe between the commands.
Use dup2 to redirect the standard output of one command to the standard input of the next command.

Handling Environment Variables: (Jovi)
Implement a function to handle environment variables (e.g., $VAR).
Parse the user input and check for variables prefixed with '$'.
Expand the variables by looking up their corresponding values in the environment.

Handling Special Variables: (Jovi)
Implement a function to handle special variables like $? (exit status of the most recently executed foreground pipeline).
Keep track of the exit status after executing a command and store it in a variable.
Expand the special variables whenever they are encountered in the user input.

Handling Control Signals: (Jovi)
Implement signal handlers for ctrl-C (SIGINT), ctrl-D (EOF), and ctrl-\ (SIGQUIT).
For ctrl-C, display a new prompt on a new line.
For ctrl-D, exit the shell.
For ctrl-, do nothing.

Implementing Built-in Commands: (Yixin)
Implement separate functions for each built-in command (e.g., echo, cd, pwd, export, unset, env, exit).
Use appropriate system calls or library functions to execute the functionality of each built-in command.

Memory Leaks: ()
Ensure that your own code does not have memory leaks.
Free any dynamically allocated memory


----------------------------------------------------------

Person 1:
    1. (DONE) Displaying a Prompt: Person 1 can work on implementing the function to display the prompt and handle user input.
    2. Working History: Person 1 can handle the implementation of the command history data structure and the related functionalities.
    3. Searching and Launching Executables: Person 1 can work on parsing user input, identifying built-in commands, 
       and searching for executables in the PATH variable.
    4. Handling Quotes: Person 1 can handle the implementation of the function to handle quotes in the user input.
    5. Implementing Redirections: Person 1 can work on identifying and handling input/output redirections and here documents.
    6. Handling Environment Variables: Person 1 can handle the implementation of expanding environment variables in the user input.
    7. Handling Special Variables: Person 1 can work on implementing the functionality to handle special variables like $?.
    8. Handling Control Signals: Person 1 can handle the implementation of signal handlers for ctrl-C, ctrl-D, and ctrl-.

Person 2:
    1. Implementing Pipes: Person 2 can work on identifying and handling the pipe symbol in the user input, splitting commands, 
       and creating pipes between them.
    2. Implementing Built-in Commands: Person 2 can work on implementing separate functions for each built-in command, 
       such as echo, cd, pwd, export, unset, env, and exit.
Both:
    1. Memory Leaks: At the end both can focus on ensuring that the code written by both individuals does not have any memory leaks 
       and properly frees allocated memory.
*/