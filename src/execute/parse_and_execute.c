/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_and_execute.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 14:44:57 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_builtin_cmd(char command)
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
    return (0);
}

void    exec_builtin_cmd(char **arg)
{
    //int result;

    if (ft_strcmp(arg[0], "cd") == 0) 
        ft_cd();
    if (ft_strcmp(arg[0], "echo") == 0) 
        ft_echo();
    if (ft_strcmp(arg[0], "env") == 0) 
        ft_env();
    if (ft_strcmp(arg[0], "export") == 0) 
        ft_export();
    if (ft_strcmp(arg[0], "pwd") == 0) 
        ft_pwd();
    if (ft_strcmp(arg[0], "unset") == 0) 
        ft_unset();
    return (0)
}

void    parse_and_execute(t_token *tokens, char **envp)
{
    if (is_builtin_cmd(tokens->type) == 1) 
        exec_builtin_cmd(tokens->type, envp);   
}