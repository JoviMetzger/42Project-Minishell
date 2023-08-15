/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tool_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 10:35:53 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/13 10:40:18 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	have_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

int	dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i])
			|| str[i] == '\'' || str[i] == '\"'
			|| str[i] == '|' || str[i] == '<'
			|| str[i] == '>')
			break ;
		i++;
	}
	return (i);
}

int	space_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	non_dollar_len(char *str, int quo)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i]))
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && quo == 0)
			break ;
		i++;
	}
	return (i);
}
