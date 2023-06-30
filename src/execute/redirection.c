/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 10:51:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/29 17:22:26 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi_in(t_cmd *cmd)
{
	if (!cmd->in)
		return ;
	cmd->infile = open(cmd->in, O_RDONLY);
	dup2(cmd->infile, 0);
	close(cmd->infile);
}

void	redi_out(t_cmd *cmd)
{
	if (!cmd->out)
		return ;
	cmd->outfile = open(cmd->out, O_WRONLY | O_CREAT , 0777);
	dup2(cmd->outfile, 0);
	close(cmd->outfile);
}

void	redi_app(t_cmd *cmd)
{
	if (!cmd->app)
		return ;
	cmd->appfile = open(cmd->app, O_WRONLY | O_APPEND | O_CREAT , 0777);
	dup2(cmd->appfile, 0);
	close(cmd->appfile);
}

//mini_pipe