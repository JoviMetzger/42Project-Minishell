/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:18:10 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/20 16:13:56 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*token_to_cmd(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*new;
	t_token *curr;
	char	**words;
	int		len;
	int		i;

	curr = *token;
	cmd = NULL;
	while(curr != NULL)
	{
		i = 0;
		if (curr->type == CMD)
		{
			len = cmd_len(&curr, curr->index);
			words = malloc(sizeof(char *) * len);
			if (!words)
				return (NULL);//free some thing
			words[len - 1] = NULL;
			while (i < len - 1)
			{
				words[i] = curr->str;
				i++;
				if (curr->next == NULL)
					break ;
				curr = curr->next;
			}
			new = new_cmd(words, len);
			add_cmd_end(&cmd, new);
		}
		curr = curr->next;
	}
	return (cmd);
}

 
int	cmd_len(t_token **token, int index)
{
	int	i;
	t_token *curr;

	i = 1;
	curr = *token;
	while(curr != NULL)
	{
		if (curr->index == index && curr->type == CMD && curr!= NULL)
		{
			i++;
			if(curr->next == NULL)
				return (i);
			curr = curr->next;
			while (curr->type == ARG && curr != NULL)
			{
				i++;
				if(curr->next == NULL)
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


//complie:gcc create_cmd.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a



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



//complie:gcc create_cmd.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a
//test2:token_to_cmd && cmd_len

/* int main(int argc, char **argv, char **envp)
{
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	str = " cmd arg| cmd aa a a a |";
	//str = " cmd arg|";
	//str = "  chkhk df ";//have segmentation fault
	//str = "  chkhk ";
	
	t_token *token = tokenized(str);
	int len = cmd_len(&token, 0);
	printf("%i ",len);
	t_cmd *cmd = token_to_cmd(&token);
	t_cmd *curr = cmd;
	while (curr != NULL)
	{
		int i = 0;
		while (i < curr->len)
		{
			printf("%s ",curr->words[i]);
			i++;
		}
		curr=curr->next;
	} 
	return 0;
} 
 */