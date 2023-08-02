/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_assign_to_enum.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 20:47:57 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_input();
 *	- Convert specific tokens to their corresponding enum types based 
 *	  on their previous token type.
 */
static void	ft_input(t_token *curr)
{
	if (curr->prev->type == INPUT_RE && curr->type == WORD)
		curr->type = INFILE;
	else if (curr->prev->type == OUTPUT_RE && curr->type == WORD)
		curr->type = OUTFILE;
	else if (curr->prev->type == APPEND_RE && curr->type == WORD)
		curr->type = APPFILE;
	else if (curr->prev->type == HERE_DOC && curr->type == WORD)
		curr->type = DELIMI;
}

/* ft_assign_to_enum();
 *	- Assign the correct enum type to each token based on its string value.
 *	- The function checks if the token's string value is NULL or 
 *	  if its type is SQUO (single quote). 
 *		- If either of these conditions is true, 
 *		  the token's type is set to WORD.
 *	- If the token's type is EMPTY, the function checks its string value 
 *	  to determine its enum type.
 *		- If the value matches one of the symbols ("|", "<", ">", "<<", ">>"), 
 *		  the corresponding enum type is assigned to the token.
 *	- If the token's type is not EMPTY and has a previous token (curr->prev), 
 *	  the function calls ft_input() to potentially convert the token 
 *	  to a different enum type based on the previous token's type.
 */
void	ft_assign_to_enum(t_token *curr)
{
	if (!curr->str || curr->type == SQUO)
		curr->type = WORD;
	else if (curr->type == EMPTY)
	{
		if (ft_strcmp(curr->str, "|") == 0)
			curr->type = PIPE;
		else if (ft_strcmp(curr->str, "<") == 0)
			curr->type = INPUT_RE;
		else if (ft_strcmp(curr->str, ">") == 0)
			curr->type = OUTPUT_RE;
		else if (ft_strcmp(curr->str, "<<") == 0)
			curr->type = HERE_DOC;
		else if (ft_strcmp(curr->str, ">>") == 0)
			curr->type = APPEND_RE;
	}
	else if (curr->prev)
	{
		ft_input(curr);
	}
	if (!curr->next)
		return ;
}
