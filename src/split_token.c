/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 12:06:43 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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