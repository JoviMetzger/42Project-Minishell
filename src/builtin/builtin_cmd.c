/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 14:22:31 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/13 19:31:11 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_builtin_cmd(char *command)
{
    if ((ft_strcmp(command, "cd") == 0)) 
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

bool   exec_builtin_cmd(char **input, t_data *data)
{
	if (ft_strcmp(input[0], "cd") == 0) 
        data->status = ft_cd(input[1], data);
    else if (ft_strcmp(input[0], "echo") == 0) 
        data->status = ft_echo(input);
    else if (ft_strcmp(input[0], "env") == 0) 
        data->status = ft_env(data);
    else if (ft_strcmp(input[0], "export") == 0) 
        data->status = ft_export(input, data);
    else if (ft_strcmp(input[0], "pwd") == 0) 
        data->status = ft_pwd();
    else if (ft_strcmp(input[0], "unset") == 0) 
        data->status = ft_unset(input, &data->env);
	else if (ft_strcmp(input[0], "exit") == 0)
		data->status = ft_exit(input, data);
    else
        return (false);
    return (true);
}
