/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/13 10:18:22 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	run_cmd(t_cmd *cmd, char **envp, t_data *all)
{
	char *path;
	
	protect_dup2(all->tmp_fd, 0, all);
	close(all->tmp_fd);
	if( ft_strcmp(cmd->words[0], "builtin" )== 0)
	{
		printf("it's builtin");
		exit(0);
	}
	if (access(cmd->words[0], F_OK) == 0)
		path = cmd->words[0];
	else if (access(path, X_OK) == 0)
	 	path = cmd->words[0];
	else
		path = find_path(cmd->words[0], envp);
	if (!path)
		print_error(cmd->words[0], 127, all);
	else if (access(path, X_OK) != 0 && path[0] == '.')
		print_error(cmd->words[0], 126, all);
	else if (access(path, X_OK) != 0)
	 	print_error(cmd->words[0], 127, all);
	else if (execve(path, cmd->words, envp) == -1)
	{
		free(path);
		print_error(cmd->words[0], 127, all);
	}
	else
		free(path);
}

int	cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	int	fd[2];

	if (protect_pipe(fd, all) == -1)
		return (-1);
	all->id[cmd->index] = fork();
	if (all->id[cmd->index] == -1)
		return (-1);
	if (all->id[cmd->index] == 0)
	{
		if (!cmd->next)
			cmd->fd_out = all->tmp_out;
		else
			cmd->fd_out = fd[1];
		do_redirection(cmd, all, envp);
		protect_dup2(cmd->fd_out, 1, all);
		close(all->tmp_out);
		close(fd[0]);
		close(fd[1]);
		run_cmd(cmd, envp, all);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(all->tmp_fd);
		all->tmp_fd = fd[0];
		return (0);
	}
}
