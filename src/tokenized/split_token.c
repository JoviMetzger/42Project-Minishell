/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 21:47:01 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_handle_space();
 *	- Parameters:
 *		- char *str: The input string to process;
 *		- int i: The current index from where to handle spaces;
 *		- t_token **top: the token where the new token should be added.
 *
 *	- The function calculates the length of the space substring starting 
 *	  from index 'i' in the input string 'str'.
 *	- It then creates a new token and adds it to the end of the token list 
 *	  pointed to by 'top'.
 *	- The function updates the index 'i' to point to the position just after 
 *	  the space substring and returns this updated value.
 */
static int	ft_handle_space(char *str, int i, t_token **top)
{
	int		len;
	char	*line;
	t_token	*new;

	len = space_len(&str[i]);
	line = ft_substr(str, i, len);
	new = new_token(line);
	new->type = SPACES;
	add_token_end(top, new);
	i = len + i;
	return (i);
}

/* ft_split_again_token_loop();
 *	- Parameters:
 *		- char *str: The input string to split into tokens;
 *		- int i: The current index where to start splitting;
 *		- t_token *top: the token where the new tokens should be added;
 *
 *	- The function loops through the input string starting from index 'i' 
 *	  and uses other functions to split the string into tokens.
 *	- It handles single quotes ('\''), double quotes ('\"'), 
 *	  redirection symbols ('<', '>', '>>', '<<'), pipes ('|'), 
 *	  spaces, and general characters to create tokens.
 *	- The new tokens are added to the end of the token linked list 'top'.
 */
t_token	*ft_split_again_token_loop(char *str, int i, t_token *top)
{
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_without_quote(str, i, '\'', &top);
		else if (str[i] == '\"')
			i = split_without_quote(str, i, '\"', &top);
		else if (str[i] == '<' || str[i] == '>')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '|')
			i = split_char(str, i, &top, '|');
		else if (!ft_isspace(str[i]) && str[i] != '\"' 
			&& str[i] != '\'' && str[i] != '|')
			i = split_general_char(str, i, &top);
		else
			i++;
	}
	return (top);
}

/* split_again_token();
 *	- Parameters:
 *		- char *str: The input string to split into tokens;
 *
 *	- The function skips leading spaces in the input string 'str' 
 *	  and then calls ft_split_again_token_loop() 
 *	  to split the rest of the string into tokens.
 *	- The resulting tokens are returned as a linked list.
 */
t_token	*split_again_token(char *str)
{
	int		i;
	t_token	*top;
	t_token	*re;

	i = 0;
	top = NULL;
	if (!str)
		return (NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	re = ft_split_again_token_loop(str, i, top);
	return (re);
}

/* ft_split_token_loop();
 * 	- Parameters:
 *		- char *str: the input string to process;
 *		- int i: the index in the string where the iteration starts;
 *		- t_token *top: the token where new tokens will be added;
 *
 *	- The function iterates through the input string 'str'.
 *	- For each character, it checks if it is one of the following:
 *		- Single quote (')
 *		- Double quote (")
 *		- Input or output redirection symbol (< or >)
 *		- Pipe symbol (|)
 *		- Non-space character that is not part of a quoted section or pipe
 *		- Whitespace character
 *	- Depending on the character type, the function calls specific 
 *	  helper functions to handle the respective cases and
 *	  split the string into tokens.
 */
t_token	*ft_split_token_loop(char *str, int i, t_token *top)
{
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_without_quote(str, i, '\'', &top);
		else if (str[i] == '\"')
			i = split_without_quote(str, i, '\"', &top);
		else if (str[i] == '<' || str[i] == '>')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '|')
			i = split_char(str, i, &top, '|');
		else if (!ft_isspace(str[i]) && str[i] != '\"' 
			&& str[i] != '\'' && str[i] != '|')
			i = split_general_char(str, i, &top);
		else if (ft_isspace(str[i]))
			i = ft_handle_space(str, i, &top);
		else
			i++;
	}
	return (top);
}

/* split_token();
 *	- Parameters:
 *		- char *str: The input string to split into tokens;
 *
 *	- The function skips leading spaces in the input string 'str' 
 *	  and ft_split_token_loop() to split the rest of the string into tokens.
 *	- The resulting tokens are returned as a linked list.
 */
t_token	*split_token(char *str)
{
	int		i;
	t_token	*new;
	t_token	*top;
	t_token	*re;

	i = 0;
	new = NULL;
	top = NULL;
	if (!str)
		return (NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	re = ft_split_token_loop(str, i, top);
	return (re);
}
