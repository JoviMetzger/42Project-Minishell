/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/05 21:54:40 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **input, char **envp)
{
        if (ft_strcmp(input[0], "exit") == 0)
            exit(0);
        else if (ft_strcmp(input[0], "env") == 0)
            printf("history\n");
            //ft_env(input, envp);
}


