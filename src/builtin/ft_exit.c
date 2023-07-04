/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/04 11:18:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

void ft_exit(char **input)
{
    int argc;
    int exit_status;
    
    argc = ft_argc(input);
    exit_status = 0;
    if (argc > 2)
        printf("Error: exit: too many arguments\n");
    if (input[1] != NULL)
    {
        exit_status = atoi(input[1]);
        if (!ft_isdigit(exit_status))
        {
            printf("Error: exit: numeric argument required\n");
            exit(1);
        }
    }
    printf("exit\n");
    exit(exit_status);
}
