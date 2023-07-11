/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:43:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long int g_exit_status;

bool ft_is_digit(char *str) 
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-' && str[i] != '+')
            return false;
        i++;
    }
    return true;
}

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

int ft_exit(char **input)
{    
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (ft_argc(input) == 2)
    {
        if (ft_is_digit(input[1]))
        {
            g_exit_status = ft_atoi(input[1]);
        }
        else
        {
            ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
            g_exit_status = EXIT_FAILURE;
            exit(g_exit_status);
        }
    }
    else if (ft_argc(input) > 2)
    {
        g_exit_status = EXIT_FAILURE;
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
    }
    else
    {
        g_exit_status = EXIT_SUCCESS;
        exit(g_exit_status);
    }
    return (0);
}
