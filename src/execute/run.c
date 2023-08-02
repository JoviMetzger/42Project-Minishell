/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 18:59:18 by jmetzger      ########   odam.nl         */
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
 *	- This function is used for executing a command in a pipeline.
 *	- It creates a child process using fork() and sets up 
 *	  the necessary file descriptors for communication between 
 *	  the parent and child processes using protect_pipe.
 *	- It then calls run_cmd() to execute the command in the child process.
 *	- First, we create a pipe for communication between parent 
 *	  and child processes.
 *	- We fork a new process.
 *		- If fork failed, print error and exit with the exit status of 
 *		  the child process.
 *	- If 'id == 0', Child process: 
 *		- We set up redirection of standard output to the writing end 
 *		  of the pipe.
 *		- Execute the command in the child process with run_cmd().
 *	- Else ,Parent process:
 *		- Wait for the child process to complete.
 *		- Update the shell's overall status with the exit status of 
 *		  the child process.    
 */
void	cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	int		fd[2];
	pid_t	id;
	int		status;

	protect_pipe(fd);
	id = fork();
	if (id == -1)
		exit(WEXITSTATUS(status));
	if (id == 0)
	{
		protect_dup2(fd[1], 1);
		protect_close(fd[1]);
		protect_close(fd[0]);
		run_cmd(cmd, envp, all);
		exit (0);
	}
	else
	{
		protect_waitpid(id, &status, 0);
		all->status = WEXITSTATUS(status);
	}
}

/* last_cmd_child();
 *	- Parameters:
 *		- t_cmd *cmd: the command struct, to access the variables;
 *		- char **envp: the environment variables;
 *		- t_data *data: the main data struct;
 *
 *	- We fork a new process.
 *		- If fork failed, print error and exit with the exit status of 
 *		  the child process.
 *	- If 'id == 0), Child process:
 *		- Execute the command in the child process with run_cmd().
 *	- Else, Parent process:
 *		- Wait for the child process to complete.
 *		- Update the shell's overall status with the exit status 
 *		  of the child process.  
 */
void	last_cmd_child(t_cmd *cmd, char **envp, t_data *all)
{
	pid_t	id;
	int		status;

	id = fork();
	if (id == -1)
		print_error(NULL, 0);
	if (id == 0)
	{
		run_cmd(cmd, envp, all);
	}
	else
	{
		protect_waitpid(id, &status, 0);
		all->status = WEXITSTATUS(status);
	}
}
