/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/28 11:00:45 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	run_cmd(t_cmd *cmd, char **envp)
{
	char *path;
	
	path = find_path(cmd->words[0], envp);
	if ((is_builtin_cmd(cmd->words[0])) == 1) 
		exec_builtin_cmd(cmd->words);
	else if (execve(path, cmd->words, envp) == -1)
		print_error();
}

void	cmd_child(t_cmd *cmd, char **envp)
{
	int		fd[2];
	pid_t	id;

	pipe(fd);
	id = fork();
	if (id == -1)
		exit(1);
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
		close(fd[0]);
		waitpid(id, NULL, 0);
	}
}

void	last_cmd_child(t_cmd *cmd, char **envp)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		print_error();
	if (id == 0)
		run_cmd(cmd, envp);
	else
		waitpid(id, NULL, 0);
}

//complie:gcc find_path.c create_cmd.c run.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a
//test