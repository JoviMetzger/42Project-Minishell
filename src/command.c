/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/13 10:21:45 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_commands(char **envp, t_data *all)
{
	int	i;

	i = 0;
	if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		all->token = NULL;
		open_pipe(all);//return -1
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		fork_loop(all, envp);
		close_all_fd(&all->cmd, all);
		while (i < all->cmd_len)
		{
			protect_waitpid(all->id[i], &all->status, 0, all);
			if (WEXITSTATUS(all->status))
				all->status = WEXITSTATUS(all->status);
			i++;
		}
	}
}

void	fork_loop(t_data *all, char **envp)
{
	t_cmd	*curr;

	curr = all->cmd;
	while (curr)
	{
		cmd_child(curr, envp, all);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
}

int	redi_loop(t_cmd **top, t_data *all, char **envp)
{
	t_cmd	*curr;

	curr = *top;
	while (curr)
	{
		do_redirection(curr, all, envp);
		if (!curr->next)
			return (0);
		curr = curr->next;
	}
	return (0);
}

int	close_all_fd(t_cmd **top, t_data *all)
{
	t_cmd	*curr;

	curr = *top;
	while (curr)
	{
		if (curr->fd_in != 0)
			protect_close(curr->fd_in, all);
		if (curr->fd_out != 1)
			protect_close(curr->fd_out, all);
		if (!curr->next)
			return (0);
		curr = curr->next;
	}
	return (0);
}
