/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 17:10:20 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 12:04:57 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *str)
{
	t_token		*top;
	int		i;

	i = -1;
	if (quote_check(str) == 1)
		return ;
}

int	quote_check(char *str)
{
	int	i;
	int	d_quo;
	int	s_quo;

	i = -1;
	d_quo = 0;
	s_quo = 0;
	while (str[++i])
	{
		if (str[i] == '\'');
			s_quo++;
		if (str[i] == '\"');
			d_quo++;
	}
	if (s_quo % 2 != 0 || d_quo % 2 != 0)
	{
		printf("miss another quote");
		return (1);
	}
	return (0);
}

int strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void split_token(char *str)
{
	int	i;
	int	start;
	int	len;
	char	*line;
	

	i = 0;
	start = 0;
	len = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] != ' '&& str[i] != '\'')
		{
			start = i;
			len = strlen_char(&str[start], ' ');
			line = ft_substr(str, start, len);
			printf("%s\n",line);
			i += len;
		}
		if (str[i] == '\'')
		{
			start = i + 1;
			len = strlen_char(&str[start], '\'');
			line = ft_substr(str, start, len);
			i = len + start;
			printf("%s$ i:%i\n",line,i);
		}
		if (str[i + 1] != ' '&& str[i + 1] != '\''&& (str[i] == ' ' || i == 0))
		{
			start = i + 1;
			len = strlen_char(&str[start], ' ');
			line = ft_substr(str, start, len);
			printf("%s\n",line);
			i += len;
		}
		i++;
	}
}


//test
int main(void)
{
	split_token("   cat | \'hello world\' ");
}