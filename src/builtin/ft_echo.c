/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:40 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/12 14:24:46 by jmetzger      ########   odam.nl         */
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

int ft_echo(char **input)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (!input)
        return (EXIT_FAILURE);
    if (ft_argc(input) > 1)
    {
        while (input[i] && ft_strcmp(input[i], "-n") == 0)
        {
            n = 1;
            i++;
        }
        if (input[i])
        {
            ft_putstr_fd(input[i], STDOUT_FILENO);
            i++;
        }
        while (input[i])
        {
            ft_putstr_fd(" ", STDOUT_FILENO);
            ft_putstr_fd(input[i], STDOUT_FILENO);
            i++;
        }
        if (n == 0)
            ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
