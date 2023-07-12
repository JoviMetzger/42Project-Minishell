/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redi_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 14:56:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/12 10:33:48 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi_here_doc(t_token *redi, t_data *all, char **envp)
{
	int		fd[2];
	pid_t	id;

	pipe(fd);
	id = fork();
	if (id < 0)
		print_error(NULL, 0);
	if (id == 0)
	{
		close(fd[0]);
		here_doc(fd[1], redi->str, all, envp);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		waitpid(id, NULL, 0);
	}
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
			free(line);
			close(out);
			exit(0);
		}
		if (have_dollar(line))
		{
			to_tmp = dollar_split(line);
			swap_val(&to_tmp, envp, all);
			tmp = line;
			line = token_to_str(&to_tmp);
			free(tmp);
		}
		line = ft_strjoin(line,"\n");
		write(out, line, ft_strlen(line));
		free(line);
	}
}
