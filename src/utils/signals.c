/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 15:56:08 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * I am using a global variable to store the exit status of signals.
 * But because the 'signal()' function can only return 'void', 
 * so we use this global variable to pass the exit status.
 * Since 'signal()' can't directly pass a struct, 
 * using a global variable is a workaround to capture the exit status.
 */
int	g_exit_status;

/* restore_prompt();
 *	- Signal handler for SIGINT (Ctrl-C) in the parent process.
 *	- Displays a new prompt and updates the exit status.
 */
void	restore_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 128 + sig;
	}
}

/* ctrl_c();
 *	- Signal handler for SIGINT (Ctrl-C) in a child process.
 *	- Exits the current child process and updates the exit status.
 */
void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_exit_status = 128 + sig;
	}
}

/* backslash();
 *	- Signal handler for SIGQUIT (Ctrl-\).
 *	- Writes "^\Quit" with the sig to the output and updates the exit status.
 */
void	backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g_exit_status = 128 + sig;
	}
}

/* handle_signal();
 *	- Parameters:
 *		- int num: the signal number to handle 
 *	 	  (1 for parent process, 2 for child process);
 *		- t_data *data: main struct, for the exit status;
 *
 *	- Configures the signal handling for the minishell.
 *	- struct termios: is used to store terminal attributes, 
 *	  which control various aspects of terminal behavior.
 *	- tcgetattr: retrieves the terminal attributes.
 *	- The ECHOCTL flag is turns off (clears), 
 *	  so the control characters won't be echoed.
 *		- c_lflag: local flags.
 *		- ECHOCTL: controls whether the terminal echoes control 
 *	  	  characters as ^X. 
 *	- When 'num' is 1 (signal is in the parent process):
 *		- SIGINT is set to call the 'restore_prompt' function 
 *		  when received (used for Ctrl-C).
 *		- SIGQUIT is set to be ignored (used for Ctrl-\).
 *	- When 'num' is 2 (signal is in a child process):
 *		- SIGINT is set to call the 'ctrl_c' function 
 *		  when received (used for Ctrl-C).
 *		- SIGQUIT is set to call the 'backslash' function 
 *		  when received (used for Ctrl-\).
 *	- It updates the 'data->status' with the value of 'g_exit_status'.
 *
 *	NOTE: Ctrl-D is not a signal it is a EOF discripter. 
 *		  So Ctrl-D gets handeld in the main().
 */
void	handle_signal(int num, t_data *data)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
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
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	data->status = g_exit_status;
}
