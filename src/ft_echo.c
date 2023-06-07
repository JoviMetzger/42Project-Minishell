/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:40 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/06 16:48:46 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

void ft_echo(char **input)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (ft_argc(input) > 1)
    {
        while (input[i] && ft_strcmp(input[i], "-n") == 0)
        {
            n = 1;
            i++;
        }
        while (input[i])
        {
            printf("%s ", input[i]);
            if (input[i + 1] && input[i][0] != '\0')
                printf(" ");
            i++;
        }
        if (n == 0)
            printf("\n");
    }
}
