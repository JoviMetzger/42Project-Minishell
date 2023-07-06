/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/06 08:38:41 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	run_cmd(t_cmd *cmd, char **envp)
{
	char *path;
	
	if( ft_strcmp(cmd->words[0], "builtin" )== 0)
	{
		printf("it's builtin");
		exit(0);
	}
	if (access(cmd->words[0], F_OK) == 0)
		path = cmd->words[0];
	else
		path = find_path(cmd->words[0], envp);
	if (!path)
		print_error(cmd->words[0], 127);
	else if (execve(path, cmd->words, envp) == -1)
		print_error(cmd->words[0], 0);
}

void	cmd_child(t_cmd *cmd, char **envp)
{
	int		fd[2];
	pid_t	id;
	

	pipe(fd);
	do_redirection(cmd);
	id = fork();
	if (id == -1)
		exit(1);
	if (id == 0)
	{
		dup2(fd[1],1);
		close(fd[1]);
		close(fd[0]);
		do_redirection(cmd);
		run_cmd(cmd, envp);
	}
	else
	{
		if (!cmd->redi)
		{
			dup2(fd[0],0);
			close(fd[1]);
			close(fd[0]);
		}
		else
		{
			close(fd[1]);
			close(fd[0]);
		}
		waitpid(id, NULL, 0);
	}
}

void	last_cmd_child(t_cmd *cmd, char **envp)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		print_error(NULL, 0);
	if (id == 0)
	{
		if (cmd->redi)
			do_redirection(cmd);
		run_cmd(cmd, envp);
	}
	else
		waitpid(id, NULL, 0);
}

//complie:gcc find_path.c create_cmd.c run.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a
//test
