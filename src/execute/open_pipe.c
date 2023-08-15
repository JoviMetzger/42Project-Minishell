/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 15:24:54 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 15:24:54 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipe(t_data *all, t_cmd *cmd, int **fd_2d)
{
	fd_2d[cmd->index] = malloc(sizeof(int) * 2);
	if (!fd_2d[cmd->index])
		return (-1);
	protect_pipe(fd_2d[cmd->index], all);
	if (cmd->index != 0)
		cmd->fd_in = fd_2d[cmd->index - 1][0];
	if (!cmd->next)
	{
		protect_close(fd_2d[cmd->index][0], all);
		protect_close(fd_2d[cmd->index][1], all);
	}
	else
		cmd->fd_out = fd_2d[cmd->index][1];
	return (0);
}

int	open_pipe(t_data *all)
{
	int		**fd_2d;
	t_cmd	*curr;

	fd_2d = malloc(sizeof(int *) * (all->cmd_len + 1));
	if (!fd_2d)
		return (1);
	fd_2d[all->cmd_len] = NULL;
	curr = all->cmd;
	while (curr)
	{
		if (init_pipe(all, curr, fd_2d) == -1)
		{
			free_fd_2d(fd_2d);
			return (1);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free_fd_2d(fd_2d);
	return (0);
}

void	free_fd_2d(int **fd_2d)
{
	int	i;

	i = 0;
	while (fd_2d[i])
	{
		free(fd_2d[i]);
		i++;
	}
	free(fd_2d);
}
