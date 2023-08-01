/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/31 15:07:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_char(char *str, int i, t_token **top)
{
	char	*line;

	line = ft_substr(str, i, 1);
	add_token_end(top, new_token(line));
	i += 1;
	return (i);
}

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

int	split_without_quote(char *str, int i, char c, t_token **top)
{
	int		start;
	int		len;
	char	*line;
	t_token	*new;

	start = i + 1;
	len = strlen_char(&str[start], c);
	if (len == 0)
		return (len + start + 1);
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

int	split_with_quote(char *str, int i, char c, t_token **top)
{
	int		start;
	int		len;
	char	*line;
	t_token	*new;

	start = i;
	len = strlen_char(&str[start + 1], c) + 2;
	if (len == 2)
		return (len + start + 1);
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
