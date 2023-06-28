/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/24 11:50:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        ft_env(t_env *env)
{
    while (env && env->next != NULL)
    {
        printf("%s", env->value);
        env = env->next;
    }
    if (env)
        printf("%s", env->value);
}

