/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 08:56:25 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/31 15:49:21 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			return (0);
		i++;
	}
	return (1);
}

static int	env_index(t_token *token, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(&token->str[1], "=");
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], tmp, ft_strlen(tmp)) != NULL)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}

char	*find_env(t_token **token, char **envp)
{
	int	index;
	int	i;

	i = 0;
	if (!*token)
		return (NULL);
	index = env_index(*token, envp);
	if (index == -1 || !envp[index])
		return (NULL);
	while (envp[index][i] != '=')
		i++;
	return (&envp[index][i + 1]);
}
