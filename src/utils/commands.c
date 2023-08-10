/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/09 21:41:05 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* redi_loop();
 *	- Parameters;
 *		- t_cmd **top: the top of the command linked list;
 *		- t_data *all: the main data struct;
 *
 *	- The function iterates through the command list starting from 'top'.
 *	- For each command, it calls do_redirection() to handle 
 *	  input/output redirection based on the command's file descriptors.
 *	- If the command has no next element (last command), 
 *	  the function returns 0 to indicate successful completion.
 */
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

/* close_all_fd();
 *	- Parameter;
 *		- t_cmd **top: the top of the command linked list;
 *
 *	- The function iterates through the command list starting from 'top'.
 *	- For each command, it checks and closes the input (fd_in) 
 *	  and output (fd_out) file descriptors if they are not the default values.
 *	- If the command has no next element (last command), 
 *	  the function returns 0 to indicate successful completion.
 */
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

/* ft_exit_status();
 *	- Parameter;
 *		- t_data *all: the main data struct;
 *
 *	- The function iterates through each child process using protect_waitpid().
 *	- For each command, it retrieves its exit status using WEXITSTATUS() 
 *	  and updates the main data struct 'all' with the exit status.
 */
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

/* ft_child_process();
 *	- Parameters;
 *		- t_cmd *curr: the current command in the linked list;
 *		- char **envp: the environment variables;
 *		- t_data *all: the main data struct;
 *
 *	- The function iterates through the command list starting from 'curr'.
 *	- For each command, it sets up signal handling using handle_signal().
 *	- It then calls cmd_child() to execute the command in a child process, 
 *	  handles input/output redirections, and executes the command with execvp().
 *	- If the command has no next element (last command), the function returns.
 */
static void	ft_child_process(t_cmd *curr, t_data *all)
{
	while (curr)
	{
		handle_signal(2, all);
		cmd_child(curr, all);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
}

/* ft_commands();
 *	- Parameters;
 *		- char **envp: the environment variables;
 *		- t_data *all: the main data struct;
 *
 *	- The function starts by checking if the input is empty using ft_strcmp()
 *	  and returns if it is.
 *	- It then tokenizes the input using tokenized() to handle 
 *	  variable substitution and splits the input into separate commands
 *	  using token_to_cmd().
 *	- The original token list is freed using free_token() to release memory.
 *	- The function sets up the pipeline for commands using open_pipe() 
 *	  and allocates memory for an array to store child process IDs (all->id).
 *	- If the first command is a built-in command, 
 *	  it executes the built-in command using exec_builtin_cmd() and returns.
 *	- Otherwise, it calls ft_child_process() 
 *	  to handle the execution of child processes for each command.
 *	- After execution, it closes input/output file descriptors for each command 
 *	  using close_all_fd() and updates the exit status of each command 
 *	  using ft_exit_status().
 */
void	ft_commands(t_data *all)
{
	t_cmd	*curr;

	if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all);
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
		ft_child_process(curr, all);
		close_all_fd(&all->cmd);
		ft_exit_status(all);
		free_cmd(all);
	}
}
