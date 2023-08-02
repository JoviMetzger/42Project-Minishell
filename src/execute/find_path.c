/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 12:25:44 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 16:02:33 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* path_index();
 *	- Parameters:
 *	  - char **envp: A pointer to the environment variables array;
 *
 *	- Find the index of the "PATH" environment variable 
 *	  in the given 'envp' array.
 *	- Returns the index of the "PATH" environment variable if found, 
 *	  or -1 if not found.
 */
int	path_index(char **envp)
{
	int	i;

	i = 1;
	while (envp[++i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return (i);
	}
	if (!envp[i])
		return (-1);
	return (i);
}

/* find_path();
 *	- Parameters:
 *	  - char *cmd: The command to search for in 
 *		the directories specified by "PATH";
 *	  - char **envp: A pointer to the environment variables array;
 *
 *	- First we get the index of the "PATH" environment variable, 
 *	  with path_index().
 *	- Then we split the "PATH" variable value into an array of directory 
 *	  paths using ':' as the delimiter.
 *	- We loop through each directory path in the "PATH" array 
 *	  to find the full path of the command.
 *		- We ft_strjoin() the current directory path till we have the full path.
 *		- Check if the current 'path' is accessible (exists) 
 *		  using the 'access' function.
 *		- If the command is found, free the 'all_path' array 
 *		  and return the full path.
 */
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
		free(path_undone);
		if (access(path, F_OK) == 0)
		{
			free_2dstr(all_path);
			return (path);
		}
	}
	free_2dstr(all_path);
	return (NULL);
}
