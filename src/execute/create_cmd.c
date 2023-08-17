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
	int		index;

	curr = all->token;
	all->cmd = NULL;
	index = 0;
	while(curr)
	{
		i = 0;
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			len = cmd_len(&curr, curr->index);
			words = malloc(sizeof(char *) * len);
			if (!words)
				print_error(NULL, 0, all);
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
			new->index = index;
			add_cmd_end(&all->cmd, new);
			index++;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	all->cmd_len = index;
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
	new->next = NULL;
	new->redi = NULL;
	new->words = words;
	new->len = len;
	new->fd_in = 0;
	new->fd_out = 0;
	new->index = 0;
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

//complie:gcc create_cmd.c ../tool/free_error.c ../tool/tool_utils.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a
//test2:token_to_cmd && cmd_len

/* int main(int argc, char **argv, char **envp)
{
	t_data all;
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	//str = " <infile cmd  <infile arg arg>outfile| cmd1 aa a a a >1outfile|";
	str = " cmd arg|sd|ad| <asd";//ad don't have null after
	//str = " \'asdas\"\'\"\"$PATH ADS $$ $chkhk df ";//have segmentation fault
	//str = "  chkhk ";
	//str = "  chkhk  \"HELLO -> \'\"";
	all.input = str;
	tokenized(&all, envp);
	token_to_cmd(&all);
	t_cmd *curr = all.cmd;
	while (curr != NULL)
	{
		int i = 0;
		while (i < curr->len)
		{
			printf("%i: %s\n",i, curr->words[i]);
			i++;
		}
		curr=curr->next;
	}  
	printf("cmd_len : %i \n",all.cmd_len);
	return 0;
} */

//complie:gcc create_cmd.c ../tool/free_error.c ../tool/tool_utils.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a
//test3:add_redirection

// int main(int argc, char **argv, char **envp)
// {
// 	t_data all;
// 	char *str;
// 	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
// 	str = " <infile|jhj|>hih ";
// 	//str = " cmd arg|";
// 	//str = "  chkhk df ";//have segmentation fault
// 	//str = "  chkhk  \"HELLO -> \'\";
// 	all.input = str;

// 	tokenized(&all, envp);
// 	int len = cmd_len(&all.token, 0);
// 	token_to_cmd(&all);
// 	t_cmd *curr_cmd = all.cmd;
// 	while(curr_cmd)
// 	{
// 		t_token *curr = curr_cmd->redi;
// 		int i = 0;
// 		while (i < curr_cmd->len)
// 		{
// 			printf("str: %i: %s\n",i, curr_cmd->words[i]);
// 			i++;
// 		}
// 		while (curr != NULL)
// 		{
// 			printf("redi: %s \n",curr->str);
// 			curr=curr->next;
// 		}
// 		curr_cmd=curr_cmd->next;
// 	}
// 	return 0;
// }