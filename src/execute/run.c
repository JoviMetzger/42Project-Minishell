/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/20 17:51:27 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	run_cmd(t_cmd *cmd, char **envp)
{
	char *path;
	
	path = find_path(cmd->words[0], envp);
	execve(path, cmd->words, envp);
		//exit(1);//print_error
}

void	cmd_child(t_cmd *cmd, char **envp)
{
	int		fd[2];
	pid_t	id;

	pipe(fd);
	id = fork();
	if (id == -1)
		exit(1);
	cmd->in = fd[0];
	cmd->out = fd[1];
	if (id == 0)
	{
		dup2(fd[1], 1);
		run_cmd(cmd, envp);
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		//close(fd[0]);
		waitpid(id, NULL, 0);
	}
}

void	last_cmd_child(t_cmd *cmd, char **envp)
{
	//int		fd[2];
	pid_t	id;

	//pipe(fd);
	id = fork();
	if (id == -1)
		exit(1);
	if (id == 0)
	{
		dup2(cmd->in, 1);
		run_cmd(cmd, envp);
	}
	else
	{
		close(cmd->in);
		waitpid(id, NULL, 0);
	}
}

//complie:gcc find_path.c create_cmd.c run.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a
//test

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