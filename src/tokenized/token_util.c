/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:04:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 10:59:10 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\'' || c == '\"')
	{
		while (str[i] && str[i] != c)
			i++;
		return (i);
	}
	while (str[i] && str[i] != c && !ft_isspace(str[i]) && str[i] != '\''
		&& str[i] != '\"' && str[i] != '|'
		&& str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

t_token	*new_token(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = EMPTY;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*copy_token(t_token *old)
{
	t_token	*new;

	if (!old)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(old->str);
	new->type = old->type;
	new->next = NULL;
	new->prev = NULL;
	new->index = 0;
	return (new);
}

void	add_token_end(t_token **top, t_token *new)
{
	t_token	*current;
	int		i;

	i = 1;
	current = *top;
	if (!new)
		return ;
	if (!current)
	{
		*top = new;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
		i++;
	}
	current->next = new;
	new->prev = current;
	new->index = i;
}

void	swap_val(t_token **top, char **envp, t_data *all)
{
	t_token	*curr;
	char	*tmp;

	curr = *top;
	tmp = NULL;
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC)
		{
			if (curr->next && curr->next->type != SPACES)
				curr->next->type = DELIMI;
			else if (curr->next && curr->next->type == SPACES
				&& curr->next->next && curr->next->next->type != SPACES)
				curr->next->next->type = DELIMI;
		}
		if (curr->str && curr->type != DELIMI)
			dollar_swap_val(&curr, envp, all);
		curr = curr->next;
	}
}
