/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/27 14:49:37 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	quote_check(char *str)
{
	int	i;
	int	d_quo;
	int	s_quo;
	int	start;
	int	len;

	i = 0;
	d_quo = 0;
	s_quo = 0;
	len =0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = quote_count(str, i, &s_quo, '\'');
		if (str[i] == '\"')
			i = quote_count(str, i, &d_quo, '\"');
		i++;
	}
	if (s_quo % 2 != 0 || d_quo % 2 != 0)
	{
		printf("unclosed quote error \n");
		return (1);
	}
	return (0);
}

int quote_count(char *str, int i,int *quo_nb, char quo)
{
	quo_nb++;
	i++;
	while(str[i])
	{
		if (str[i] == quo)
		{
			quo_nb++;;
			break ;
		}
		i++;
	}
	return (i);
}

void	tokenized(t_data *all)
{
	t_token		*curr;
	int		i;

	i = -1;
	if (quote_check(all->input) == 1)
		return ;
	all->token = split_token(all->input);
	curr = all->token;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->str, "|") == 0)
			curr->type = PIPE;
		else if (ft_strcmp(curr->str, "&") == 0)
			curr->type = AT;
		else if (ft_strcmp(curr->str, "<") == 0)
			curr->type = INPUT_REDIRECTION;
		else if (ft_strcmp(curr->str, ">") == 0)
			curr->type = OUTPUT_REDIRECTION;
		else if (ft_strcmp(curr->str, "<<") == 0)
			curr->type = HERE_DOCUMENT;
		else if (ft_strcmp(curr->str, ">>") == 0)
			curr->type = APPEND_REDIRECTION;
		else if ((curr->prev == NULL || curr->prev->type == PIPE) && curr->type == EMPTY)
			curr->type = CMD;
		else if ((curr->prev->type == CMD || curr->prev->type == ARG) && curr->type == EMPTY)
			curr->type = ARG;
		else if (curr->prev->type == INPUT_REDIRECTION && curr->type == EMPTY)
			curr->type = INFILE;
		else if (curr->prev->type == OUTPUT_REDIRECTION && curr->type == EMPTY)
			curr->type = OUTFILE;
		curr = curr->next;
	}
}

//test:gcc split_token.c token_util.c tokenized.c ../../libft/libft.a

/* int main(void)
{
	t_token *test;
	t_token *curr;
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" ";
	//str = " cmd arg| cmd";
	//str = "  chkhk df";
	str = "  chkhk df >outfile <infile";
	
	test = tokenized(str);
	curr = test;
	printf("test:%s\n", str);
	while (curr != NULL)
	{
		printf("%i:%s\n", curr->type, curr->str);
		curr = curr->next;
	}//printf("\n");
	return 0;
} */