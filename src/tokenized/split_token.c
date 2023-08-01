/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/01 22:21:43 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*split_again_token(char *str)
{
	int		i;
	t_token	*top;

	i = 0;
	top = NULL;
	if (!str)
		return (NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_without_quote(str, i, '\'', &top);
		else if (str[i] == '\"')
			i = split_without_quote(str, i, '\"', &top);
		else if (str[i] == '<' || str[i] == '>')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '|')
			i = split_char(str, i, &top);
		else if (!ft_isspace(str[i]) && str[i] != '|')
			i = split_general_char(str, i, &top);
		else
			i++;
	}
	return (top);
}

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
			i = split_char(str, i, &top);
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
