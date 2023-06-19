/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/19 17:10:41 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*find_path(t_cmd *cmd, char **envp)
{
	
}

void	run_cmd(t_cmd *cmd, char **envp)
{
	path = find_path(cmd, envp);
	if (execve(path, cmd->words, envp) == -1)
		print_error();
}