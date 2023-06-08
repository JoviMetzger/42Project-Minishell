/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 17:26:12 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	quote_check(char *str)
{
	int	i;
	int	d_quo;
	int	s_quo;

	i = -1;
	d_quo = 0;
	s_quo = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			s_quo++;
		if (str[i] == '\"')
			d_quo++;
	}
	if (s_quo % 2 != 0 || d_quo % 2 != 0)
	{
		printf("miss another quote");
		return (1);
	}
	return (0);
}

t_token	*tokenized(char *str)
{
	t_token		*top;
	t_token		*curr;
	int		i;

	i = -1;
	curr = top;
	if (quote_check(str) == 1)
		return ;
	top = split_token(str);
	while (curr != NULL)
	{
		if (t_strcmp(curr->str, "|") == 0)
			curr->type = PIPE;
		else if (t_strcmp(curr->str, "<") == 0)
			curr->type = INPUT_REDIRECTION;
		else if (t_strcmp(curr->str, ">") == 0)
			curr->type = OUTPUT_REDIRECTION;
		else if (t_strcmp(curr->str, "<<") == 0)
			curr->type = HERE_DOCUMENT;
		else if (t_strcmp(curr->str, ">>") == 0)
			curr->type = APPEND_REDIRECTION;
		else
			curr->type = WORD;
		curr = curr->next;
	}
}

