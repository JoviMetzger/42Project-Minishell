/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_dollar_sign.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 14:23:24 by jmetzger      ########   odam.nl         */
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
		if (str[i] == '$' || ft_isspace(str[i]))
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

/* swap_val();
 *	- Parameters:
 *	  - t_token **top: A double pointer to the top node of 
 *		the token linked list;
 *	  - char **envp: The array of strings representing 
 *		the environment variables;
 *	  - t_data *all: A pointer to a data structure containing additional 
 		program information;
 *
 *	- Replace token strings with corresponding values from 
 *	  the environment or special variables.
 *		- For example: "$?" will get the exit_status 
 *		  from 'all->status' with ft_itoa().
 */

void	swap_val(t_token **top, char **envp, t_data *all)
{
	t_token	*curr;

	curr = *top;
	while (curr != NULL)
	{
		if (curr->str)
		{
			if (ft_strcmp(curr->str, "$") == 0)
				curr->str = "$";
			else if (ft_strcmp(curr->str, "$$") == 0)
				curr->str = "id";
			else if (ft_strcmp(curr->str, "$?") == 0)
				curr->str = ft_itoa(all->status);
			else if (curr->str[0] == '$' && curr->str[1] != '$')
				curr->str = find_env(&curr, envp);
		}
		curr = curr->next;
	}
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
