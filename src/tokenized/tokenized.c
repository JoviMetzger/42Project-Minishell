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
	char	*tmp;

	to_tmp = dollar_split(curr->str, DQUO);
	swap_val(&to_tmp, envp);
	tmp = curr->str;
	curr->str = token_to_str(&to_tmp);
	free(tmp);
	curr->type = WORD;
	free_token(to_tmp);
}

static char	*extract_words(t_token *curr, char **envp)
{
	char	*words;
	t_token	*to_tmp;

	words = NULL;
	to_tmp = NULL;
	while (curr && (curr->type == WORD
			|| curr->type == SQUO || curr->type == DQUO))
	{
		if (curr->str && curr->type == DQUO)
			if_dquo(curr, to_tmp, envp);
		if (!words)
			words = ft_strdup(curr->str);
		else
			words = ft_strjoin(words, curr->str);
		if (!curr->next || (curr->next && (curr->next->type == SPACES
					|| curr->next->type == PIPE 
					|| curr->next->type == INPUT_RE
					|| curr->next->type == OUTPUT_RE 
					|| curr->next->type == HERE_DOC
					|| curr->next->type == APPEND_RE)))
			break ;
		curr = curr->next;
	}
	return (words);
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
			words = extract_words(curr, envp);
			new = new_token(words);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (curr && curr->type != SPACES)
		{
			new = copy_token(curr);
			add_token_end(&top, new);
		}
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
	envp = ft_get_envp(all->env);
	curr = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	to_tmp = NULL;
	to_tmp = dollar_split(all->input, 0);
	swap_val(&to_tmp, envp);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp, curr, words, envp);
	free_token(to_tmp);
	curr = all->token;
	ft_assign_to_enum(curr);
	free_envp(envp);
	return (0);
}
