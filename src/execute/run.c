/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/10 14:03:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* run_cmd();
 *	- Parameters:
 *		- t_cmd *cmd: the command struct, access 'words' variables;
 *		- char **envp: the environment variables;
 *		- t_data *data: the main data struct;
 *
 *	- Execute a command either as a built-in command or 
 *	  an external command using execve.
 *	- If the command is a built-in command, 
 *	  it is executed using exec_builtin_cmd().
 *	- Else the command is an external command.
 *		- The function first checks if the command exists and 
 *		  can be executed by calling access().
 *		- If the command exists, it tries to find its full path 	
 *		  using find_path().
 * 		- If the full path is found, the command is executed using execve().
 *	- If the command is not found or cannot be executed, 	
 * 	  it prints an error message.
 */
void	run_cmd(t_cmd *cmd, char **envp, t_data *data)
{
	char	*path;

	if ((is_builtin_cmd(cmd->words[0])) == 1)
	{
		exec_builtin_cmd(cmd->words, data);
		return ;
	}
	if (access(cmd->words[0], F_OK) == 0)
		path = cmd->words[0];
	else
		path = find_path(cmd->words[0], envp);
	if (!path)
		print_error(cmd->words[0], 127);
	else if (execve(path, cmd->words, envp) == -1)
		print_error(cmd->words[0], 0);
}

/* cmd_child();
 *	- Parameters:
 *		- t_cmd *cmd: the command struct, to access the variables;
 *		- char **envp: the environment variables.
 *		- t_data *all: the main data struct;
 *  
 *	- Inside the function, a new child process is created using fork(), 
 *	  and its process ID is stored in all->id[cmd->index].
 *	- If the fork operation fails, the child process exits with an error code.
 *	- In the child process, input and output redirections are set up based on 
 *	  the information provided in the 'cmd' struct.
 *	- If 'fd_in' is not equal to 0, it duplicates the file descriptor 'fd_in' 
 *	  to the standard input (0) using protect_dup2().
 *	- Same with, if 'fd_out' is not equal to 1, it duplicates the file 
 *	  descriptor 'fd_out' to the standard output (1) using protect_dup2().
 *	- After setting up the redirections, all file descriptors for 
 *	  the commands are closed with close_all_fd(&all->cmd).
 * 	- Finally, the actual command is executed by calling the run_cmd().
 *	- The child process then exits gracefully with an exit status of 0.
 */
void	cmd_child(t_cmd *cmd, t_data *all)
{
	char	**envp;

	envp = ft_get_envp(all->env);
	all->id[cmd->index] = fork();
	if (all->id[cmd->index] == -1)
		exit(0);
	if (all->id[cmd->index] == 0)
	{
		do_redirection(cmd, all, envp);
		if (cmd->fd_in != 0)
			protect_dup2(cmd->fd_in, 0);
		if (cmd->fd_out != 1)
			protect_dup2(cmd->fd_out, 1);
		close_all_fd(&all->cmd);
		run_cmd(cmd, envp, all);
		exit(0);
	}
}
