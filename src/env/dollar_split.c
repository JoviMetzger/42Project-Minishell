/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 14:06:24 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_handle_double_dollar();
 *  - Parameters:
 *    - char *str: The input string being processed;
 *    - int *i: A pointer to the current position in the input string;
 *    - t_token **top: token struct;
 * 
 *  - Handle the case when encountering a double dollar sign ($$) 
 * 	  in the input string.
 *  - This function extracts (ft_substr()) the double dollar sign 
 * 	  from the input string, creates a new token with the extracted substring,
 * 	  and adds it to the token linked list.
 * 	- Note: we passing a int *i, so the 'original' i can continue in 
 * 			dollar_split() without affecting the original variable.
 * 			But variable i in ft_handle_double_dollar() must be 
 * 			at the same position, so we use the pointer to i.
 */
static void	ft_handle_double_dollar(char *str, int *i, t_token **top)
{
	char	*line;

	line = ft_substr(str, *i, 2);
	add_token_end(top, new_token(line));
	*i += 2;
}

/* ft_handle_single_dollar();
 *  - Parameters:
 *    - char *str: The input string being processed;
 *    - int *i: A pointer to the current position in the input string;
 *    - t_token **top: token struct;
 * 
 *  - Handle the case when encountering a single dollar sign ($) 
 * 	  in the input string.
 *  - This function extracts the substring starting from 
 * 	  the single dollar sign until the end of the variable name 
 * 	  from the input string.
 *    It creates a new token with the extracted substring and adds 
 * 	  it to the token linked list.
 *	- Note: we passing a int *i, so the 'original' i can continue 
 *			in dollar_split() without affecting the original variable.
 * 			But, i in ft_handle_single_dollar() must be at the same position, 
 *			so we use the pointer to i.
 */
static void	ft_handle_single_dollar(char *str, int *i, t_token **top)
{
	int		one_len;
	char	*line;

	one_len = dollar_len(&str[*i + 1]) + 1;
	line = ft_substr(str, *i, one_len);
	add_token_end(top, new_token(line));
	*i += one_len;
}

/* ft_handle_substring_or_space();
 *  - Parameters:
 *    - char *str: The input string being processed;
 *    - int *i: A pointer to the current position in the input string;
 *    - t_token **top: token struct;
 *    - int (*given_func)(char *): A function pointer to 
 * 		the 'dollar_len' or 'space_len' function;
 * 
 *  - Handle the case when encountering a substring or space 
 * 	  in the input string.
 *  - This function extracts the substring based on the length calculated 
 * 	  by 'given_func' starting from the current position in the input string.
 *    It creates a new token with the extracted substring and adds it to 
 * 	  the token linked list.
 *	- Note: we passing a int *i, so the 'original' i can continue in 
 *			dollar_split() without affecting the original variable.
 * 			But variable i in ft_handle_substring_or_space() must be 
 *			at the same position, so we use the pointer to i.
 */
static void	ft_handle_substring_or_space(char *str, int *i, t_token **top, \
		int (*given_func)(char *))
{
	int		one_len;
	char	*line;

	one_len = given_func(&str[*i]);
	line = ft_substr(str, *i, one_len);
	add_token_end(top, new_token(line));
	*i += one_len;
}

/* dollar_split();
 *  - Split the input string into tokens based on specific criteria 
 *	  ($$, $, substring, or space).
 *  - This function iterates through the input string and 
 * 	  uses helper functions to handle each case 
 * 	  (double dollar sign, single dollar sign, substring, or space).
 *    It creates tokens for each encountered substring and 
 * 	  builds a linked list of tokens.
 *    The resulting linked list is returned as the function output.
 *  - Returns a pointer to the top node of the resulting token linked list.
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
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
				ft_handle_double_dollar(str, &i, &top);
			else
				ft_handle_single_dollar(str, &i, &top);
		}
		else if (!ft_isspace(str[i]))
			ft_handle_substring_or_space(str, &i, &top, &dollar_len);
		else if (ft_isspace(str[i]))
			ft_handle_substring_or_space(str, &i, &top, &space_len);
	}
	return (top);
}
