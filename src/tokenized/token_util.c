/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:04:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 15:32:13 by yizhang       ########   odam.nl         */
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
	while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
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
	new->next = NULL;
	return (new);
}

void	add_token_end(t_token **top, t_token *new)
{
	t_token	*current;

	current = *top;
	if (!new)
		return ;
	if (!*top)
	{
		*top = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
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