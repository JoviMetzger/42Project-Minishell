/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:04:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 12:05:06 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_token	*new_token(char *str)
{
	t_token	new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = EMPTY;
	new->next = NULL;
	return (new);
}

void	add_token_end(t_token **top, t_token *new)
{
	t_token	*current;

	current = *top;
	if (!new)
		reuturn ;
	if (!*top)
		*top = new;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}