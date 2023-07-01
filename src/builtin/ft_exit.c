/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 17:52:28 by jmetzger      ########   odam.nl         */
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
    if (input == NULL)
    {
        printf("Error: No exit status provided\n");
        exit(1);
    }
    else if (argc > 2)
    {
        printf("Error: Too many arguments for exit\n");
        exit(1); 
    }
    if (input[1] != NULL)
    {
        exit_status = atoi(input[1]);
        if (!ft_isdigit(exit_status))
        {
            perror("exit");
            exit(1);
        }
    }
    printf("exit_status: %d\n", exit_status); //rm 
    printf("exit\n");
    exit(exit_status);
}
