/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/09 15:45:45 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* handle_dollar_variable();
 *	- Parameters:
 *		- char *str: the input string to process;
 *		- int i: the index in the string where the dollar variable starts;
 *		- t_token **top: the token where new tokens will be added;
 *
 *	- If the character following the dollar sign is also a dollar sign, 
 *	  it creates a token for "$$".
 *	- Otherwise, it calculates the length of the dollar variable 
 *	  and creates a token for the entire variable.
 */
static int	handle_dollar_variable(char *str, int i, t_token **top)
{
	int		one_len;
	char	*line;

	if (str[i + 1] && str[i + 1] == '$')
	{
		line = ft_substr(str, i, 2);
		add_token_end(top, new_token(line));
		i += 2;
	}
	else
	{
		one_len = dollar_len(&str[i + 1]) + 1;
		line = ft_substr(str, i, one_len);
		add_token_end(top, new_token(line));
		i += one_len;
	}
	return (i);
}

/* handle_non_dollar_variable();
 *	- Pparameters:
 *		- char *str: the input string to process;
 *		- int i: the index in the string where the non-dollar variable starts;
 *		- t_token **top: the token where new tokens will be added;
 *
 *	- It calculates the length of the non-dollar variable 
 *	  and creates a token for that portion of the string.
 */
static int	handle_non_dollar_variable(char *str, int i, t_token **top)
{
	int		one_len;
	char	*line;

	one_len = non_dollar_len(&str[i]);
	line = ft_substr(str, i, one_len);
	add_token_end(top, new_token(line));
	i += one_len;
	return (i);
}

/* handle_whitespace();
 *	- Parameters:
 *		- char *str: the input string to process;
 *		- int i: the index in the string where the whitespace starts;
 *		- t_token **top: the token where new tokens will be added;
 *
 *	- It calculates the length of the whitespace 
 *	  and creates a token for that portion of the string.
 */
static int	handle_whitespace(char *str, int i, t_token **top)
{
	int		one_len;
	char	*line;

	one_len = space_len(&str[i]);
	line = ft_substr(str, i, one_len);
	add_token_end(top, new_token(line));
	i += one_len;
	return (i);
}

/* dollar_split();
 *	- Parameter:
 *		- char *str: the input string to split;
 *
 *	- The function iterates through the 'str' character by character and calls 
 *	  the appropriate handler functions based on the current character.
 *	- The function returns a linked list of tokens, 
 *	  representing the split portions of the input 'str'.
 *	- If 'str' is NULL, it returns a single empty token.
 */
t_token	*dollar_split(char *str)
{
	int		i;
	t_token	*top;

	i = 0;
	top = NULL;
	if (!str)
		return (new_token(NULL));
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_with_quote(str, i, '\'', &top) - 1;
		else if (str[i] == '$')
			i = handle_dollar_variable(str, i, &top);
		else if (!ft_isspace(str[i]))
			i = handle_non_dollar_variable(str, i, &top);
		else if (ft_isspace(str[i]))
			i = handle_whitespace(str, i, &top);
		else
			i++;
	}
	return (top);
}
