/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 21:54:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* split_char();
 *	- Parameters:
 *		- char *str: The input string;
 *		- int i: The current index in the input string;
 *		- t_token **top: The token linked list's head;
 *
 *	- Split a single character from the input string and 
 *	  add it as a new token to the linked list.
 *	- The function extracts a single character from 
 *	  the input string starting at index i using ft_substr().
 *	- It creates a new token and 
 *	  adds it to the end of the token linked list using add_token_end().
 */
int	split_char(char *str, int i, t_token **top)
{
	char	*line;

	line = ft_substr(str, i, 1);
	add_token_end(top, new_token(line));
	i += 1;
	return (i);
}

/* split_redi();
 *	- Parameters:
 *		- char *str: The input string;
 *		- int i: The current index in the input string;
 *		- char c: The redirection symbol to split;
 *		- t_token **top: The token linked list's head;
 *
 *	- Split a redirection symbol from the input string and 
 *	  add it as a new token to the linked list.
 *	- The function checks if the next character in the input string (i + 1)
 *	  matches the redirection symbol (c).
 *	- If it does, the function ft_substr() the two-character redirection symbol.
 *	- It creates a new token and 
 *	  adds it to the end of the token linked list with add_token_end().
 *	- If the next character does not match the redirection symbol, 
 *	  the function treats the current character as a regular character and 
 *	  calls split_char() to add it to the token linked list.
 */
int	split_redi(char *str, int i, char c, t_token **top)
{
	char	*line;

	if (str[i + 1] == c)
	{
		line = ft_substr(str, i, 2);
		add_token_end(top, new_token(line));
		i += 2;
	}
	else
		i = split_char(str, i, top);
	return (i);
}

/* split_general_char();
 * 	- Parameters:
 *		- char *str: The input string;
 *		- int i: The current index in the input string;
 *		- t_token **top: The token linked list's head;
 *
 *	- Split a general word (sequence of characters without quotes or spaces)
 *	  and add it as a new token to the linked list.
 *	- We ft_substr() until the next space character is encountered 
 *	  using strlen_char() and store it in 'line'.
 *	- It creates a new token and 
 *	  adds it to the end of the token linked with add_token_end().
 *	- The function updates the index (i + len) to skip 
 *	  the extracted sequence and continues the input string.
 */
int	split_general_char(char *str, int i, t_token **top)
{
	int		len;
	char	*line;

	len = strlen_char(&str[i], ' ');
	line = ft_substr(str, i, len);
	add_token_end(top, new_token(line));
	i = len + i;
	return (i);
}

/* split_without_quote();
 *	- Parameters:
 *		- char *str: The input string;
 *		- int i: The current index in the input string;
 *		- char c: The quote character to look for;
 *		- t_token **top: the token linked list's head;
 *
 *	- Split a word without quotes from the input string 
 *	  and add it as a new token to the linked list.
 *	- First, we store the current position i in 'start'.
 *	- Calculate the length of the substring with strlen_char()
 *	  (until the next occurrence of the delimiter 'c').
 *	- If len is 0, it means there's nothing to extract, 
 *	  so 'line' will be set to NULL.
 *	- Otherwise, we ft_substr() and store it in 'line'.
 *	- Move the pointer to the next position.
 *	- If 'c' is a single quote ('), set the type to SQUO.
 *	- Otherwise, set the type to WORD.
 *	- Add the new token to the end of the linked list pointed by 'top'.  
 */
int	split_without_quote(char *str, int i, char c, t_token **top)
{
	int		start;
	int		len;
	char	*line;
	t_token	*new;

	start = i + 1;
	len = strlen_char(&str[start], c);
	if (len == 0)
		line = NULL;
	else
		line = ft_substr(str, start, len);
	i = len + start + 1;
	new = new_token(line);
	if (c == '\'')
		new->type = SQUO;
	else
		new->type = WORD;
	add_token_end(top, new);
	return (i);
}

/* split_with_quote();
 *	- Parameters:
 *		- char *str: The input string;
 *		- int i: The current index in the input string;
 *		- char c: The quote character enclosing the word;
 *		- t_token **top: the token linked list's head;
 *
 *	- First, we store the current position i in 'start'.
 *	- Calculate the length of the substring with strlen_char()
 *	  (including the opening and closing quote characters).
 *	- If len is 0, it means there's nothing to extract, 
 *	  so 'line' will be set to NULL.
 *	- Otherwise, we ft_substr() and store it in 'line'.
 *	- Move the pointer to the next position.
 *	- Add the new token to the end of the linked list pointed by 'top'.
 */
int	split_with_quote(char *str, int i, char c, t_token **top)
{
	int		start;
	int		len;
	char	*line;
	t_token	*new;

	start = i;
	len = strlen_char(&str[start + 1], c) + 2;
	if (len == 0)
		line = NULL;
	else
		line = ft_substr(str, start, len);
	i = len + start + 1;
	new = new_token(line);
	add_token_end(top, new);
	return (i);
}
