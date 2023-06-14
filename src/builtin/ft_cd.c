/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 10:26:54 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// chdir();
//  used to change the current working directory of the calling process.
// void ft_cd(const char *path)
// {
//     const char *home;
//     int result;
    
//     if (path == NULL)
//     {
//         home = getenv("HOME");
//         if (home != NULL)
//             chdir(home);
//     }
//     else
//     {
//         result = chdir(path);
//         if (result != 0)
//             perror("cd");
//     }
// }