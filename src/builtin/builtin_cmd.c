/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 14:22:31 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/03 13:08:14 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_builtin_cmd(char *command)
{
    if (ft_strcmp(command, "cd") == 0) 
        return (1);
    if (ft_strcmp(command, "echo") == 0) 
        return (1);
    if (ft_strcmp(command, "env") == 0) 
        return (1);
    if (ft_strcmp(command, "export") == 0) 
        return (1);
    if (ft_strcmp(command, "pwd") == 0) 
        return (1);
    if (ft_strcmp(command, "unset") == 0) 
        return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
    return (0);
}

void    exec_builtin_cmd(char **input, char **envp)
{
	if (ft_strcmp(input[0], "cd") == 0) 
        ft_cd(input[1]);
    else if (ft_strcmp(input[0], "echo") == 0) 
        ft_echo(input);
    else if (ft_strcmp(input[0], "env") == 0) 
        ft_env(envp);
    else if (ft_strcmp(input[0], "export") == 0) 
        ft_export(input, envp);
    else if (ft_strcmp(input[0], "pwd") == 0) 
        ft_pwd();
    else if (ft_strcmp(input[0], "unset") == 0) 
        ft_unset(input, envp);
	else if (ft_strcmp(input[0], "exit") == 0)
		ft_exit(input);
}
