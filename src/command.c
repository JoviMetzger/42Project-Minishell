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

void ft_commands(char **envp, t_data *all)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	if (ft_strcmp(all->input, "exit") == 0)
		exit(0);
	//else if (ft_strcmp(all->input, "history") == 0)
	//	printf_history(all->history);
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		open_pipe(all);
		redi_loop(&all->cmd, all, envp);
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		curr = all->cmd;
		while (curr)
		{
			cmd_child(curr, envp, all);
			if (!curr->next)
				break ;
			curr = curr->next;
		}
		close_all_fd(&all->cmd);
		while (i < all->cmd_len)
		{
			protect_waitpid(all->id[i], &all->status, 0);
			if (WEXITSTATUS(all->status))
				all->status = WEXITSTATUS(all->status);
			i++;
		}
		free_cmd(all);
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
