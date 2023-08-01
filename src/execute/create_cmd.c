/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/31 22:41:04 by jmetzger      ########   odam.nl         */
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
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->words = words;
	new->next = NULL;
	new->len = len;
	new->redi = NULL;
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

static void	ft_token_loop(t_data *all, t_cmd *new, t_token *curr, char **words)
{
	int		len;
	int		i;

	i = 0;
	if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
	{
		len = cmd_len(&curr, curr->index);
		words = malloc(sizeof(char *) * len);
		if (!words)
			print_error(NULL, 0);
		words[len - 1] = NULL;
		while (curr->type != PIPE && curr != NULL && i < len)
		{
			if (curr->type == WORD && curr->str)
			{
				words[i] = ft_strdup(curr->str);
				i++;
			}
			if (!curr->next)
				break ;
			curr = curr->next;
		}
		new = new_cmd(words, len);
		add_cmd_end(&all->cmd, new);
	}
}

void	token_to_cmd(t_data *all)
{
	t_cmd	*new;
	t_token	*curr;
	char	**words;

	curr = all->token;
	all->cmd = NULL;
	new = NULL;
	words = NULL;
	while (curr)
	{
		ft_token_loop(all, new, curr, words);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	add_redirection(all);
}
