/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/06 16:48:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
    char *buf;
    
    buf = (char *)malloc(sizeof(char) * 1000);
    if (getcwd(buf, 1000) != NULL)
        printf("%s\n", buf);
    else 
        perror("pwd error ----//////wrong error message\n");
    free(buf);
}
