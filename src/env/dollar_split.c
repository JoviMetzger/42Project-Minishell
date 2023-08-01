/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/01 21:39:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_handle_double_dollar(char *str, int *i, t_token **top)
{
	char	*line;

	line = ft_substr(str, *i, 2);
	add_token_end(top, new_token(line));
	*i += 2;
}

static void	ft_handle_single_dollar(char *str, int *i, t_token **top)
{
	int		one_len;
	char	*line;

	one_len = dollar_len(&str[*i + 1]) + 1;
	line = ft_substr(str, *i, one_len);
	add_token_end(top, new_token(line));
	*i += one_len;
}

static void	ft_handle_substring_or_space(char *str, int *i, t_token **top, \
		int (*len_func)(char *))
{
	int		one_len;
	char	*line;

	one_len = len_func(&str[*i]);
	line = ft_substr(str, *i, one_len);
	add_token_end(top, new_token(line));
	*i += one_len;
}

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
		{
			if (str[i + 1] && str[i + 1] == '$')
				ft_handle_double_dollar(str, &i, &top);
			else
				ft_handle_single_dollar(str, &i, &top);
		}
		else if (!ft_isspace(str[i]))
			ft_handle_substring_or_space(str, &i, &top, &non_dollar_len);
		else if (ft_isspace(str[i]))
			ft_handle_substring_or_space(str, &i, &top, &space_len);
	}
	return (top);
}
