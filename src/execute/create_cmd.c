/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 15:49:51 by jmetzger      ########   odam.nl         */
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
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->words = words;
	new->next = NULL;
	new->len = len;
	new->redi = NULL;
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

/* ft_token_loop();
 *	- Parameters:
 *	  - t_data *all: the main struct, to access the command struct;
 *	  - t_cmd *new: A pointer to the current command node being constructed;
 *	  - t_token *curr: A pointer to the current token being processed 
 *		in the token linked list;
 *	  - char **words: An array to hold the words of the current command 
 *		being constructed;
 *
 *	- This function is called from the token_to_cmd().
 *	- If the current token belongs to a new command sequence 
 *	  (before PIPE or at the beginning).
 *	- It calculate the length of the command with cmd_len().
 *	- If token of type is WORD, else it will skip over them.
 *		- It makes a copy the words of the command into 
 *		  the 'words' array with ft_strdup().
 *	- Create a new command node using new_cmd() with 
 *	  the 'words' array and its length.
 *	- Add the new command node to the end of 
 *	  the command linked list with add_cmd_end().
 */
static void	ft_token_loop(t_data *all, t_cmd *new, t_token *curr, char **words)
{
	int		len;
	int		i;

	i = 0;
	if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
	{
		len = cmd_len(&curr, curr->index);
		words = malloc(sizeof(char *) * len);
		if (!words)
			print_error(NULL, 0);
		words[len - 1] = NULL;
		while (curr->type != PIPE && curr != NULL && i < len)
		{
			if (curr->type == WORD && curr->str)
			{
				words[i] = ft_strdup(curr->str);
				i++;
			}
			if (!curr->next)
				break ;
			curr = curr->next;
		}
		new = new_cmd(words, len);
		add_cmd_end(&all->cmd, new);
	}
}

/* token_to_cmd();
 *	- Converts the token linked list into a command linked list. 
 *	- It sets up the necessary variables and calls ft_token_loop() 
 *	  to process the tokens and build the command linked list.
 */ 
void	token_to_cmd(t_data *all)
{
	t_cmd	*new;
	t_token	*curr;
	char	**words;

	curr = all->token;
	all->cmd = NULL;
	new = NULL;
	words = NULL;
	while (curr)
	{
		ft_token_loop(all, new, curr, words);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	add_redirection(all);
}
