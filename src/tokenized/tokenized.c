/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/01 20:36:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_data *all, t_token **top, char **envp)
{
	t_token		*curr;
	t_token		*to_tmp;
	char		*tmp;

	curr = *top;
	tmp = NULL;
	to_tmp = NULL;
	while (curr != NULL)
	{
		if (curr->str && have_dollar(curr->str) && curr->type != SQUO)
		{
			to_tmp = dollar_split(curr->str);
			swap_val(&to_tmp, envp, all);
			tmp = curr->str;
			curr->str = token_to_str(&to_tmp);
			free(tmp);
		}
		if (!curr->next)
			return ;
		curr = curr->next;
	}
}

static char	*concatenate_words(t_token **token)
{
	t_token	*curr;
	char	*words;

	curr = *token;
	words = NULL;
	while (curr && (curr->type == WORD || curr->type == SQUO))
	{
		if (!words)
			words = ft_strdup(curr->str);
		else
			words = ft_strjoin(words, curr->str);
		if (!curr->next || curr->type == SPACES)
			break ;
		curr = curr->next;
	}
	return (words);
}

static void	handle_non_word_tokens(t_token **token, t_token **top)
{
	t_token	*new;

	new = copy_token(*token);
	add_token_end(top, new);
	*token = (*token)->next;
}

t_token	*delspace_jointoken(t_token **token)
{
	t_token	*curr;
	t_token	*top;
	t_token	*new;
	char	*words;

	curr = *token;
	top = NULL;
	words = NULL;
	while (curr)
	{
		if (curr->type == WORD || curr->type == SQUO)
		{
			words = concatenate_words(&curr);
			new = new_token(words);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (curr->type != SPACES)
			handle_non_word_tokens(&curr, &top);
		if (!curr)
			break ;
		curr = curr->next;
	}
	return (top);
}

void	tokenized(t_data *all, char **envp)
{
	t_token		*curr;
	t_token		*to_tmp;
	char		*tmp;

	curr = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	tmp = NULL;
	to_tmp = NULL;
	to_tmp = dollar_split(all->input);
	swap_val(&to_tmp, envp, all);
	tmp = all->input;
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp);
	curr = all->token;
	while (curr != NULL)
	{
		ft_assign_to_enum(curr);
		curr = curr->next;
	}
}
