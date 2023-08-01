/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 10:51:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/31 22:27:15 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redirection(t_data *all)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!all->cmd || !all->token)
		return ;
	curr = all->token;
	cmd = all->cmd;
	cmd->redi = NULL;
	while (cmd != NULL && curr != NULL)
	{
		if (curr->type == INFILE || curr->type == OUTFILE 
			|| curr->type == APPFILE || curr->type == DELIMI)
			add_token_end(&cmd->redi, copy_token(curr));
		else if (curr->type == PIPE)
			cmd = cmd->next;
		curr = curr->next;
	}
}

void	do_redirection(t_cmd *cmd, t_data *all, char **envp)
{
	t_token	*redi;

	redi = cmd->redi;
	while (redi)
	{
		if (redi->type == INFILE)
			redi_in(redi);
		else if (redi->type == OUTFILE)
			redi_out(redi);
		else if (redi->type == APPFILE)
			redi_app(redi);
		else if (redi->type == DELIMI)
			redi_here_doc(redi, all, envp);
		if (!redi->next)
			return ;
		redi = redi->next;
	}
}

void	redi_in(t_token *redi)
{
	int	file;

	file = open(redi->str, O_RDONLY);
	if (file < 0)
		print_error(redi->str, 1);
	protect_dup2(file, 0);
	protect_close(file);
}

void	redi_out(t_token *redi)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
		print_error(redi->str, 1);
	protect_dup2(file, 1);
	protect_close(file);
}

void	redi_app(t_token *redi)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (file < 0)
		print_error(redi->str, 1);
	protect_dup2(file, 1);
	protect_close(file);
}
