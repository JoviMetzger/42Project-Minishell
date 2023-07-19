/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removing_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 11:48:38 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/18 13:24:10 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++; 
	}
	return (str);
}

char *ft_quotes(char *str, char c)
{
    int i = 0;
    char *ret;

    while (str[i])
    {
		if (str[i] == c && str[i - 1] == ' ' && str[i - 1] == '=')
			return (str);
		else if (str[i] == c && str[i - 1] != ' ' && str[i - 1] != '=' && str[i + 1] != '\0')
		{
            ret = remove_quotes(str, c);
			return (ret);
        }
        i++;
    }
    return (str);
}

char *ft_converter(char *input) 
{ 
    int	i;
	int	d_quo;
	int	s_quo;
    char *str;

	i = 0;
	d_quo = 0;
	s_quo = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '\'')
			s_quo++;
		if (input[i] == '\"')
			d_quo++;
		i++;
	}
	if (s_quo % 2 == 0)
        str = ft_quotes(input, '\'');
    if (d_quo % 2 == 0)
	    str = ft_quotes(input, '\"');
    //printf("T: %s\n", str);
    return (str);
}