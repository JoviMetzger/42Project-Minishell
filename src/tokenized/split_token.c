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

//test :  gcc split_token.c token_util.c tokenized.c ../tool/free_error.c ../tool/protection.c ../tool/tool_utils.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a

/* int main(void)
{
	t_token *test;
	t_token *curr;
	char *str;

	//str = "|||cmd ";
	//str = "  c\"\'\" asdasda\"\'\">&| \"|\" ";
	//str = "&&&cmd "; //break pipe
	//str = "$ adisad $PATH  $$<<c\"\'\'\" <<<<< c\'\"\"\' b\"cd\" c \"\'\'\" | \'hello world>\'>> ";
	str = "$PATH $$<<   	infile <infile cmd arg>outfile| cmd|1 aa a a a >1outfile|";
	//str = "$ adisad  $PATH  a\"\'\'\"a <<<";
	//str = " $ $chkhk$$$ df";
	//str = " $PATH| |ADS asd$ads$ads $chkhk df ";//have segmentation fault
	//str = " cmd arg| cmd";
	//str = " <infile as<infile cmd arg>outfile| cmd1 aa a a a >1outfile|";
	test = split_token(str);
	printf("test:%s\n", str);
	//str = " cmd arg| cmd";
	curr = test;
	while (curr != NULL)
	{
		printf("%s$\n", curr->str);
		curr = curr->next;
	}
	return 0;
} */
