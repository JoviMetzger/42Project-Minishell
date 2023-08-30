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

void	do_redirection(t_cmd *cmd, t_data *all)
{
	t_token	*redi;
	int		in;
	int		out;

	redi = cmd->redi;
	in = 0;
	out = 0;
	while (redi)
	{
		if (redi->type == INFILE)
			in = redi_in(cmd, redi, all);
		else if (redi->type == OUTFILE)
			out = redi_out(cmd, redi, all);
		else if (redi->type == APPFILE)
			redi_app(cmd, redi, all);
		if (!redi->next)
			return ;
		redi = redi->next;
	}
}

int	redi_in(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;

	(void)cmd;
	file = open(redi->str, O_RDONLY);
	if (file < 0)
		print_error(redi->str, 1, all);
	all->tmp_fd = file;
	return (file);
}

int	redi_out(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
		print_error(redi->str, 1, all);
	cmd->fd_out = file;
	return (file);
}

int	redi_app(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (file < 0)
		print_error(redi->str, 1, all);
	cmd->fd_out = file;
	return (file);
}
