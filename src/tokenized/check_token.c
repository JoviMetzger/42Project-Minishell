/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:56:36 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 22:24:39 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_check_token();
 *	- Parameters:
 *		- t_token *curr: The current token in the token linked list;
 *		- t_token *new_top: The new token that should be added;
 * 
 *	- The function loops through the token linked list starting 
 *	  from the current token 'curr' and 
 *	  concatenates consecutive non-space tokens into a single string 'str'.
 *	- It creates a new token and adds it to the end of 
 *	  the new token linked list pointed to by 'new_top'.
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
}
