/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/28 12:46:44 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /*
// * Handling signal interrupts:
// *     - Implement signal handlers for SIGINT (ctrl-C), SIGQUIT (ctrl-), 
// *       and SIGTERM (ctrl-D). 
// *     - Define the desired behavior for each signal, such as displaying a prompt, 
// *       exiting the shell, or ignoring the signal.
// * 
// * Interactive mode behavior: 
// *     - Define the behavior of the shell in interactive mode for each 
// *       signal mentioned in the requirements.
// *     - For example, pressing ctrl-C should display a new prompt on a new line.
// */

void restore_prompt(int signal)
{
    (void)signal;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void handle_ctrl_c(int signal)
{
    (void)signal;
    write(STDERR_FILENO, "\n", 1);
}

void handle_ctrl_backslash(int signal)
{
    (void)signal;
}

void handle_ctrl_d(int signal)
{
    (void)signal;
    write(STDOUT_FILENO, "exit\n", 1);
    exit(0);
}

/* ft_signal_handler();
*   - Inside the function, there are three conditions checking the value of sig. 
*   - If sig is equal to 1, it sets the signal handlers for SIGINT and 
*     SIGQUIT to restore_prompt() and SIG_IGN (ignore), respectively. 
*   - If sig is equal to 2, it sets the signal handlers for SIGINT and 
*     SIGQUIT to ctrl_c() and back_slash(), respectively. 
*   - Finally, if sig is equal to 3, it executes the exit(0) statement, 
*     indicating the termination of the program.
*/
void ft_signal_handler(int sig)
{
    if (sig == 1)
    {
        signal(SIGINT, restore_prompt);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (sig == 2)
    {
        signal(SIGINT, handle_ctrl_c);
        signal(SIGQUIT, handle_ctrl_backslash);
        
    }
    else if (sig == 3)
    {
        signal(SIGINT, handle_ctrl_d);
        
    }
}

// -------------------------------------------

// static void new_line(int signal)
// {
//     (void)signal;
//     rl_on_new_line();
//     exit(0);
// }

// static void restore_prompt(int signal)
// {
//     (void)signal;
//         ft_putchar_fd('\n', STDOUT_FILENO);
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
// }

// void signals_wait(void)
// {
//     signal(SIGINT, restore_prompt);
//     signal(SIGQUIT, SIG_IGN);
// }

// void signals_run(void)
// {
//     signal(SIGINT, new_line);
//     signal(SIGQUIT, new_line);
// }


/// --------------------

// void handle_ctrl_c(int signal)
// {
//     (void)signal;
//     printf("\n");
//     display_prompt();
//     fflush(stdout);
// }

// void handle_ctrl_backslash(int signal)
// {
//     (void)signal;
//     write(STDOUT_FILENO, "\b\b  \b\b", 2);
// }

// void handle_ctrl_d(int signal)
// {
//     (void)signal;
//     write(STDOUT_FILENO, "exit\n", 1);
//     exit(0);
// }

// void ft_signal_handler()
// {
//     char input[100];
    
//     signal(SIGINT, handle_ctrl_c);
//     signal(SIGQUIT, handle_ctrl_backslash);
//     signal(SIGTERM, SIG_IGN);
//     if (input[0] == '\n')
//     {
//         display_prompt();
//     }
//     if (strcmp(input, "exit\n") == 0)
//     {
//         display_prompt();
//     }
// }
