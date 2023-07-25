/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/25 13:16:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_argc();
 *	- Utility function; used in built-in commands to count the number 
 *	  of arguments in a string (char**).
 *	- It counts the number of elements in the input array until it reaches 
 *	  the null-terminating element (NULL).
 *	- Returns the count of arguments in the input array.
 */
int	ft_argc(char **input)
{
	int	len;

	len = 0;
	while (input[len])
		len++;
	return (len);
}

/* ft_is_digit();
 *	- Used in ft_exit() to check if a given string consists of 
 *	  valid numeric characters ('0' to '9'), '-' or '+'.
 */
int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}
