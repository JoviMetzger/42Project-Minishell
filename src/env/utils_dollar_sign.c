/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_dollar_sign.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/31 22:42:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[i] == '$' || ft_isspace(str[i]))
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

int	non_dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i]))
			break ;
		i++;
	}
	return (i);
}
