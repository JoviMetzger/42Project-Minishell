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

static void	run_cmd_(char *path, DIR *dir, t_data *all, char **envp)
{
	if (!path)
		print_error(all->cmd->words[0], 127, all);
	else if (!dir && access(path, X_OK) != 0 && path[0] == '.' )
		print_error(all->cmd->words[0], 126, all);
	else if (dir && (path[0] == '.' || path[0] == '/'))
	{
		closedir(dir);
		print_error(all->cmd->words[0], 7, all);
	}
	else if (!dir && access(path, X_OK) != 0)
		print_error(all->cmd->words[0], 127, all);
	else if (!path && !dir && access(all->cmd->words[0], X_OK) != 0)
		print_error(all->cmd->words[0], 6, all);
	else if (execve(path, all->cmd->words, envp) == -1)
	{
		free(path);
		print_error(all->cmd->words[0], 127, all);
	}
	else
		free(path);
}

void	run_cmd(t_cmd *cmd, char **envp, t_data *all)
{
	char	*path;
	DIR		*dir;

	dir = opendir(cmd->words[0]);
	protect_dup2(all->tmp_fd, 0, all);
	close(all->tmp_fd);
	if ((is_builtin_cmd(cmd->words[0])) == 1)
	{
		exec_builtin_cmd(cmd->words, all);
		return ;
	}
	if (access(cmd->words[0], F_OK) == 0)
		path = cmd->words[0];
	else if (access(path, X_OK) == 0 && !dir)
		path = cmd->words[0];
	else
		path = find_path(cmd->words[0], envp);
	run_cmd_(path, dir, all, envp);
}

static void	ft_do_(t_cmd *cmd, t_data *all, int fd[2], char **envp)
{
	if (!cmd->next)
		cmd->fd_out = all->tmp_out;
	else
		cmd->fd_out = fd[1];
	do_redirection(cmd, all);
	protect_dup2(cmd->fd_out, 1, all);
	protect_close(all->tmp_out, all);
	protect_close(fd[0], all);
	protect_close(fd[1], all);
	run_cmd(cmd, envp, all);
	exit(0);
}

int	cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	int		fd[2];

	do_here_doc(cmd, envp, all);
	if (protect_pipe(fd, all) == -1)
		return (-1);
	handle_signal(2);
	all->id[cmd->index] = fork();
	if (all->id[cmd->index] == -1)
		return (-1);
	if (all->id[cmd->index] == 0)
	{
		ft_do_(cmd, all, fd, envp);
	}
	else
	{
		protect_close(fd[1], all);
		if (all->tmp_fd)
			protect_close(all->tmp_fd, all);
		all->tmp_fd = fd[0];
		return (0);
	}
	return (0);
}
