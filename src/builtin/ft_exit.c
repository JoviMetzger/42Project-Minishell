/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 18:36:38 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(int exit_status, int argc)
{
    printf("exit\n");
    if (exit_status == 0)
    {
        perror("exit");
        exit(225);
    }
    if (argc > 2)
    {
        perror("exit");
        exit(exit_status); 
    }
    exit(0);
}

// static void ft_free(void **argv)
// {
//     int i;
    
//     if (argv == NULL)
//         return ;
//     i = 0;
//     while (argv[i] != NULL)
//     {
//         free(argv[i]);
//         argv[i] = NULL;
//         i++;
//     }
//     free(argv);
// }

// void ft_exit(char **argv, char *cmd)
// {
//     int exit_status;
    
//     printf("exit\n");
//     if (argv[1] != NULL)
//     {
//         exit_status = ft_atoi(argv[1]);
//         if (exit_status == 0 && ft_strcmp(argv[1], "0") != 0)
//         {
//             perror("exit");
//             exit(225);
//         }
        
//         if (argv[2] != NULL)
//             perror("exit");
        
//         free(cmd);
//         ft_free((void**)argv);
//         exit(exit_status);
//     }
    
//     free(cmd);
//     ft_free((void**)argv);
//     exit(0);
// }

// static void ft_free(void **argv)
// {
//     int i;
    
//     if (argv == NULL)
//         return ;
//     i = 0;
//     while (argv[i] != NULL)
//     {
//         free(argv[i]);
//         argv[i] = NULL;
//         i++;
//     }
//     free(argv);
// }
