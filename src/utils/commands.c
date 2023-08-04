/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/04 12:49:49 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	close_all_fd(t_cmd **top)
{
	t_cmd	*curr;

	curr = *top;
	while (curr)
	{
		if (curr->fd_in != 0)
			protect_close(curr->fd_in);
		if (curr->fd_out != 1)
			protect_close(curr->fd_out);
		if (!curr->next)
			return (0);
		curr = curr->next;
	}
	return (0);
}

static void	ft_exit_status(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->cmd_len)
	{
		protect_waitpid(all->id[i], &all->status, 0);
		if (WEXITSTATUS(all->status))
			all->status = WEXITSTATUS(all->status);
		i++;
	}
}

static void	ft_child_process(t_cmd *curr, char **envp, t_data *all)
{
	while (curr)
	{
		cmd_child(curr, envp, all);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
}

/* ft_commands();
 *	-
 */
void	ft_commands(char **envp, t_data *all)
{
	t_cmd	*curr;

	if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		open_pipe(all);
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		curr = all->cmd;
		if (is_builtin_cmd(all->cmd->words[0]) == 1)
		{
			exec_builtin_cmd(all->cmd->words, all);
			return ;
		}
		ft_child_process(curr, envp, all);
		close_all_fd(&all->cmd);
		ft_exit_status(all);
		free_cmd(all);
	}
}
