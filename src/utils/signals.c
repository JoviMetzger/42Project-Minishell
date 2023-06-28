/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/27 16:01:00 by jmetzger      ########   odam.nl         */
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

// void restore_prompt(int signal)
// {
//     if (signal == SIGINT)
//     {
//         ft_putchar_fd('\n', STDOUT_FILENO);
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
// }

// void handle_ctrl_c(int signal)
// {
//     if (signal == SIGINT)
//     {
//         write(STDERR_FILENO, "\n", 1);
//     }
// }

// void handle_ctrl_backslash(int signal)
// {
//     if (signal == SIGQUIT)
//     {
//         ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
//     }
// }

// void handle_ctrl_d(int signal)
// {
//     if (signal == SIGINT)
//     {
//         ft_putchar_fd('exit\n', STDOUT_FILENO);
//         exit(0);
//     }
// }

// /* ft_signal_handler();
// *   - Inside the function, there are three conditions checking the value of sig. 
// *   - If sig is equal to 1, it sets the signal handlers for SIGINT and 
// *     SIGQUIT to restore_prompt() and SIG_IGN (ignore), respectively. 
// *   - If sig is equal to 2, it sets the signal handlers for SIGINT and 
// *     SIGQUIT to ctrl_c() and back_slash(), respectively. 
// *   - Finally, if sig is equal to 3, it executes the exit(0) statement, 
// *     indicating the termination of the program.
// */
// void ft_signal_handler(int sig)
// {
//     if (sig == 1)
//     {
//         signal(SIGINT, restore_prompt);
//         signal(SIGQUIT, SIG_IGN);
//     }
//     else if (sig == 2)
//     {
//         signal(SIGINT, handle_ctrl_c);
//         signal(SIGQUIT, handle_ctrl_backslash);
        
//     }
//     else if (sig == 3)
//     {
//         signal(SIGINT, handle_ctrl_d);
//     }
// }


static void new_line(int signo)
{
    (void)signo;
    rl_on_new_line();
}

static void restore_prompt(int signo)
{
    (void)signo;
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
}

void signals_wait_cmd(void)
{
    signal(SIGINT, restore_prompt);
    signal(SIGQUIT, SIG_IGN);
}

void signals_run_cmd(void)
{
    signal(SIGINT, new_line);
    signal(SIGQUIT, new_line);
}
