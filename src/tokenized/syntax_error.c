/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 12:55:41 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/24 21:32:33 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error_check(char *input)
{
	if (input[0] == '|' && input[1] == '|' )
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n",
			STDERR_FILENO);
		return (258);
	}
	else if (input[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 
			STDERR_FILENO);
		return (258);
	}
	else if (ft_strchr("><", input[ft_strlen(input) - 1]))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (258);
	}
	else
		g_exit_status = 0;
	return (0);
}
