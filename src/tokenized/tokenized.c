/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/06 17:07:31 by yizhang       ########   odam.nl         */
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
	if (!str)
		return (0);
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
		exit (1);
	}
	return (0);
}

int quote_count(char *str, int i,int *quo_nb, char quo)
{
	*quo_nb += 1;
	i++;
	while(str[i])
	{
		if (str[i] == quo)
		{
			*quo_nb += 1;
			break ;
		}
		i++;
	}
	return (i);
}

void	tokenized(t_data *all, char **envp)
{
	t_token		*curr;
	char	*tmp;

	tmp = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	all->token = split_token(all->input);
	curr = all->token;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->str, "|") == 0 && curr->type == EMPTY)
			curr->type = PIPE;
		else if (ft_strcmp(curr->str, "<") == 0 && curr->type == EMPTY)
			curr->type = INPUT_RE;
		else if (ft_strcmp(curr->str, ">") == 0 && curr->type == EMPTY)
			curr->type = OUTPUT_RE;
		else if (ft_strcmp(curr->str, "<<") == 0 && curr->type == EMPTY)
			curr->type = HERE_DOC;
		else if (ft_strcmp(curr->str, ">>") == 0 && curr->type == EMPTY)
			curr->type = APPEND_RE;
		else if (curr->str[0] == '$' && curr->type == EMPTY)
		{
			tmp = find_env(&curr, envp);
			if (tmp)
				curr->str = ft_strdup(tmp);
			else
				curr->str = NULL;
			curr->type = WORD;
		}
		else if (curr->prev && curr->prev->type == INPUT_RE && curr->type == EMPTY)
			curr->type = INFILE;
		else if (curr->prev && curr->prev->type == OUTPUT_RE && curr->type == EMPTY)
			curr->type = OUTFILE;
		else if (curr->prev && curr->prev->type == APPEND_RE && curr->type == EMPTY)
			curr->type = APPFILE;
		else if (curr->prev && curr->prev->type == HERE_DOC && curr->type == EMPTY)
			curr->type = DELIMI;
		else if (curr->type == EMPTY)
			curr->type = WORD;
		if (!curr->next)
			return ;
		curr = curr->next;
	}
}

//test:gcc split_token.c token_util.c tokenized.c ../env/find_env.c ../../libft/libft.a

/* int main(int argc, char **argv,char **envp)
{
	t_token *curr;
	t_data	all;
	char *str;

	all.cmd =NULL;
	all.history =NULL;
	(void)argc;
	(void)argv;
	//all.input = "  c\"\'\" asdasda\"\'\">&| \"|\" ";
	//all.input = " cmd arg| cmd";
	//all.input = "  chkhk df";
	//all.input = "  chkhk df >outfile <infile";
	//all.input = " cmd <file  >outfile | \"|\"<infile";
	//all.input = "cat <file1 cat > out | <ls| <file cmd"; //break pipe
	//all.input = " $PATH $$<< infile <infile cmd arg>outfile| cmd1 aa a a a >1outfile|";//$$ error
	all.input = " $PATH ADS  $sdf $ df ";
	//all.input = " $PATH ";
	//all.input = "||\"|\"cmd "; //break pipe
	//all.input = " \"echo\" hello ";
	//all.input = " \"echo\" hello | wc";
	//all.input = "<file1 cat > out \"|\" <infile "; //works 
	//all.input = " <infile cmd >outfile | <infile";
	tokenized(&all, envp);
	curr = all.token;
	printf("test:%s\n", all.input);
	 while (curr != NULL)
	{
		printf(" %i: type :%i :%s\n", curr->index, curr->type , curr->str);
		curr = curr->next;
	} 
	return 0;
} */

