/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_dollar_sign.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 10:56:56 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* have_dollar();
 *	- Check if a string contains the dollar sign ($) character.
 *	- Returns 1 if the dollar sign is present in the string, 0 otherwise.
 */
int	have_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

/* dollar_len();
 *	- Calculate the length of the substring until 
 *	  the next dollar sign ($) or whitespace.
 */
int	dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i])
			|| str[i] == '\'' || str[i] == '\"'
			|| str[i] == '|' || str[i] == '<'
			|| str[i] == '>')
			break ;
		i++;
	}
	return (i);
}

/* space_len();
 *	- Calculate the length of leading whitespace in the input string.
 */
int	space_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	non_dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i]) || str[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

/* token_to_str();
 *	- Convert a linked list of tokens into a single string.
 *	- Returns a string representing the concatenated tokens.
 */
char	*token_to_str(t_token **top)
{
	t_token	*curr;
	char	*lang_str;

	if (!*top)
		return (NULL);
	curr = *top;
	lang_str = NULL;
	while (curr != NULL)
	{
		if (curr->str)
		{
			if (!lang_str)
				lang_str = ft_strdup(curr->str);
			else
				lang_str = ft_strjoin(lang_str, curr->str);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (lang_str);
}
