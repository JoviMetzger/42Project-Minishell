/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:04:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 22:37:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* split_no_space();
 *	- Parameters:
 *	- char *str: The input string to split;
 *	- int i: The current index from where the splitting should start;
 *	- t_token **top: the token where the new token should be added;
 *
 *	- The function calculates the length of the substring in 'str' starting from index 'i' until the first space character (' ') is encountered.
 *	- It then creates a new token with the substring and adds it to the end of the token linked list pointed to by 'top'.
 *	- The function updates the index 'i' to point to the position just after the substring and returns this updated value.
 */
int	split_no_space(char *str, int i, t_token **top)
{
	int		len;
	char	*line;

	len = strlen_char(&str[i], ' ');
	line = ft_substr(str, i, len);
	add_token_end(top, new_token(line));
	i = len + i;
	return (i);
}

/* strlen_char();
 * - Calculate the length of a substring until a specific character is encountered.
 * - Parameters:
 *   - char *str: The input string to calculate the length of the substring from.
 *   - char c: The character to search for in the input string.
 * - Returns:
 *   - The length of the substring until the first occurrence of character 'c'.
 *
 * - The function calculates the length of the substring in 'str' starting from index 'i' until the first occurrence of character 'c'.
 * - If 'c' is a single quote ('\'') or double quote ('\"'), it stops counting at the first matching closing quote.
 * - The function is used by 'split_no_space' to calculate the length of the substring until the first space character or other specific characters ('|', '<', '>') are encountered.
 */
int	strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\'' || c == '\"')
	{
		while (str[i] && str[i] != c)
			i++;
		return (i);
	}
	while (str[i] && str[i] != c && !ft_isspace(str[i]) && str[i] != '\''
		&& str[i] != '\"' && str[i] != '|'
		&& str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

/* new_token();
 * - Create a new token node with the provided string and default values for other fields.
 * - Parameters:
 *   - char *str: The string value to be assigned to the 'str' field of the new token.
 * - Returns:
 *   - A pointer to the newly created token node.
 *
 * - The function allocates memory for a new token node and assigns the input string 'str' to its 'str' field.
 * - It sets the 'type' field of the token to 'EMPTY', 'index' to 0, and initializes 'next' and 'prev' pointers to NULL.
 * - The function returns a pointer to the new token node.
 */
t_token	*new_token(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = EMPTY;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/* copy_token();
 * - Create a copy of an existing token node.
 * - Parameters:
 *   - t_token *old: A pointer to the token node to be copied.
 * - Returns:
 *   - A pointer to the newly created token node (a copy of the original token).
 *
 * - The function allocates memory for a new token node and copies the 'str' field from the original token 'old'.
 * - It sets the 'type' field of the new token to the same value as the original token and initializes 'next' and 'prev' pointers to NULL.
 * - The function returns a pointer to the new token node (the copied token).
 */
t_token	*copy_token(t_token *old)
{
	t_token	*new;

	if (!old)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(old->str);
	new->type = old->type;
	new->next = NULL;
	new->prev = NULL;
	new->index = 0;
	return (new);
}

/* add_token_end();
 * - Add a new token node to the end of the token linked list.
 * - Parameters:
 *   - t_token **top: A pointer to the top of the token linked list where the new token should be added.
 *   - t_token *new: A pointer to the new token node to be added.
 *
 * - The function traverses the token linked list starting from the node pointed to by 'top' until it reaches the last node.
 * - It then adds the new token node 'new' as the next node of the last node in the linked list.
 * - The 'prev' pointer of the new node is set to point to the last node, and the 'index' of the new node is set accordingly.
 * - If the token linked list is empty (i.e., 'top' is NULL), the new token node becomes the first node in the linked list, and 'top' is updated to point to it.
 */
void	add_token_end(t_token **top, t_token *new)
{
	t_token	*current;
	int		i;

	i = 1;
	current = *top;
	if (!new)
		return ;
	if (!current)
	{
		*top = new;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
		i++;
	}
	current->next = new;
	new->prev = current;
	new->index = i;
}
