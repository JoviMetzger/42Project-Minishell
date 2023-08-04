/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redi_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 14:56:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/03 14:53:46 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* redi_here_doc();
 *	- Parameters:
 *	  - t_token *redi: redirection token that contains 
 *		the here-document delimiter;
 *	  - t_data *all: main struct;
 *	  - char **envp: A pointer to the environment variables array;
 *
 *	- The user's input is written to the pipe, 
 *	  and the parent process (the shell) reads from the other end of the pipe, 
 *	  capturing the input into the specified file descriptor 'out'.
 *	- First, we create a pipe to communicate between the child 
 *	  and parent processes.
 *	- Then we fork a child process to handle the here-document input.
 *	- If 'id == 0': 
 *		- Child process: close the read end of the pipe 
 *		  and read input from the user into the pipe.
 *	- Else: 
 *		- Parent process: redirect the input to the read end of the pipe, 
 *		  close unnecessary file descriptors, 
 *		  and wait for the child process to finish.	
 */
void	redi_here_doc(t_cmd *cmd, t_token *redi, t_data *all, char **envp)
{
	int		fd[2];
	pid_t	id;

	protect_pipe(fd);
	id = fork();
	if (id < 0)
		print_error(NULL, 0);
	if (id == 0)
	{
		protect_close(fd[0]);
		here_doc(fd[1], redi->str, all, envp);
		protect_close(fd[1]);
	}
	else
	{
		cmd->fd_in = dup(fd[0]);
		protect_close(fd[0]);
		protect_close(fd[1]);
		protect_waitpid(id, NULL, 0);
	}
}

/* ft_exit_program();
 *	- Parameters:
 *	  - char *line: The input line to be freed before exiting;
 *	  - int out: The file descriptor to be closed before exiting;
 *
 *	- Frees the 'line' buffer, closes the file descriptor 'out', 
 *	  and exits the program with a successful status (exit code 0).
 */
static void	ft_exit_program(char *line, int out)
{
	free(line);
	protect_close(out);
	exit(0);
}

/* here_doc();
 *	- Parameters:
 *	  - int out: The file descriptor to which the here-document 
 *		input should be written;
 *	  - char *limiter: The delimiter that indicates the end of 
 *		the here-document input.
 *	  - t_data *all: main data struct;
 *	  - char **envp: A pointer to the environment variables array;
 *
 *	- In a while loop we read the input line from the user with a prompt "> ".
 *	- If the entered line matches the delimiter ,we exit the program(success).
 *	- If the line contains variables with a '$' (dollar sign).
 *		- Tokenize the line, swap variables with their values, 
 *		  and reconstruct the line.
 *	- ft_strjoin() a newline character to the line and write (protect_write()) 
 *	  it to the 'out' file descriptor.	
 */
void	here_doc(int out, char *limiter, t_data *all, char **envp)
{
	char		*line;
	t_token		*to_tmp;
	char		*tmp;

	tmp = NULL;
	to_tmp = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 
			&& ft_strlen(limiter) == ft_strlen(line))
			ft_exit_program(line, out);
		if (have_dollar(line))
		{
			to_tmp = dollar_split(line);
			swap_val(&to_tmp, envp, all);
			tmp = line;
			line = token_to_str(&to_tmp);
			free(tmp);
		}
		line = ft_strjoin(line, "\n");
		protect_write(out, line, ft_strlen(line));
		free(line);
	}
}
