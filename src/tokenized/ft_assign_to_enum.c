/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_assign_to_enum.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/03 11:04:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_input();
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
static void	ft_input(t_token *curr)
{
	if (curr->str && curr->prev && curr->prev->type == INPUT_RE 
		&& curr->type == EMPTY)
		curr->type = INFILE;
	else if (curr->str && curr->prev && curr->prev->type == OUTPUT_RE 
		&& curr->type == EMPTY)
		curr->type = OUTFILE;
	else if (curr->str && curr->prev && curr->prev->type == APPEND_RE 
		&& curr->type == EMPTY)
		curr->type = APPFILE;
	else if (curr->str && curr->prev && curr->prev->type == HERE_DOC 
		&& curr->type == EMPTY)
		curr->type = DELIMI;
	else if (curr->str && (curr->type == EMPTY || curr->type == SQUO))
		curr->type = WORD;
}

/* ft_assign_to_enum();
 *	- Parameters:
 *		- t_token *curr: The current token in the token linked list;
 *
 *	- The function checks the string value of the current token 'curr' and
 *	  assigns the appropriate enum type to it based on specific string matches.
 *	- If the current token's string value matches one of the symbols 
 *	  ("|", "<", ">", "<<", ">>") it is assigned the corresponding enum type.
 *	- Else (value does not match any of the symbols or its type is not EMPTY), 
 *	  it calls ft_input() to convert it to a different enum type 
 *	  based on its previous token's type.
 */
void	ft_assign_to_enum(t_token *curr)
{
	if (curr->str && ft_strcmp(curr->str, "|") == 0 
		&& curr->type == EMPTY)
		curr->type = PIPE;
	else if (curr->str && ft_strcmp(curr->str, "<") == 0 
		&& curr->type == EMPTY)
		curr->type = INPUT_RE;
	else if (curr->str && ft_strcmp(curr->str, ">") == 0 
		&& curr->type == EMPTY)
		curr->type = OUTPUT_RE;
	else if (curr->str && ft_strcmp(curr->str, "<<") == 0 
		&& curr->type == EMPTY)
		curr->type = HERE_DOC;
	else if (curr->str && ft_strcmp(curr->str, ">>") == 0 
		&& curr->type == EMPTY)
		curr->type = APPEND_RE;
	else
		ft_input(curr);
	if (!curr->next)
		return ;
}
