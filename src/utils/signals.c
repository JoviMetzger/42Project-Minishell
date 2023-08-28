/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/28 11:49:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_signal_heredoc();
 *	- Display the here_doc sign (>)
 *	- And exit the process.
 */
void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		exit (g_exit_status = 1);
	}
}

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
		g_exit_status = 1;
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
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = sig + 128;
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
		g_exit_status = sig + 128;
	}
}

/* handle_signal();
 *	- Configures the signal handling for the minishell.
 *	- struct termios: is used to store terminal attributes, 
 *	  which control various aspects of terminal behavior.
 *	- tcgetattr: retrieves the terminal attributes.
 *	- The ECHOCTL flag is turns off (clears), 
 *	  so the control characters won't be echoed.
 *		- c_lflag: local flags.
 *		- ECHOCTL: controls whether the terminal echoes control 
 *	  	  characters as ^X. 
 *	- When num 1; signal is in the parent process:
 *		- SIGINT is set to call the 'restore_prompt' function 
 *		  when received (used for Ctrl-C).
 *		- SIGQUIT is set to be ignored (used for Ctrl-\).
 *	- When num 2; signal is in a child process:
 *		- Turn back on the control characters.
 *		- SIGINT is set to call the 'ctrl_c' function 
 *		  when received (used for Ctrl-C).
 *		- SIGQUIT is set to call the 'backslash' function 
 *		  when received (used for Ctrl-\).
 *	- When num 3; signal is in a here_doc:
 *		- SIGINT is set to call the 'signal_heredoc' function 
 *		  when received (used for Ctrl-C).
 *		- SIGQUIT is set to be ignored (used for Ctrl-\).
 *
 *	NOTE: Ctrl-D is not a signal it is a EOF discripter. 
 *		  So Ctrl-D gets handeld in the main().
 */
void	handle_signal(int num)
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
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
	if (num == 3)
	{
		signal(SIGINT, signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
