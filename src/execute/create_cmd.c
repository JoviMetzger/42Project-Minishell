/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 11:37:42 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_command(t_token **curr, t_data *all, int index)
{
	int		len;
	char	**words;
	t_cmd	*new;

	len = cmd_len(curr, (*curr)->index);
	words = extract_command_words(curr, len);
	new = new_cmd(words, len);
	new->index = index;
	add_cmd_end(&all->cmd, new);
}

char	**extract_command_words(t_token **curr, int len)
{
	char	**words;
	int		i;

	words = malloc(sizeof(char *) * len);
	if (!words)
		print_error(NULL, 0);
	words[len - 1] = NULL;
	i = 0;
	while ((*curr)->type != PIPE && *curr != NULL && i < len)
	{
		if ((*curr)->type == WORD && (*curr)->str)
		{
			words[i] = ft_strdup((*curr)->str);
			i++;
		}
		if (!(*curr)->next)
			break ;
		*curr = (*curr)->next;
	}
	return (words);
}

void	token_to_cmd(t_data *all)
{
	t_token	*curr;
	int		index;

	curr = all->token;
	all->cmd = NULL;
	index = 0;
	while (curr)
	{
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			handle_single_command(&curr, all, index);
			index++;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	all->cmd_len = index;
	add_redirection(all);
}
