/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/31 15:13:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_atoll();
 *	- This function converts a string 'str' to an unsigned long long integer.
 *	- Returns the unsigned long long int.
 */
unsigned long long int	ft_atoll(const char *str)
{
	unsigned long long int	result;
	int						sign;
	int						i;

	result = 0;
	sign = 1;
	i = 0;
	while ((*str == ' ') || (*str == '\f')
		|| (*str == '\n') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* is_llong_int();
 *	- This function checks if the given string 'str' 
 *	  represents a valid long long integer.
 *	- The function verifies if the string 'str' is a valid representation 
 *	  of a long long integer.
 *	- It checks for special cases, such as 
 *	  the minimum long long int value "-9223372036854775808".
 *	- If the length of the string is greater than 20 characters, 
 *	  it returns false to prevent overflow.
 *	- It handles leading '+' or '-' signs, 
 *	  skipping them before performing the validation.
 *	- The function then iterates through the remaining characters in 'str' 
 *	  and checks if each character is a digit (0-9).
 *	- If the long long integer overflows or contains non-digit characters, 
 *	  it returns false; otherwise, it returns true.
 */
bool	is_llong_int(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str++;
	}
	return (true);
}

/* ft_llint_check();
 *	- Checks if the input string represents a valid long long integer 
 *	  and converts it to a long long int.
 *	- The converted long long int is assigned to the 'exit_code' and returned.
 *	- Returns the 'exit_code' as a long long integer if the input string 
 *	  represents a valid long long int.
 *	- If the input is not a valid long long int, it displays an error message 
 *	  to STDERR and returns 255 as the exit code.
 *	- If the converted long long int is out of the range of long long int, 
 *	  it also returns 255 as the exit code.
 */
static int	ft_llint_check(char **str)
{
	int				exit_code;
	long long int	is_long;

	if (is_llong_int(str[1]))
	{
		is_long = ft_atoll(str[1]);
		if (is_long >= LLONG_MIN && is_long <= LLONG_MAX)
			exit_code = ft_atoll(str[1]);
		else
			exit_code = 255;
	}
	else
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			STDERR_FILENO);
		exit_code = 255;
	}
	return (exit_code);
}

/* determine_exit_code();
 *	- This function determines the exit code to be used for the 'exit' command.
 *	- It checks if the provided argument is a 
 *	  valid numeric representation (long long integer).
 *	- If the argument is a valid numeric representation, 
 *	  it converts it to a long long int using ft_llint_check().
 *	- Returns the determined exit code as a long long integer if the argument 
 *	  is a valid numeric representation.
 *	- If the argument is not a valid numeric representation, 
 *	  it displays an error message to STDERR and returns 255 as the exit code.
 */
static int	determine_exit_code(char **str)
{
	int				exit_code;

	exit_code = 0;
	if (ft_is_digit(str[1]) == 0)
	{
		exit_code = ft_llint_check(str);
	}
	else 
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 
			STDERR_FILENO);
		exit_code = 255;
	}
	return (exit_code);
}

/* ft_exit();
 *	- Parameters:
 *		- char **input: the whole input command line, split into a char**;
 *
 *	- This function implements the 'exit' command behavior in the shell.
 *	- It displays the "exit" message to STDOUT.
 *	- If there are more than two arguments after 'exit', 
 *	  it sets the shell's status to EXIT_FAILURE and displays 
 *	  an error message to STDERR for having too many arguments.
 *	- If there is one argument (besides 'exit'), 
 *	  it determines the exit code using determine_exit_code() function, 
 *	  sets the shell's status accordingly, 
 *	  and exits the shell with the determined exit code.
 *	- If there are no arguments after 'exit', 
 *	  it sets the shell's status to EXIT_SUCCESS and exits the shell.
 */
int	ft_exit(char **input)
{
	int	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_argc(input) > 2)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	}
	else if (ft_argc(input) == 2)
	{
		g_exit_status = determine_exit_code(input);
		exit(g_exit_status);
	}
	else
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		exit(g_exit_status);
	}
	return (g_exit_status);
}
