/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/28 17:38:58 by jmetzger      ########   odam.nl         */
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

void ft_exit(char **argv)
{
    exit(0);
    int argc;
    
    argc = ft_argc(argv);
    printf("exit\n");
    if (argv == NULL)
    {
        printf("Error: No exit status provided\n");
        exit(1);
    }
    if (argc > 2)
    {
        printf("Error: Too many arguments for exit\n");
        exit(1); 
    }
    // if (!ft_isdigit(exit_status))
    //     perror("exit");
    exit(0);
}
