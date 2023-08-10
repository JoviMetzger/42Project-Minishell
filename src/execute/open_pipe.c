/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 15:24:54 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 21:30:28 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* init_pipe();
 *	- Parameters:
 *		- t_cmd *cmd: the command for which the pipe is being initialized;
 *		- int **fd_2d: 2D array of file descriptors representing the pipeline;
 *
 *	- The function allocates memory for an array 
 *	  and stores it in fd_2d[cmd->index].
 *	- If memory allocation fails, the function returns -1.
 *	- The function then calls protect_pipe() to create the pipe 
 *	  and protect against interruptions.
 *	- If the command is not the first command in the pipeline, 
 *	  it sets the input file descriptor (fd_in).
 *	- If the command is the last command in the pipeline,
 *	  it closes both ends of its own pipe.
 *	- Otherwise, for intermediate commands, it sets 
 *	  the output file descriptor (fd_out) to the write 
 *	  end of the current command's pipe.
 */
int	init_pipe(t_cmd *cmd, int **fd_2d)
{
	fd_2d[cmd->index] = malloc(sizeof(int) * 2);
	if (!fd_2d[cmd->index])
		return (-1);
	protect_pipe(fd_2d[cmd->index]);
	if (cmd->index != 0)
		cmd->fd_in = fd_2d[cmd->index - 1][0];
	if (!cmd->next)
	{
		close(fd_2d[cmd->index][0]);
		close(fd_2d[cmd->index][1]);
	}
	else
		cmd->fd_out = fd_2d[cmd->index][1];
	return (0);
}

/* free_fd_2d();
 *	- Parameter;
 *		- int **fd_2d: a 2D array of file descriptors;
 *
 *	- The function iterates through the array and frees the memory 
 *	  for each subarray before freeing the main array itself.
 */
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

/* open_pipe();
 *	- Parameter;
 *		- t_data *all: the main data struct;
 *
 *	- The function allocates memory for a 2D array of file descriptors (fd_2d).
 * 	- The last element of fd_2d is set to NULL, indicating the end of the array.
 *	- It then iterates through the command linked list and calls init_pipe() 
 *	  for each command to initialize the pipes.
 *	- If any error occurs during the initialization, 
 *	  it frees the allocated memory for fd_2d and returns 1 to indicate failure.
 *	- After initializing all pipes, it frees the memory allocated for fd_2d and 
 *	  returns 0 to indicate success.
 */
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
		if (init_pipe(curr, fd_2d) == -1)
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
