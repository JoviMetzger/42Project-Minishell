/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redi_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 14:56:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/04 16:05:49 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi_here_doc(t_token *redi)
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
		here_doc(fd[1], redi->str);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		waitpid(id, NULL, 0);
	}
}

void	here_doc(int out, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && ft_strlen(limiter) == ft_strlen(line) - 1)
		{
			free(line);
			close(out);
			exit(0);
		}
		write(out, line, ft_strlen(line));
		free(line);
	}
}

char	*get_next_line(int fd)
{
	int		i;
	int		j;
	char	buff;
	char	*str;

	i = 8;
	j = 0;
	str = malloc(600);
	while (i)
	{
		i = read(fd, &buff, 1);
		if (i < 0)
			return (free(str), NULL);
		if (i > 0)
			str[j] = buff;
		if (i == 0 || str[j] == '\n')
			break ;
		j++;
	}
	str[j++] = '\n';
	str[j++] = '\0';
	return (str);
}
