/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:40 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/25 21:34:33 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_print_echo();
 *	- char **input: the whole input command line, for the 'echo' command;
 *
 *	- This function prints the arguments provided to the 'echo' command.
 *	- It skips any leading '-n' arguments that indicate the 'no newline' option.
 *	- It then prints each argument separated by a space.
 *	- If the 'no newline' option (-n) is not present, it adds 
 *	  a newline character at the end.
 */
static void	ft_print_echo(char **input)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (input[i] && ft_strcmp(input[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	if (input[i])
	{
		ft_putstr_fd(input[i], STDOUT_FILENO);
		i++;
	}
	while (input[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(input[i], STDOUT_FILENO);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

/* ft_echo();
 *	- char **input: The whole input command line, split into a char**;
 *
 *	- This function implements the 'echo' command behavior in the shell.
 *	- It checks if the 'input' is not NULL.
 *	- If there are arguments (more than one), 
 *	  it prints them using ft_print_echo().
 *	- If there are no arguments, 
 *	  it prints a newline character to standard output.
 */
int	ft_echo(char **input)
{
	if (!input)
		return (EXIT_FAILURE);
	if (ft_argc(input) > 1)
		ft_print_echo(input);
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
