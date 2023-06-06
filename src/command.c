/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/06 17:01:18 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **input, char **envp, t_history *data)
{
    (void)envp;
    if (ft_strcmp(input[0], "exit") == 0)
        exit(0);
    else if (ft_strcmp(input[0], "history") == 0)
        printf_history(data);
    // else if (ft_strcmp(input[0], "env") == 0)
    //     ft_env(input, envp);
    // else if (ft_strcmp(input[0], "uset") == 0)
    //     ft_uset();
    // else if (ft_strcmp(input[0], "export") == 0)
    //     ft_export();
    // else if (ft_strcmp(input[0], "pwd") == 0)
    //     ft_pwd();
    // else if (ft_strcmp(input[0], "cd") == 0)
    //     ft_cd(input, envp);
    // else if (ft_strcmp(input[0], "echo") == 0)
    //     ft_echo(); 
}