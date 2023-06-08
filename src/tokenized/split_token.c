/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/08 16:42:34 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*split_token(char *str)
{
	int	i;
	int	start;
	int	len;
	char	*line;
	t_token	*top;
	

	i = 0;
	start = 0;
	len = 0;
	top = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			start = i + 1;
			len = strlen_char(&str[start], '\'');
			line = ft_substr(str, start, len);
			i = len + start + 1;
			//printf("2.%s$, len:%i\n",line,len);
			add_token_end(&top, new_token(line));
		}
		else if (str[i] == '\"')
		{
			start = i + 1;
			len = strlen_char(&str[start], '\"');
			line = ft_substr(str, start, len);
			i = len + start + 1;
			//printf("3%s$\n",line);
			add_token_end(&top, new_token(line));
		}
		else if (str[i] != ' ' && (str[i - 1] == ' '|| i == 0 ) && str[i] != '\'' && str[i] != '\"')
		{
			start = i;
			len = strlen_char(&str[start], ' ');
			line = ft_substr(str, start, len);
			//printf("1.%s$, len:%i\n",line,len);
			add_token_end(&top, new_token(line));
			//i = len + start;
		}
		i++;
	}
	return (top);
}

//test:  gcc split_token.c token_util.c tokenized.c ../../libft/libft.a

int main(void)
{
	t_token *test;
	t_token *curr;

	
	test = split_token("  c\"\'\'\"  c\'\"\"\' b\"cd\" c \"\'\'\" | \'hello world\' ");
	//test = split_token("  chkhk df");
	curr = test;
	while (curr != NULL)
	{
		printf("%s ", curr->str);
		curr = curr->next;
	}printf("\n");
	return 0;
}
