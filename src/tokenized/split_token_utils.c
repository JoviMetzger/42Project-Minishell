/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 16:19:32 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/09 16:22:22 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_spaces_char(char *str, int i, t_token **top)
{
	int		len;
	char	*line;
	t_token	*new;

	len = space_len(&str[i]);
	line = ft_substr(str, i, len);
	new = new_token(line);
	new->type = SPACES;
	add_token_end(top, new);
	i += len;
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
		new->type = DQUO;
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
		new->type = DQUO;
	add_token_end(top, new);
	return (i);
}

int	split_char(char *str, int i, t_token **top, char c)
{
	char	*line;
	t_token	*new;

	line = ft_substr(str, i, 1);
	new = new_token(line);
	if (c == '|')
		new->type = PIPE;
	if (c == '<')
		new->type = INPUT_RE;
	if (c == '>')
		new->type = OUTPUT_RE;
	add_token_end(top, new);
	i += 1;
	return (i);
}
