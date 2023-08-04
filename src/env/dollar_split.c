/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 10:51:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
