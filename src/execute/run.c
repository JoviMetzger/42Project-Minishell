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

void	cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	all->id[cmd->index] = fork();
	if (all->id[cmd->index] == -1)
		exit(0);
	if (all->id[cmd->index] == 0)
	{
		do_redirection(cmd, all, envp);
		if (cmd->fd_in != 0)
			protect_dup2(cmd->fd_in, 0);
		if (cmd->fd_out != 1)
			protect_dup2(cmd->fd_out, 1);
		close_all_fd(&all->cmd);
		run_cmd(cmd, envp);
		exit(0);
	}
}
