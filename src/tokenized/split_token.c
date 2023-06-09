/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:06:38 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 11:57:39 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*split_token(char *str)
{
	int	i;
	int	start;
	int	len;
	char	*line;
	t_token	*new;
	t_token	*top;
	

	i = 0;
	start = 0;
	len = 0;
	top = NULL;
	if (!str)
		return (NULL);
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
			//printf("2.%s, len:%i\n",line,len);
			new = new_token(line);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (str[i] == '\"')
		{
			start = i + 1;
			len = strlen_char(&str[start], '\"');
			line = ft_substr(str, start, len);
			i = len + start + 1;
			//printf("3.%s, len:%i\n",line,len);
			new = new_token(line);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				line = ft_substr(str, i, 2);
				//printf("5.%s, len:%i\n",line,1);
				add_token_end(&top, new_token(line));
				i+=2;
			}
			else
			{
				line = ft_substr(str, i, 1);
				//printf("4.%s, len:%i\n",line,1);
				add_token_end(&top, new_token(line));
				i += 1;
			}
		}
		else if (str[i] == '|')
		{
			line = ft_substr(str, i, 1);
			//printf("4.%s, len:%i\n",line,1);
			add_token_end(&top, new_token(line));
			i += 1;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				line = ft_substr(str, i, 2);
				//printf("5.%s, len:%i\n",line,1);
				add_token_end(&top, new_token(line));
				i+=2;
			}
			else
			{
				line = ft_substr(str, i, 1);
				//printf("4.%s, len:%i\n",line,1);
				add_token_end(&top, new_token(line));
				i += 1;
			}
		}
		else if (str[i] != ' ' && str[i] != '\"' && str[i] != '\''&& str[i] != '|')
		{
			len = strlen_char(&str[i], ' ');
			line = ft_substr(str, i, len);
			//printf("1.%s, len:%i\n",line,len);
			add_token_end(&top, new_token(line));
			i = len + i;
		}
		else
			i++;
	}
	return (top);
}

//test :  gcc split_token.c token_util.c  ../../libft/libft.a

/* int main(void)
{
	t_token *test;
	t_token *curr;
	char *str;

	//str = "|||cmd ";
	//str = "  c\"\'\" asdasda\"\'\">&| \"|\" ";
	//str = "&&&cmd "; //break pipe
	//str = "$ adisad $PATH  $$<<c\"\'\'\" <<<<< c\'\"\"\' b\"cd\" c \"\'\'\" | \'hello world>\'>> ";
	str = "$PATH $$<< infile <infile cmd arg>outfile| cmd1 aa a a a >1outfile|";
	//str = "$ adisad  $PATH  a\"\'\'\"a <<<";
	//str = " $ $chkhk$$$ df";
	str = " $PATH ADS asd$ads$ads $chkhk df ";//have segmentation fault
	//str = " cmd arg| cmd";
	//str = " <infile as<infile cmd arg>outfile| cmd1 aa a a a >1outfile|";
	test = split_token(str);
	printf("test:%s\n", str);
	//str = " cmd arg| cmd";
	curr = test;
	while (curr != NULL)
	{
		printf("%s\n", curr->str);
		curr = curr->next;
	}
	return 0;
} */