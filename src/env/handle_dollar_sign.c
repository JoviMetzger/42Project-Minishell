/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_dollar_sign.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/13 10:48:10 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*dollar_split(char *str, int quo)
{
	int		i;
	t_token	*top;

	i = 0;
	top = NULL;
	if (!str)
		return (new_token(NULL));
	while (str[i])
	{
		if (str[i] == '\'' && quo == 0)
			i = split_with_quote(str, i, '\'', &top) - 1;
		else if (str[i] == '\"' && quo == 0)
			i = split_with_quote(str, i, '\"', &top) - 1;
		else if (str[i] == '<')
			i = split_redi(str, i, str[i], &top);
		else if (str[i] == '$')
			i = dollar_split_dollar(str, i, &top);
		else if (!ft_isspace(str[i]))
			i = dollar_split_nondollar(str, i, &top, quo);
		else if (ft_isspace(str[i]))
			i = split_spaces_char(str, i, &top);
		else
			i++;
	}
	return (top);
}

void	swap_val(t_token **top, char **envp, t_data *all)
{
	t_token	*curr;
	char	*tmp;

	curr = *top;
	tmp = NULL;
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC)
		{
			if (curr->next && curr->next->type != SPACES)
				curr->next->type = DELIMI;
			else if (curr->next && curr->next->type == SPACES
				&& curr->next->next && curr->next->next->type != SPACES)
				curr->next->next->type = DELIMI;
		}
		if (curr->str && curr->type != DELIMI)
			dollar_swap_val(&curr, envp, all);
		curr = curr->next;
	}
}

char	*token_to_str(t_token **top)
{
	t_token	*curr;
	char	*lang_str;

	if (!*top)
		return (NULL);
	curr = *top;
	lang_str = NULL;
	while (curr != NULL)
	{
		if (curr->str)
			lang_str = add_str_to_strend(lang_str, curr->str);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free_token(*top);
	return (lang_str);
}

//test:  gcc handle_dollar_sign.c find_env.c ../tool/free_error.c ../tool/protection.c ../tool/tool_utils.c ../tokenized/token_util.c ../tokenized/split_token.c ../../libft/libft.a

/* int main(int argc, char **argv, char **envp)
{
	int a;
	char *str;
	t_token *top = NULL;
	t_data all;
	int i;
	i = 0;

	(void)argv;
	(void)argc;
	atexit(leaks);
	//str = "hgjgh$dsf$sdfd$?$$$$$PATH";
	//str = "$PATH $dsf $sdf d$?$$$$$";
	str = "$PATH $$<< infile| hgj|gh$dsf$sdfd$?$$$$$";
	str = "echo adsfd\'\'afas\'$PATH\'";
	str = "echo \'$PATH\'xchgfg\"$PATH\"";
	str = "grep <Makefile c|grep e|grep $|wc";
	//str = "\"$USER\'$USER\'\"";
	//str = "\'$USER\"$USER\"\'";
	//str = "\"$USER\"\"\"\'\'\'$USER\'";
	//str = "ASD$USER";
	str = "ASDASD\'$USER\"$USER\"\'\'\'HASDOASDH\'$USER\'\"$USER\"";
	top = dollar_split(str, DQUO);//
	swap_val(&top, envp, &all);//
 	printf("\n\n\n");
	char *lang_str;
	lang_str = token_to_str(&top);
	printf("lang :%s\n",lang_str);
	free(lang_str);
	return (0);
} */