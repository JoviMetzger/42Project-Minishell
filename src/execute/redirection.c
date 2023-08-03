/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 10:51:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 16:25:24 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

void	do_redirection(t_cmd *cmd, t_data *all, char **envp)
{
	t_token	*redi;

	redi = cmd->redi;
	while(redi)
	{
		if(redi->type == INFILE)
			redi_in(cmd, redi);
		else if (redi->type == OUTFILE)
			redi_out(cmd, redi);
		else if (redi->type == APPFILE)
			redi_app(cmd, redi);
		else if (redi->type == DELIMI)
			redi_here_doc(cmd, redi, all, envp);
		if (!redi->next)
			return ;
		redi = redi->next;
	}
}

void	redi_in(t_cmd *cmd, t_token *redi)
{
	int	file;
	
	file = open(redi->str, O_RDONLY);
	if (file < 0)
		print_error(redi->str, 1);
	cmd->fd_in = file;
	//protect_close(file);
}

void	redi_out(t_cmd *cmd, t_token *redi)
{
	int	file;
	
	file = open(redi->str, O_WRONLY | O_CREAT |O_TRUNC, 0777);
	if(file < 0)
		print_error(redi->str, 1);
	cmd->fd_out = file;
	//protect_close(file);
}

void	redi_app(t_cmd *cmd, t_token *redi)
{
	int	file;
	
	file = open(redi->str, O_WRONLY | O_APPEND | O_CREAT , 0777);
	if (file < 0)
		print_error(redi->str, 1);
	cmd->fd_out = file;
	//protect_close(file);
}