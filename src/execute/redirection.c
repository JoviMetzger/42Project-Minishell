/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 10:51:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 11:00:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redirection(t_data *all)
{
	t_token *curr;
	t_cmd	*cmd;

	if (!all->cmd || !all->token)
		return ;
	curr = all->token;
	cmd = all->cmd;
	cmd->redi = NULL;
	while(cmd != NULL && curr != NULL)
	{
		if (curr->type == INFILE || curr->type == OUTFILE || curr->type == APPFILE || curr->type == DELIMI)
			add_token_end(&cmd->redi, copy_token(curr));
		else if (curr->type == PIPE)
			cmd = cmd->next;
		curr = curr->next;
	}
}

void	do_redirection(t_cmd *cmd, t_data *all, char **envp)
{
	t_token	*redi;
	int		in;
	int		out;

	redi = cmd->redi;
	in = 0;
	out = 0;
	while(redi)
	{
		if(redi->type == INFILE)
		{
			if (in != 0)
				close(in);
			in = redi_in(cmd, redi, all);
		}
		else if (redi->type == OUTFILE)
		{
			if (out != 0)
				close(out);
			out = redi_out(cmd, redi, all);
		}
		else if (redi->type == APPFILE)
		{
			if (out != 0)
				close(out);
			redi_app(cmd, redi, all);
		}
		else if (redi->type == DELIMI)
		{
			if (in != 0)
				close(in);
			redi_here_doc(cmd, redi, all, envp);
		}
		if (!redi->next)
			return ;
		redi = redi->next;
	}
}

int	redi_in(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;
	
	file = open(redi->str, O_RDONLY);
	if (file < 0)
		print_error(redi->str, 1, all);
	cmd->fd_in = file;
	return (file);
}

int	redi_out(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;
	
	file = open(redi->str, O_WRONLY | O_CREAT |O_TRUNC, 0777);
	if(file < 0)
		print_error(redi->str, 1, all);
	cmd->fd_out = file;
	return (file);
}

int	redi_app(t_cmd *cmd, t_token *redi, t_data *all)
{
	int	file;
	
	file = open(redi->str, O_WRONLY | O_APPEND | O_CREAT , 0777);
	if (file < 0)
		print_error(redi->str, 1, all);
	cmd->fd_out = file;
	return (file);
}
