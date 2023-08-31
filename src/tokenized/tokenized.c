/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/19 11:26:03 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	if_dquo(t_token *curr, t_token *to_tmp, char **envp)
{
	if (!envp)
		return ;
	to_tmp = dollar_split(curr->str, DQUO);
	swap_val(&to_tmp, envp);
	free(curr->str);
	curr->str = token_to_str(&to_tmp);
	curr->type = WORD;
}

static t_token	*extract_words(t_token *curr, char **words, char **envp)
{
	t_token	*to_tmp;
	char	*tmp;

	to_tmp = NULL;
	tmp = NULL;
	while (curr && (curr->type == WORD
			|| curr->type == SQUO || curr->type == DQUO))
	{
		if (curr->str && curr->type == DQUO)
			if_dquo(curr, to_tmp, envp);
		free_token(to_tmp);
		if (!*words)
			*words = ft_strdup(curr->str);
		else
		{
			tmp = *words;
			*words = ft_strjoin(*words, curr->str);
			free(tmp);
		}
		if (check_type_break(curr))
			break ;
		curr = curr->next;
	}
	return (curr);
}

t_token	*delspace_jointoken(t_token **token, t_token *top, 
	char *words, char **envp)
{
	t_token	*curr;
	t_token	*new;

	curr = *token;
	top = NULL;
	while (curr)
	{
		if (curr && (curr->type == WORD || curr->type == SQUO
				|| curr->type == DQUO))
		{
			words = NULL;
			curr = extract_words(curr, &words, envp);
			new = new_token(words);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (curr && curr->type != SPACES)
			add_token_end(&top, copy_token(curr));
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (top);
}

static void	ft_assign_to_enum(t_token *curr)
{
	while (curr != NULL)
	{
		if (curr->str && curr->prev
			&& curr->prev->type == INPUT_RE
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = INFILE;
		else if (curr->str && curr->prev
			&& curr->prev->type == OUTPUT_RE 
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = OUTFILE;
		else if (curr->str && curr->prev
			&& curr->prev->type == APPEND_RE
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = APPFILE;
		else if (curr->str && curr->prev
			&& curr->prev->type == HERE_DOC
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = DELIMI;
		else if (curr->str && (curr->type == EMPTY 
				|| curr->type == SQUO || curr->type == DQUO))
			curr->type = WORD;
		if (!curr->next)
			return ;
		curr = curr->next;
	}
}

int	tokenized(t_data *all)
{
	t_token		*curr;
	t_token		*to_tmp;
	char		**envp;
	char		*words;

	words = NULL;
	curr = NULL;
	envp = ft_get_envp(all->env);
	if (quote_check(all->input) == 1)
		return (1);
	to_tmp = NULL;
	to_tmp = dollar_split(all->input, 0);
	swap_val(&to_tmp, envp);
	free(all->input);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp, curr, words, envp);
	free_token(to_tmp);
	curr = all->token;
	ft_assign_to_enum(curr);
	free_envp(envp);
	return (0);
}
