/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/06 17:33:24 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_to_cmd(t_data *all)
{
	t_cmd	*new;
	t_token	*curr;
	char	**words;
	int		len;
	int		i;
	int		index;

	curr = all->token;
	all->cmd = NULL;
	index = 0;
	while (curr)
	{
		i = 0;
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			len = cmd_len(&curr, curr->index);
			words = malloc(sizeof(char *) * len);
			if (!words)
				print_error(NULL, 0, all);
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
			new->index = index;
			add_cmd_end(&all->cmd, new);
			index++;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	all->cmd_len = index;
	add_redirection(all);
}

void	add_redirection(t_data *all)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!all->cmd || !all->token)
		return ;
	curr = all->token;
	cmd = all->cmd;
	cmd->redi = NULL;
	while (cmd != NULL && curr != NULL)
	{
		if (curr->type == INFILE || curr->type == OUTFILE
			|| curr->type == APPFILE || curr->type == DELIMI)
			add_token_end(&cmd->redi, copy_token(curr));
		else if (curr->type == PIPE)
			cmd = cmd->next;
		curr = curr->next;
	}
}

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
	new->next = NULL;
	new->redi = NULL;
	new->words = words;
	new->len = len;
	new->fd_in = 0;
	new->fd_out = 0;
	new->index = 0;
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
