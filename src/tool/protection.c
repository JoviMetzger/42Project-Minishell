/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 12:54:21 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 12:55:28 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	protect_waitpid(pid_t id, int *status, int options, t_data *all)
{
	if (waitpid(id, status, options) == -1)
	{
		print_error(NULL, 1, all);
		return (-1);
	}
	return (0);
}

void	protect_dup2(int file, int file2, t_data *all)
{
	if (dup2(file, file2) == -1)
	{
		g_exit_status = 1;
		print_error(NULL, 1, all);
	}
}

void	protect_close(int file, t_data *all)
{
	if (close(file) == -1)
	{
		g_exit_status = 1;
		print_error(NULL, 1, all);
	}
}

void	protect_write(int fd, char *buf, int count, t_data *all)
{
	if (write(fd, buf, count) == -1)
	{
		g_exit_status = 1;
		print_error(NULL, 1, all);
	}
}

int	protect_pipe(int fd[2], t_data *all)
{
	(void)all;
	if (pipe(fd) == -1)
	{
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}
