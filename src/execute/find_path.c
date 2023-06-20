/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 12:25:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/20 12:26:05 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		path_index(char **envp)
{
	int	i;

	i = 1;
	while(envp[++i] != NULL)
	{
		
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return (i);
	}
	if (!envp[i])
		return (-1);
	return (i);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_undone;
	char	*path;
	char	**all_path;
	int		i;
	
	
	i = path_index(envp);
	if (i < 0)
		return (NULL);
	all_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (all_path[++i])
	{
		path_undone = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(path_undone, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}