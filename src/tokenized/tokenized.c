/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 13:49:32 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_words(t_token **curr)
{
	char	*words;

	words = NULL;
	while (*curr && ((*curr)->type == WORD || (*curr)->type == SQUO))
	{
		if (!words)
			words = ft_strdup((*curr)->str);
		else
			words = ft_strjoin(words, (*curr)->str);
		if (!(*curr)->next || ((*curr)->next && ((*curr)->next->type == SPACES
					|| (*curr)->next->type == PIPE 
					|| (*curr)->next->type == INPUT_RE
					|| (*curr)->next->type == OUTPUT_RE 
					|| (*curr)->next->type == HERE_DOC
					|| (*curr)->next->type == APPEND_RE)))
			break ;
		*curr = (*curr)->next;
	}
	return (words);
}

t_token	*delspace_jointoken(t_token **token, char *words)
{
	t_token	*curr;
	t_token	*top;
	t_token	*new;

	curr = *token;
	top = NULL;
	while (curr)
	{
		if (curr->type == WORD || curr->type == SQUO)
		{
			words = extract_words(&curr);
			new = new_token(words);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (curr->type != SPACES)
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

/* ft_assign_to_enum();
 *	- Convert specific tokens to their corresponding enum types based on 
 *	  their previous token type.
 *	- The function checks the string value and type of the current token 'curr' 
 *	  and its previous token 'curr->prev'.
 *	- If the current token type is EMPTY, and its previous token's type matches 
 *	  specific conditions 
 *	  (INPUT_RE, OUTPUT_RE, APPEND_RE, or HERE_DOC), it updates the current 
 *	  token's type accordingly.
 *	- If the token's type is EMPTY or SQUO (single quote), it is set to WORD.
 */
void	ft_assign_to_enum(t_token *curr)
{
	while (curr != NULL)
	{
		if (curr->str && curr->prev && curr->prev->type == INPUT_RE 
			&& curr->type == WORD)
			curr->type = INFILE;
		else if (curr->str && curr->prev && curr->prev->type == OUTPUT_RE 
			&& curr->type == WORD)
			curr->type = OUTFILE;
		else if (curr->str && curr->prev && curr->prev->type == APPEND_RE 
			&& curr->type == WORD)
			curr->type = APPFILE;
		else if (curr->str && curr->prev && curr->prev->type == HERE_DOC 
			&& curr->type == WORD)
			curr->type = DELIMI;
		else if (curr->str && (curr->type == EMPTY || curr->type == SQUO))
			curr->type = WORD;
		if (!curr->next)
			return ;
		curr = curr->next;
	}
}

/* tokenized();
 *	- Parameters:
 *		- t_data *all: the main data struct;
 *		- char **envp: The environment variables;
 *
 */
void	tokenized(t_data *all, char **envp)
{
	t_token		*curr;
	t_token		*to_tmp;
	char		*words;

	curr = NULL;
	words = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	to_tmp = NULL;
	to_tmp = dollar_split(all->input);
	swap_val(&to_tmp, envp, all);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp, words);
	curr = all->token;
	ft_assign_to_enum(curr);
}
