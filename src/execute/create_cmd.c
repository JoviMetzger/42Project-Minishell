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
	new = NULL;
	while(curr)
	{
		if (curr->index == 0 || (curr->prev && curr->prev->type == PIPE))
		{
			len = cmd_len(&curr, curr->index) + 1;
			//printf ("len:%i \n",len);
			words = malloc(sizeof(char *) * len + 1);
			if (!words)
				print_error(NULL, 0);
			words[len] = NULL;
			i = 0;
			while (curr && curr->type != PIPE)
			{
				while (curr->type == WORD)
				{
					if (curr->str)
					{
						if (!words[i] && curr->str)
							words[i] = ft_strdup(curr->str);
						else
							words[i] = ft_strjoin(words[i], curr->str);
					}
					if (!curr->next || curr->type == PIPE)
						break ;
					curr = curr->next;
				}
				if (!curr->next || curr->type == PIPE)
					break ;
				curr = curr->next;
				if (words[i])
					i++;
			}
			new = new_cmd(words, len);
			new->len = len;
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

	i = 0;
	curr = *token;
	while(curr != NULL)
	{
		if (curr->index == index)
		{
			while (curr && curr->type != PIPE)
			{
				if (curr->type == WORD)
				{
					//printf("%i. %s*\n", i, curr->str);
					i++;
					while (curr->type == WORD && curr->next)
						curr = curr->next;
				}
				if (!curr->next || curr->type == PIPE)
					return (i);
				curr = curr->next;
			}
			return (i);
		}
		if (!curr->next)
			return (i);
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

//complie:gcc create_cmd.c ../tool/free_error.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../../libft/libft.a

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

// int main(int argc, char **argv, char **envp)
// {
// 	t_data all;
// 	char *str;
// 	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
// 	//str = " <infile cmd  <infile arg arg>outfile| cmd1 aa a a a >1outfile|";
// 	//str = " cmd arg|";//segv
// 	//str = " \'asdas\"\'\"\"$PATH ADS $$ $chkhk df ";//have segmentation fault
// 	//str = "  chkhk jkjj kk K|adfas asdf";
// 	//str = "  chkhk  \"HELLO -> \'\"hjkhjk\'kkk\' ee |SDSDA|";
// 	//str = "ls | echo \'$PATH\' \"$PATHfs\"sdf | sfgsdf|sfgs";
// 	str = "  ls   ";
// 	all.input = str;

// 	tokenized(&all, envp);
// 	//printf("len : %i \n",len);
// 	token_to_cmd(&all);
// 	t_cmd *curr = all.cmd;
// 	int len = cmd_len(&all.token, 0);
// 	//printf("len : %i \n",len);
// 	while (curr != NULL)
// 	{
// 		int i = 0;
// 		while (i < curr->len)
// 		{
// 			printf("%i: %s\n",i, curr->words[i]);
// 			i++;
// 		}
// 		if (!curr->next)
// 			break ;
// 		curr=curr->next;
// 		printf("\n");
// 	}

// 	return 0;
// }

//complie:gcc create_cmd.c ../tool/free_error.c ../tool/tool_utils.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../env/find_env.c ../env/handle_dollar_sign.c ../../libft/libft.a
//test3:add_redirection

/* int main(int argc, char **argv, char **envp)
{
	t_data all;
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	str = " <infile cmd  <infile arg arg>outfile| cmd1 aa a a a >1outfile|";//error
	//str = " cmd arg|";
	str = "  chkhk df ";//have segmentation fault
	//str = "  chkhk  \"HELLO -> \'\"";
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