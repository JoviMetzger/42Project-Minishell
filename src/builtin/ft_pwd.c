/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:43:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd()
{
    char *buf;
    
    buf = getcwd(NULL, 0);
    if (buf)
    {
        ft_putstr_fd(buf, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
    {
        perror("getcwd() error");
        return (EXIT_FAILURE);
    }
    free(buf);
    return (EXIT_SUCCESS);
}
