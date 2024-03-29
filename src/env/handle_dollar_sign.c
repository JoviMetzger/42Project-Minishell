/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_dollar_sign.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/13 10:48:10 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*dollar_split(char *str, int quo)
{
	int		i;
	t_token	*top;

	i = 0;
	top = NULL;
	if (!str)
		return (new_token(NULL));
	while (str[i])
	{
		if (str[i] == '\'' && quo == 0)
			i = split_with_quote(str, i, '\'', &top) - 1;
		else if (str[i] == '\"' && quo == 0)
			i = split_with_quote(str, i, '\"', &top) - 1;
		else if (str[i] == '<')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '$')
			i = dollar_split_dollar(str, i, &top);
		else if (!ft_isspace(str[i]))
			i = dollar_split_nondollar(str, i, &top, quo);
		else if (ft_isspace(str[i]))
			i = split_spaces_char(str, i, &top);
		else
			i++;
	}
	return (top);
}

void	swap_val(t_token **top, char **envp)
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
			dollar_swap_val(&curr, envp);
		curr = curr->next;
	}
}

char	*token_to_str(t_token **top)
{
	t_token	*curr;
	char	*lang_str;

	if (!*top)
		return (NULL);
	curr = *top;
	lang_str = NULL;
	while (curr != NULL)
	{
		if (curr->str)
			lang_str = add_str_to_strend(lang_str, curr->str);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free_token(*top);
	return (lang_str);
}
