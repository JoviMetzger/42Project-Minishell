/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 16:06:14 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(char **envp)
{
   int i;

   i = 0;
   while (envp[i] != NULL)
   {
      printf("%s\n", envp[i]);
      i++;
   }
}
