/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:40 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/19 16:02:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_extension();
 *  - This function checks if the given string starts with the option '-n'.
 *  - It verifies that every character following the '-' is 'n'.
 *  - Returns 0 if the condition is met, otherwise returns 1.
 */
static int	ft_extension(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

/* ft_print_echo();
 *	- Parameters:
 *		- char **input: the whole input command line, for the 'echo' command;
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
	while (input[i] && ft_extension(input[i]) == 0)
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
 *	- Parameters:
 *		- char **input: The whole input command line, split into a char**;
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
	if (input[1] == 0)
		return (0);
	if (ft_argc(input) > 1)
		ft_print_echo(input);
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
