/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/20 09:39:01 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int		path_index(char **envp)
{
	int	i;

	i = 1;
	while(envp[++i] != NULL)
	{
		
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return (i);
	}
	if (!envp[i])
		return (-1);
	return (i);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_undone;
	char	*path;
	char	**all_path;
	int		i;
	
	
	i = path_index(envp);
	if (i < 0)
		return (NULL);
	all_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (all_path[++i])
	{
		path_undone = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(path_undone, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}

void	run_cmd(t_cmd *cmd, char **envp)
{
	char *path;
	
	path = find_path(cmd->words[0], envp);
	execve(path, cmd->words, envp);
		//exit(1);//print_error
}

//complie:gcc create_cmd.c run.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a


/* int main(int argc, char **envp)
{
	char *cmd[2];
	char *str;
	
	
	cmd[0] ="ls";
	cmd[1] = NULL;
	//execve("/bin/ls", cmd, envp);
	run_cmd(cmd, envp);
	return (0);
} */

/* int main(int argc, char **argv, char **envp)
{
	char *str;
	//str = "  c\'\"\' asdasda\"\'\">&| \"|\" dcd ";
	//str = " ls -alt| cmd aa a a a |";
	//str = "  echo \'hellow world\' u"; //have to have | after a sentences? why?
	str = "  wc \'hellow world\' |";
	
	t_token *token = tokenized(str);
	t_cmd *cmd = token_to_cmd(&token);
	t_cmd *curr = cmd;
	int len = 0;
	run_cmd(cmd, envp);
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
} */