/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/09 15:46:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* extract_words();
 *	- Parameter:
 *		- t_token **curr: the current token in the linked list;
 *
 *	- The function iterates through the linked list starting from 'curr'.
 *	- While encountering consecutive WORD or SQUO tokens, 
 *	  it concatenates their strings to form a single string 'words'.
 *	- When it reaches a token of a different type 
 *	  (SPACES, PIPE, INPUT_RE, OUTPUT_RE, HERE_DOC, APPEND_RE), 
 *	  it stops the extraction and returns the concatenated 'words'.
 */
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

/* delspace_jointoken():
 *	- Parameters:
 *		- t_token **token: the top of the original token linked list;
 *		- char *words: the concatenated string of WORD and SQUO tokens;
 *
 *	- The function iterates through the original token linked list 'token'.
 *	- If it encounters a sequence of consecutive WORD or SQUO tokens, 
 *	  it calls extract_words() to extract the words and 
 *	  creates a new token of type WORD with the concatenated 'words'.
 *	- If the current token is of any type other than SPACES, 
 *	  it creates a new token by copying the current token.
 */
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
 *		- char **envp: the environment variables;
 *
 *	- The function starts by checking if the input contains balanced quotes 
 *	  using quote_check() and exits with an error if the check fails.
 *	- It then tokenizes the input using dollar_split() to handle dollar variables
 *	  and split_token() to split the input into separate tokens.
 *	- The tokens are then passed through delspace_jointoken() to extract words 
 *	  and create a new token linked list.
 *	- After that, the function assigns token types 
 *	  to each token using ft_assign_to_enum().
 */
void	tokenized(t_data *all)
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
	swap_val(&to_tmp, all);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp, words);
	curr = all->token;
	ft_assign_to_enum(curr);
}
