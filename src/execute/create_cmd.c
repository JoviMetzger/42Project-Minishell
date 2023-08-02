/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/06 17:33:24 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_to_cmd(t_data *all)
{
	t_cmd	*new;
	t_token *curr;
	char	**words;
	int		len;
	int		i;

	curr = all->token;
	all->cmd = NULL;
	while(curr)
	{
		i = 0;
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			len = cmd_len(&curr, curr->index);
			words = malloc(sizeof(char *) * len);
			if (!words)
				print_error(NULL, 0);
			words[len - 1] = NULL;
			while (curr->type != PIPE && curr != NULL && i < len)
			{
				if (curr->type == WORD &&curr->str)
				{
					words[i] = ft_strdup(curr->str);
					i++;
				}
				if (!curr->next)
					break ;
				curr = curr->next;
			}
			new = new_cmd(words, len);
			add_cmd_end(&all->cmd, new);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	add_redirection(all);
}

void	add_redirection(t_data *all)
{
	t_token *curr;
	t_cmd	*cmd;


	if (!all->cmd || !all->token)
		return ;
	curr = all->token;
	cmd = all->cmd;
	cmd->redi = NULL;
	while(cmd != NULL && curr != NULL)
	{
		if (curr->type == INFILE || curr->type == OUTFILE || curr->type == APPFILE || curr->type == DELIMI)
			add_token_end(&cmd->redi, copy_token(curr));
		else if (curr->type == PIPE)
			cmd = cmd->next;
		curr = curr->next;
	}
}

int	cmd_len(t_token **token, int index)
{
	int	i;
	t_token *curr;

	i = 1;
	curr = *token;
	while(curr != NULL)
	{
		if (curr->index == index)
		{
			while (curr->type != PIPE && curr)
			{
				if (curr->type == WORD && curr->str)
					i++;
				if (!curr->next)
					return(i);
				curr = curr->next;
			}
			return(i);
		}
		curr = curr->next;
	}
	return (i);
}

t_cmd	*new_cmd(char **words, int len)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->words = words;
	new->next = NULL;
	new->len = len;
	new->redi = NULL;
	return (new);
}

void	add_cmd_end(t_cmd **top, t_cmd *new)
{
	t_cmd	*curr;

	curr = *top;
	if (!new)
		return ;
	if (!*top)
	{
		*top = new;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}


//complie:gcc create_cmd.c free_error.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../../libft/libft.a

//test1:add_cmd_end && new_cmd
/* int main(int argc, char **argv, char **envp)
{
	t_token *test;
	int	i = 0;
	t_cmd *cmd = NULL;
	
	char **str;
	str = malloc(sizeof(char *) * 3);
	str[0]= "ls";
	str[1]= "adsas";
	str[2]= NULL;
	
	char **str2;
	str2 = malloc(sizeof(char *) * 3);
	str2[0]= "222";
	str2[1]= "ads121as";
	str2[2]= NULL;
	add_cmd_end(&cmd, new_cmd(str,3));
	add_cmd_end(&cmd, new_cmd(str2,3));
	add_cmd_end(&cmd, new_cmd(str,3));
	t_cmd *curr = cmd;
	while (curr != NULL)
	{
		i = 0;
		while (i < 3)
		{
			printf("%i:%s ", i,curr->words[i]);
			i++;
		}
		printf("\n");
		curr = curr->next;
	}
	return 0;
} */

//complie:gcc create_cmd.c free_error.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../../libft/libft.a
//test2:token_to_cmd && cmd_len

/* int main(int argc, char **argv, char **envp)
{
	t_data all;
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	//str = " <infile cmd  <infile arg arg>outfile| cmd1 aa a a a >1outfile|";
	//str = " cmd arg|";
	str = " $PATH ADS $$ $chkhk df ";//have segmentation fault
	//str = "  chkhk ";
	all.input = str;

	tokenized(&all, envp);
	int len = cmd_len(&all.token, 0);
	printf("len : %i \n",len);
	token_to_cmd(&all);
	t_cmd *curr = all.cmd;
	while (curr != NULL)
	{
		int i = 0;
		while (i < len)
		{
			printf("%s\n",curr->words[i]);
			i++;
		}
		curr=curr->next;
	}  
	return 0;
} */

//complie:gcc create_cmd.c free_error.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../../libft/libft.a
//test3:add_redirection

/* int main(int argc, char **argv, char **envp)
{
	t_data all;
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	str = " <infile cmd  <infile arg arg>outfile| cmd1 aa a a a >1outfile|";
	//str = " cmd arg|";
	//str = "  chkhk df ";//have segmentation fault
	//str = "  chkhk ";
	all.input = str;

	tokenized(&all, envp);
	int len = cmd_len(&all.token, 0);
	printf("len : %i \n",len);
	token_to_cmd(&all);
	t_token *curr = all.cmd->redi;
	printf("%s ",curr->str);
	int i =0;
	while (curr != NULL)
	{
		i++;
		printf("%s ",curr->str);
		curr=curr->next;
	} 
	return 0;
} */