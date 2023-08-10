/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 15:40:40 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* handle_single_command();
 *	- Parameters:
 *		- t_token **curr: a pointer to the current token in the linked list;
 *		- t_data *all: the main data struct;
 *		- int index: the index of the command to be executed;
 *
 *	- The function calculates the length of the command by calling cmd_len() 
 *	  to count the number of tokens in the current command.
 *	- It then uses extract_command_words() to extract the words of the command 
 *	  and store them in a dynamically allocated char array.
 *	- A new t_cmd struct is created using new_cmd(), 
 *	  which takes the extracted words and the length of the command as input.
 *	- The index of the command is set, and the new command struct is added to 
 *	  the end of the command linked list using add_cmd_end().
 */
void	handle_single_command(t_token **curr, t_data *all, int index)
{
	int		len;
	char	**words;
	t_cmd	*new;

	len = cmd_len(curr, (*curr)->index);
	words = extract_command_words(curr, len);
	new = new_cmd(words, len);
	new->index = index;
	add_cmd_end(&all->cmd, new);
}

/* extract_command_words();
 *	- Parameters:
 *		- t_token **curr: the current token in the linked list;
 *		- int len: the number of tokens;
 *
 *	- The function allocates memory for an array of char pointers 
 *	  to store the words of the command.
 *	- It iterates through the linked list until it encounters a PIPE token, 
 *	  reaches the end of the list, or extracts 'len' words.
 *	- For each WORD token encountered, 
 *	  it duplicates the token's string and stores it in the char array.
 */
char	**extract_command_words(t_token **curr, int len)
{
	char	**words;
	int		i;

	words = malloc(sizeof(char *) * len);
	if (!words)
		print_error(NULL, 0);
	words[len - 1] = NULL;
	i = 0;
	while ((*curr)->type != PIPE && *curr != NULL && i < len)
	{
		if ((*curr)->type == WORD && (*curr)->str)
		{
			words[i] = ft_strdup((*curr)->str);
			i++;
		}
		if (!(*curr)->next)
			break ;
		*curr = (*curr)->next;
	}
	return (words);
}

/* token_to_cmd();
 *	- Parameter:
 *		- t_data *all: the main data struct;
 *
 *	- It iterates through the token linked list, 
 *	  and whenever it encounters the first token of a new command,
 *	  it calls handle_single_command() to extract the command 
 *	  and add it to the command linked list.
 *	- After all commands are extracted, the function calls add_redirection() 
 *	  to handle any input/output redirection specified in the tokens.
 */
void	token_to_cmd(t_data *all)
{
	t_token	*curr;
	int		index;

	curr = all->token;
	all->cmd = NULL;
	index = 0;
	while (curr)
	{
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			handle_single_command(&curr, all, index);
			index++;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	all->cmd_len = index;
	add_redirection(all);
}
