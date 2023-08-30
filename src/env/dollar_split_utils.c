/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_split_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 15:14:34 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/30 14:57:53 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_split_dollar(char *str, int i, t_token **top)
{
	char	*line;
	int		one_len;

	if (str[i + 1] && str[i + 1] == '$')
	{
		line = ft_substr(str, i, 2);
		add_token_end(top, new_token(line));
		i += 2;
	}
	else if (str[i + 1] && str[i + 1] == '?')
	{
		line = ft_substr(str, i, 2);
		add_token_end(top, new_token(line));
		i += 2;
	}
	else
	{
		one_len = dollar_len(&str[i + 1]) + 1;
		line = ft_substr(str, i, one_len);
		add_token_end(top, new_token(line));
		i += one_len;
	}
	return (i);
}

void	dollar_swap_val(t_token **curr, char **envp)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcmp((*curr)->str, "$") == 0)
	{
		free((*curr)->str);
		(*curr)->str = ft_strdup("$");
	}
	else if (ft_strcmp((*curr)->str, "$$") == 0)
	{
		free((*curr)->str);
		(*curr)->str = ft_strdup("id");
	}
	else if (ft_strcmp((*curr)->str, "$?") == 0)
	{
		free((*curr)->str);
		(*curr)->str = ft_itoa(g_exit_status);
	}
	else if ((*curr)->str[0] == '$' && (*curr)->str[1] != '$')
	{
		free((*curr)->str);
		tmp = find_env(&(*curr), envp);
		if (!tmp)
			(*curr)->str = NULL;
		else
			(*curr)->str = ft_strdup(tmp);
	}
}

char	*add_str_to_strend(char *lang_str, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!lang_str)
		lang_str = ft_strdup(str);
	else
	{
		tmp = lang_str;
		lang_str = ft_strjoin(lang_str, str);
		free(tmp);
	}
	return (lang_str);
}

int	dollar_split_nondollar(char *str, int i, t_token **top, int quo)
{
	char	*line;
	int		one_len;

	one_len = non_dollar_len(&str[i], quo);
	line = ft_substr(str, i, one_len);
	add_token_end(top, new_token(line));
	i += one_len;
	return (i);
}
