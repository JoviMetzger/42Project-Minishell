/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/19 11:26:03 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	quote_check(char *str)
{
	int	i;
	int	d_quo;
	int	s_quo;

	i = 0;
	d_quo = 0;
	s_quo = 0;
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

t_token	*delspace_jointoken(t_token ** token)
{
	t_token	*curr;
	t_token	*top;
	t_token	*new;
	char	*words;

	curr = *token;
	top = NULL;
	words = NULL;
	while(curr)
	{
		if (curr && (curr->type == WORD || curr->type == SQUO))
		{
			words = NULL;
			while (curr && (curr->type == WORD || curr->type == SQUO))
			{
				if (!words)
					words = ft_strdup(curr->str);
				else
					words = ft_strjoin(words, curr->str);
				if (!curr->next || (curr->next && (curr->next->type == SPACES
					|| curr->next->type == PIPE || curr->next->type == INPUT_RE
					|| curr->next->type == OUTPUT_RE || curr->next->type == HERE_DOC
					|| curr->next->type == APPEND_RE)))
					break ;
				curr = curr->next;
			}
			new = new_token(words);
			new->type = WORD;
			add_token_end(&top, new);
		}
		else if (curr && curr->type != SPACES)
		{
			new = copy_token(curr);
			add_token_end(&top, new);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	//free_token(curr);
	return (top);
}

void	tokenized(t_data *all, char **envp)
{
	t_token		*curr;
	t_token		*to_tmp;

	curr = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	to_tmp = NULL;
	to_tmp = dollar_split(all->input);
	swap_val(&to_tmp, envp, all);
	all->input = token_to_str(&to_tmp);
	to_tmp = split_token(all->input);
	all->token = delspace_jointoken(&to_tmp);
	curr = all->token;
	while (curr != NULL)
	{
		if (curr->str && curr->prev && curr->prev->type == INPUT_RE && curr->type == WORD)
			curr->type = INFILE;
		else if (curr->str && curr->prev && curr->prev->type == OUTPUT_RE && curr->type == WORD)
			curr->type = OUTFILE;
		else if (curr->str && curr->prev && curr->prev->type == APPEND_RE && curr->type == WORD)
			curr->type = APPFILE;
		else if (curr->str && curr->prev && curr->prev->type == HERE_DOC && curr->type == WORD)
			curr->type = DELIMI;
		else if (curr->str && (curr->type == EMPTY || curr->type == SQUO))
			curr->type = WORD;
		if (!curr->next)
			return ;
		curr = curr->next;
	}
	//syntax_error_check
}

//test:gcc split_token.c token_util.c tokenized.c ../tool/free_error.c ../tool/protection.c ../tool/tool_utils.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a

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
	all.input = " \'$PATH\' $$<< in|fi\'\'le   	  hgjgh$dsf$sdfd$?$$$$$ <infile cmd arg>outfile | cmd1 aa a a a >1outfile|";//$$ error
	//all.input = " $PATH ADS  $sdf $ df hgjgh$dsf$sdfd$?$$$$$";
	all.input = " $PATH ";
	//all.input = "ls|wc";
	//all.input = "||\"|\"cmd "; //break pipe
	//all.input = " echo adfds''fdas\'$PATH\'SDGF";
	//all.input = " \"echo\" hello | wc";
	//all.input = "<file1 cat > out \"|\" <infile "; //works 
	all.input = " <infile>cmd >outfile | <infile";
	tokenized(&all, envp);
	curr = all.token;
	printf("test:%s\n", all.input);
	 while (curr != NULL)
	{
		printf(" %i: type :%i :%s$\n", curr->index, curr->type , curr->str);
		curr = curr->next;
	} 
	return 0;
} */
