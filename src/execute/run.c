/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:07:35 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/19 18:50:43 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int		path_index(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (i);
		i++;
	}
	return (-1);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_undone;
	char	*path;
	char	**all_path;
	int		i;
	
	
	i = path_index(envp);
	printf("path:%s \n",envp[i]);
	if (i < 0)
		return (NULL);
	all_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (all_path[++i])
	{
		path_undone = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(path_undone, cmd);
		printf("path:%s \n",path);
		if (access(path, F_OK) == 0)
		{
			printf("path:%s \n",path);
			return (path);
		}
	}
	printf("path:%s \n",path);
	return (NULL);
}

void	run_cmd(char **cmd, char **envp)
{
	char *path;
	
	path = find_path(cmd[0], envp);
	//if (execve(path, cmd, envp) == -1)
		//print_error
}

//complie:gcc create_cmd.c run.c ../tokenized/split_token.c ../tokenized/token_util.c ../tokenized/tokenized.c ../../libft/libft.a


int main(int argc, char **envp)
{
	char *cmd[2];
	char *str;
	
	
	cmd[0] ="ls";
	cmd[1] = NULL;
	str = find_path(cmd[0], envp);
	printf("path:%s \n",str);
	//execve("/bin/ls", cmd, envp);
	run_cmd(cmd, envp);
	return (0);
}