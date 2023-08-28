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

int	redi_here_doc(t_token *redi, t_data *all, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	id;

	all->here_status = 0;
	protect_pipe(fd, all);
	id = fork();
	if (id < 0)
		print_error(NULL, 1, all);
	if (id == 0)
	{
		handle_signal(3);
		protect_close(fd[0], all);
		here_doc(fd[1], redi->str, all, envp);
		protect_close(fd[1], all);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		all->tmp_fd = dup(fd[0]);
		if (all->tmp_fd == -1)
			return (1);
		protect_close(fd[0], all);
		protect_close(fd[1], all);
	}
	if (protect_waitpid(id, &status, 0, all) == -1)
		return (1);
	all->here_status = status;
	if (status == 256)
		g_exit_status = 1;
	return (0);
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
}
