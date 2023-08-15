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
	else if (access(path, X_OK) != 0)
		print_error(cmd->words[0], 126, all);
	else if (execve(path, cmd->words, envp) == -1)
	{
		free(path);
		print_error(cmd->words[0], 0, all);
	}
	else
		free(path);
}

void	cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	all->id[cmd->index] = fork();
	if (all->id[cmd->index] == -1)
		print_error(NULL, 2, all);
	if (all->id[cmd->index] == 0)
	{
		do_redirection(cmd, all, envp);
		if (cmd->fd_in != 0)
			protect_dup2(cmd->fd_in, 0, all);
		if (cmd->fd_out != 1)
			protect_dup2(cmd->fd_out, 1, all);
		close_all_fd(&all->cmd, all);
		run_cmd(cmd, envp, all);
		exit(0);
	}
}
