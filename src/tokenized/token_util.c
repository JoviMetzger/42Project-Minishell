/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:04:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/04 14:11:47 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	if (c =='\'' || c =='\"')
	{
		while (str[i] && str[i] != c)
			i++;
		return (i);
	}
	while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"' && str[i] != '|' && str[i] != '<' && str[i] != '>')
		i++;
	return (i);	
}

t_token	*new_token(char *str)
{
	t_token	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->type = EMPTY;
	new->next = NULL;
	new->prev = NULL;
	new->index = 0;
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
	if (!*top)
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

//test: gcc token_util.c
/* int main(void)
{
	t_token *test;
	t_token *curr;

	test = NULL;
	add_token_end(&test,new_token("sfasdfdf"));
	add_token_end(&test,new_token("aaaa"));
	add_token_end(&test,new_token("ccccc"));
	add_token_end(&test,new_token("dddfdf"));
	add_token_end(&test,new_token("fffsdfdf"));
	curr = test;
	while (curr != NULL)
	{
		printf("%s\n", curr->str);
		curr = curr->next;
	}
	return 0;
} */