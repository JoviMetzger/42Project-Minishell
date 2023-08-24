/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redi_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 14:56:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 13:06:56 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_signal_heredoc();
 *	- We turn of the control characters.
 *	- SIG_DFL: "Signal Default" It is a constant that represents the default
 *	  action that the operating system should take when a particular signal is 
 *	  received by a process.
 */
void	ft_signal_heredoc(void)
{
	struct termios	term;
	int i = 1;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	g_exit_status = WTERMSIG(i);
}

int	redi_here_doc(t_token *redi, t_data *all, char **envp)
{
	int		fd[2];
	pid_t	id;
	protect_pipe(fd, all);
	ft_signal_heredoc();
	id = fork();
	if (id < 0)
		print_error(NULL, 1, all);
	if (id == 0)
	{
		//ft_signal_heredoc();
		protect_close(fd[0], all);
		here_doc(fd[1], redi->str, all, envp);
		protect_close(fd[1], all);
	}
	else
	{
		// ft_signal_heredoc();
		all->tmp_fd = dup(fd[0]);
		if (all->tmp_fd == -1)
			exit (1);
		protect_close(fd[0], all);
		protect_close(fd[1], all);
		if (protect_waitpid(id, &g_exit_status, 0, all) == -1)
				exit (1);
			else if (WEXITSTATUS(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			else if (WIFSIGNALED(g_exit_status))
				g_exit_status = WTERMSIG(g_exit_status) + 128;
	}
	return (all->tmp_fd);
}

void	here_doc(int out, char *limiter,t_data *all, char **envp)
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
		//ft_signal_heredoc();
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 
			&& ft_strlen(limiter) == ft_strlen(line))
		{
			if (line)
				free(line);
			protect_close(out, all);
			exit(0);
		}
		if (have_dollar(line))
		{
			to_tmp = dollar_split(line, DQUO);
			swap_val(&to_tmp, envp);
			tmp = line;
			line = token_to_str(&to_tmp);
			free(tmp);
		}
		line = ft_strjoin(line,"\n");
		protect_write(out, line, ft_strlen(line), all);
		free(line);
	}
	if (!line)
		g_exit_status = 1;
	g_exit_status = 0;
}
