/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:56:36 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 21:44:36 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_check_token();
 *	- Parameters:
 *		- t_token *curr: the current token in the linked list;
 *		- t_token *new_top: the new token where the new token will be added;
 *
 *	- The function iterates through the linked list 'curr' until it encounters 
 *	  a token of type SPACES (space token) or reaches the end of the list.
 *	- During this iteration, it concatenates the string representations of 
 *	  these tokens to form a single string 'str'.
 *	- If 'str' is NULL, it means that there were no non-space tokens 
 *	  in the sequence, and the function sets 'str' to NULL.
 *	- Otherwise, it creates a new token using new_token() with 'str' 
 *	  and adds this token to the end of the new token linked list 'new_top'
 *	  using the add_token_end() function.
 *	- After processing the sequence of tokens, the function prints 
 *	  the concatenated 'str' using printf() for debugging purposes.
 */
static void	ft_check_token(t_token *curr, t_token *new_top)
{
	t_token	*new;
	char	*str;

	str = NULL;
	while (curr && !(curr->type == SPACES))
	{
		if (!str)
		{
			if (!curr->str)
				str = NULL;
			else
				str = ft_strdup(curr->str);
		}
		else
			str = ft_strjoin(str, curr->str);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	printf("str:%s\n", str);
	new = new_token(str);
	add_token_end(&new_top, new);
}

/* check_token();
 *	- Parameters:
 *		- t_data *all: the main data struct;
 * 
 *	- The function is the entry point for checking 
 *	  and processing tokens in the token linked list.
 *	- It initializes a new token linked list 'new_top' 
 *	  to store the concatenated tokens.
 *	- The function then iterates through the original token linked list 
 *	  starting from 'all->token' and calls ft_check_token() for each token 
 *	  to concatenate non-space tokens.
 *	- The resulting new token linked list 'new_top' contains tokens with 
 *	  consecutive non-space tokens combined into single tokens.
 *	- The original token linked list is updated to point to 'new_top'.
 */
void	check_token(t_data *all)
{
	t_token	*curr;
	t_token	*new_top;

	new_top = NULL;
	curr = all->token;
	all->token = new_top;
	while (curr)
	{
		if (curr && !(curr->type == SPACES))
		{
			ft_check_token(curr, new_top);
		}
		if (!curr->next)
			return ;
		curr = curr->next;
	}
	free_token(curr);
}
