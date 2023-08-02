/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tool_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 10:35:53 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 12:01:24 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_isspace();
 *	- Function checks for whitespace characters 
 *	  (space, tab, newline, vertical tab, form feed, carriage return)
 */
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v' 
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}
