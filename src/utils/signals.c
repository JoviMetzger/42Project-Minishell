/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/20 14:29:28 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long int g_exit_status;

void	restore_prompt(int sig)
{
	if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 128 + sig;
    }
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        g_exit_status = 128 + sig;
    }
}

void	backslash(int sig)
{
    if (sig == SIGQUIT)
    {
	    printf("Quit\n");
        g_exit_status = 128 + sig;
    }
}

void	handle_signal(int num)
{
	if (num == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (num == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
}

/* The value 130 is calculated by adding 128 to the signal number. 
*   When a process receives a SIGINT signal, the default action is to terminate the process. 
*   By convention, the shell uses an exit status of 128 + signal number to indicate 
*   that the process was terminated due to a signal. In the case of SIGINT (signal number 2), 
*   adding 128 gives 130.
*/

/* Ctrl-C tells the terminal to send a SIGINT to the current foreground process, 
*   which by default translates into terminating the application. 
*   Ctrl-D tells the terminal that it should register a EOF on standard input, 
*   which bash interprets as a desire to exit.
*/
