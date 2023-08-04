/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 11:19:05 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* cmd_len();
 *	- Parameters:
 *	  - t_token **token: token struct;
 *	  - int index: The index of the first token of the command 
 *		 sequence to be measured;
 *
 *	- Calculates the length of a command sequence starting from the given 
 *	  token index in the token linked list.
 *	- If the token index matches, count the number of tokens until 
 *	  the next PIPE token or the end of the list.
 *	- If the token is of type WORD and contains a valid string, increment i.
 *	- Else we move to the next token.
 */
int	cmd_len(t_token **token, int index)
{
	int		i;
	t_token	*curr;

	i = 1;
	curr = *token;
	while (curr != NULL)
	{
		if (curr->index == index)
		{
			while (curr->type != PIPE && curr)
			{
				if (curr->type == WORD && curr->str)
					i++;
				if (!curr->next)
					return (i);
				curr = curr->next;
			}
			return (i);
		}
		curr = curr->next;
	}
	return (i);
}

/* new_cmd();
 *	- Parameters:
 *	  - char **words: An array of strings representing the words 
 *		in the command;
 *	  - int len: The length of the command in number of words;
 *
 *	- Create a new node for a linked list.
 *	- Set the 'words' field to the given array of words.
 *	- Set the 'len' field to the provided length.
 *	- Set the 'next' field to NULL, 
 *	  as this new node will be added to the end of the linked list.
 *	- Set the 'redi' field to NULL initially, 
 *	  as redirection information is added later.
 */
t_cmd	*new_cmd(char **words, int len)
{
	int		tmp_in;
	int		tmp_out;
	t_cmd	*new;

	tmp_in = dup(0);
	tmp_out = dup(1);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->words = words;
	new->next = NULL;
	new->len = len;
	new->redi = NULL;
	new->index = 0;
	new->fd_in = tmp_in;
	new->fd_out = tmp_out;
	return (new);
}

/* add_cmd_end();
 *	- Parameters:
 *	  - t_cmd **top: the command struct;
 *	  - t_cmd *new: A pointer to the new command node to be added;
 *
 *	- Adds a new node to the end of the list.
 *	- If the list is empty, the new node becomes the first node (top).
 */
void	add_cmd_end(t_cmd **top, t_cmd *new)
{
	t_cmd	*curr;

	curr = *top;
	if (!new)
		return ;
	if (!*top)
	{
		*top = new;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
