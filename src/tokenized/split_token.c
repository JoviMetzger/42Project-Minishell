/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/19 11:22:48 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	escape_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

t_token	*split_token(char *str)
{
	int		i;
	t_token	*top;

	top = NULL;
	if (!str)
		return (NULL);
	i = escape_space(str);
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
			i = split_spaces_char(str, i, &top);
	}
	return (top);
}

int	split_general_char(char *str, int i, t_token **top)
{
	int		len;
	char	*line;
	t_token	*new;

	len = strlen_char(&str[i], ' ');
	line = ft_substr(str, i, len);
	new = new_token(line);
	new->type = WORD;
	add_token_end(top, new);
	i = len + i;
	return (i);
}

int	split_redi(char *str, int i, char c, t_token **top)
{
	char	*line;
	t_token	*new;

	if (str[i + 1] == c)
	{
		line = ft_substr(str, i, 2);
		new = new_token(line);
		if (c == '<')
			new->type = HERE_DOC;
		if (c == '>')
			new->type = APPEND_RE;
		add_token_end(top, new);
		i += 2;
	}
	else
		i = split_char(str, i, top, c);
	return (i);
}
