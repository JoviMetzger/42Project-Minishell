/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/25 14:37:14 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_pwd();
 * 	- This function retrieves the current working directory using getcwd().
 * 	- If successful, it prints the current working directory to standard output
 * 	  followed by a newline.
 * 	- If getcwd() fails, it displays an error message using perror() 
 * 	  and returns EXIT_FAILURE.
 */
int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
	free(buf);
	return (EXIT_SUCCESS);
}
