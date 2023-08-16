/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 11:01:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_len(t_token **token, int index)
{
	int		i;
	t_token	*curr;

	i = 1;
	curr = *token;
	while (curr != NULL)
	{
		if (curr->index == index)
		{
			while (curr->type != PIPE && curr)
			{
				if (curr->type == WORD && curr->str)
					i++;
				if (!curr->next)
					return (i);
				curr = curr->next;
			}
			return (i);
		}
		curr = curr->next;
	}
	return (i);
}

t_cmd	*new_cmd(char **words, int len)
{
	int		tmp_in;
	int		tmp_out;
	t_cmd	*new;

	tmp_in = dup(0);
	tmp_out = dup(1);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->words = words;
	new->next = NULL;
	new->len = len;
	new->redi = NULL;
	new->index = 0;
	new->fd_in = tmp_in;
	new->fd_out = tmp_out;
	return (new);
}

void	add_cmd_end(t_cmd **top, t_cmd *new)
{
	t_cmd	*curr;

	curr = *top;
	if (!new)
		return ;
	if (!*top)
	{
		*top = new;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
