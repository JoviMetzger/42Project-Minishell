/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 10:58:49 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*delspace_jointoken(t_token **token, char **envp, t_data *all)
{
	t_token	*curr;
	t_token	*top;
	t_token	*new;
	char	*words;
	char	*tmp;
	t_token	*to_tmp;

	curr = *token;
	to_tmp = NULL;
	tmp = NULL;
	top = NULL;
	words = NULL;
	while (curr)
	{
		if (curr && (curr->type == WORD
				|| curr->type == SQUO || curr->type == DQUO))
		{
			words = NULL;
			while (curr && (curr->type == WORD
				|| curr->type == SQUO || curr->type == DQUO))
			{
				if(curr->str && curr->type == DQUO)
				{
					to_tmp = dollar_split(curr->str, DQUO);
					swap_val(&to_tmp, envp, all);
					tmp = curr->str;
					curr->str = token_to_str(&to_tmp);
					free(tmp);
				}
				if (!words)
					words = ft_strdup(curr->str);
				else
				{
					tmp = words;
					words = ft_strjoin(words, curr->str);
					free(tmp);
				}
				if (!curr->next || (curr->next && (curr->next->type == SPACES
							|| curr->next->type == PIPE
							|| curr->next->type == INPUT_RE
							|| curr->next->type == OUTPUT_RE
							|| curr->next->type == HERE_DOC
							|| curr->next->type == APPEND_RE)))
					break ;
				curr = curr->next;
			}
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
	free_token(*token);
	return (top);
}

void	give_token_type(t_data *all)
{
	t_token		*curr;

	curr = all->token;
	while (curr != NULL)
	{
		if (curr->str && curr->prev && curr->prev->type == INPUT_RE
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = INFILE;
		else if (curr->str && curr->prev && curr->prev->type == OUTPUT_RE
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = OUTFILE;
		else if (curr->str && curr->prev && curr->prev->type == APPEND_RE
			&& (curr->type == WORD || curr->type == SQUO))
			curr->type = APPFILE;
		else if (curr->str && curr->prev && curr->prev->type == HERE_DOC
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

char	*find_env_swap_dollar(t_data *all, char *swap_str, char **envp, int quo)
{
	t_token	*to_tmp;
	char	*tmp;

	tmp = NULL;
	to_tmp = dollar_split(swap_str, quo);
	swap_val(&to_tmp, envp, all);
	tmp = swap_str;
	swap_str = token_to_str(&to_tmp);
	free(tmp);
	return (swap_str);
}

void	tokenized(t_data *all)
{
	t_token		*curr;
	t_token		*to_tmp;
	char **envp;

	envp = ft_get_envp(all->env);
	curr = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	to_tmp = NULL;
	to_tmp = dollar_split(all->input, 0);
	swap_val(&to_tmp, envp, all);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp, envp, all);
}
