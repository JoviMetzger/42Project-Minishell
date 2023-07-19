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
	if (!str)
		return (NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_quote(str, i, '\'', &top);
		else if (str[i] == '\"')
			i = split_quote(str, i, '\"', &top);
		else if (str[i] == '<' || str[i] == '>')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '|')
			i = split_char(str, i, &top);
		else if (!ft_isspace(str[i]) && str[i] != '\"' && str[i] != '\''&& str[i] != '|')
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

int	split_quote(char *str, int	i, char c, t_token **top)
{
	int		start;
	int		len;
	char	*line;
	t_token	*new;

	start = i + 1;
	len = strlen_char(&str[start], c);
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

int	split_char(char *str, int i, t_token **top)
{
	char	*line;

	line = ft_substr(str, i, 1);
	add_token_end(top, new_token(line));
	i += 1;
	return (i);
}

int	split_redi(char *str, int	i, char c, t_token **top)
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

//test :  gcc split_token.c token_util.c ../tool/tool_utils.c ../../libft/libft.a

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
	str = " $PATH| |ADS asd$ads$ads $chkhk df ";//have segmentation fault
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
