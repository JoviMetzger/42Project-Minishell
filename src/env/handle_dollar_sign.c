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

int	have_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

int	dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i])
			|| str[i] == '\'' || str[i] == '\"'
			|| str[i] == '|'|| str[i] == '<'
			|| str[i] == '>')
			break ;
		i++;
	}
	return (i);
}

int	space_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	non_dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i]) || str[i] == '\'')
			break ;
		i++;
	}
		
	return (i);
}

t_token *dollar_split(char *str)
{
	int	i;
	int one_len;
	char *line;
	t_token	*top;
	
	i = 0;
	top = NULL;
	if (!str)
		return (new_token(NULL));
	while (str[i])
	{
		if (str[i] == '\'')
			i = split_with_quote(str, i, '\'', &top) - 1;
		else if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
			{
				line = ft_substr(str, i, 2);
				add_token_end(&top, new_token(line));
				//printf("2,%s \n", line);
				i += 2;
			}
			else
			{
				one_len = dollar_len(&str[i + 1]) + 1;
				line = ft_substr(str, i, one_len);
				add_token_end(&top, new_token(line));
				//printf("1,%s \n", line);
				i += one_len;
			}
		}
		else if(!ft_isspace(str[i]))
		{
			one_len = non_dollar_len(&str[i]);
			line = ft_substr(str, i, one_len);
			add_token_end(&top, new_token(line));//segv
			//printf("3,%s \n", line);
			i += one_len;
		}
		else if(ft_isspace(str[i]))
		{
			one_len = space_len(&str[i]);
			line = ft_substr(str, i, one_len);
			add_token_end(&top, new_token(line));//segv
			//printf("4,%s \n", line);
			i += one_len;
		}
		else
			i++;
	}
	return (top);
}

void swap_val(t_token **top, char **envp, t_data *all)
{
	t_token	*curr;
		t_token		*to_tmp;
	char	*tmp;

	tmp = NULL;
	to_tmp = NULL;
	curr = *top;
	while(curr != NULL)
	{
		if (curr->str)
		{
			if (ft_strcmp(curr->str, "$") == 0)
				curr->str  = "$";//swap_str(curr->str, "$");//
			else if (ft_strcmp(curr->str, "$$") == 0)
				curr->str  = "id";//swap_str(curr->str, "id");//
			else if (ft_strcmp(curr->str, "$?") == 0)
				curr->str  = ft_itoa(all->status);//swap_str(curr->str, ft_itoa(all->status)); //
			else if (curr->str[0] == '$' && curr->str[1] != '$')
				curr->str  = find_env(&curr, envp);
		}
		curr = curr->next;
	}
}

char *token_to_str(t_token **top)
{
	t_token	*curr;
	char	*lang_str;

	if (!*top)
		return (NULL);
	curr = *top;
	lang_str = NULL;
	while(curr != NULL)
	{
		if (curr->str)
		{
			if (!lang_str)
				lang_str = ft_strdup(curr->str);
			else
				lang_str = ft_strjoin(lang_str, curr->str);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (lang_str);
}

//test:  gcc handle_dollar_sign.c find_env.c ../tool/free_error.c ../tool/protection.c ../tool/tool_utils.c ../tokenized/token_util.c ../tokenized/split_token.c ../../libft/libft.a

/* int main(int argc, char **argv, char **envp)
{
	int a;
	char *str;
	t_token *top = NULL;
	t_token *new;
	t_data all;
	int i;
	i = 0;

	(void)argv;
	(void)argc;
	//str = "hgjgh$dsf$sdfd$?$$$$$PATH";
	//str = "$PATH $dsf $sdf d$?$$$$$";
	str = "$PATH $$<< infile| hgj|gh$dsf$sdfd$?$$$$$";
	str = "echo adsfd\'\'afas\'$PATH\'";
	str = "echo \'$PATH\'xchgfg\"$PATH\"";
	str = "grep <Makefile c|grep e|grep $|wc";
	new = new_token(str);
	top = dollar_split(new->str);//
	t_token *curr;
	curr = top;
	while (curr!= NULL)
	{
		printf("%s\n",curr->str);
		curr = curr->next;
	} 
	swap_val(&top, envp, &all);//
 	printf("\n\n\n");
	curr = top;
	while (curr!= NULL)
	{
		printf("%s\n",curr->str);
		curr = curr->next;
	} 
	char *lang_str;
	lang_str = token_to_str(&top);
	printf("lang :%s\n",lang_str);
} */