/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/16 10:56:52 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	fork_loop(t_data *all)
{
	t_cmd	*curr;

	handle_signal(2, all);
	curr = all->cmd;
	while (curr)
	{
		cmd_child(curr, all);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
}

void	ft_commands(t_data *all)
{
	//t_cmd	*curr;
	int	i;

	i = 0;
	if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all);
		token_to_cmd(all);
		free_token(all->token);
		all->token = NULL;
		open_pipe(all);
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		if (is_builtin_cmd(all->cmd->words[0]) == 1)
		{
			exec_builtin_cmd(all->cmd->words, all);
			return ;
		}
		fork_loop(all);
		close_all_fd(&all->cmd, all);
		//curr = all->cmd;
		while (i < all->cmd_len)
		{
			protect_waitpid(all->id[i], &all->status, 0, all);
			if (WEXITSTATUS(all->status))
				all->status = WEXITSTATUS(all->status);
			i++;
		}
		// ft_child_process(curr, all);
		// close_all_fd(&all->cmd);
		// ft_exit_status(all);
		// free_cmd(all);
	}
}
