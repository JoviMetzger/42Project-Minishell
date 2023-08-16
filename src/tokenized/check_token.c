/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:56:36 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 11:00:05 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_token(t_token *curr, t_token *new_top)
{
	t_token	*new;
	char	*str;

	str = NULL;
	while (curr && !(curr->type == SPACES))
	{
		if (!str)
		{
			if (!curr->str)
				str = NULL;
			else
				str = ft_strdup(curr->str);
		}
		else
			str = ft_strjoin(str, curr->str);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	printf("str:%s\n", str);
	new = new_token(str);
	add_token_end(&new_top, new);
}

void	check_token(t_data *all)
{
	t_token	*curr;
	t_token	*new_top;

	new_top = NULL;
	curr = all->token;
	all->token = new_top;
	while (curr)
	{
		if (curr && !(curr->type == SPACES))
		{
			ft_check_token(curr, new_top);
		}
		if (!curr->next)
			return ;
		curr = curr->next;
	}
	free_token(curr);
}
