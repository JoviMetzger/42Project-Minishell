/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2_dollar_sign.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/01 20:58:52 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_val(t_token **top, char **envp, t_data *all)
{
	t_token	*curr;
	char	*lang_str;

	curr = *top;
	lang_str = NULL;
	while (curr != NULL)
	{
		if (curr->str)
		{
			if (ft_strcmp(curr->str, "$") == 0)
				curr->str = "$";
			else if (ft_strcmp(curr->str, "$$") == 0)
				curr->str = "id";
			else if (ft_strcmp(curr->str, "$?") == 0)
				curr->str = ft_itoa(all->status);
			else if (curr->str[0] == '$' && curr->str[1] != '$')
				curr->str = find_env(&curr, envp);
		}
		curr = curr->next;
	}
}

char	*token_to_str(t_token **top)
{
	t_token	*curr;
	char	*lang_str;

	if (!*top)
		return (NULL);
	curr = *top;
	lang_str = NULL;
	while (curr != NULL)
	{
		if (curr->str)
		{
			if (!lang_str)
				lang_str = ft_strdup(curr->str);
			else
				lang_str = ft_strjoin(lang_str, curr->str);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (lang_str);
}
