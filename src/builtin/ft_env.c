/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:42:57 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_data *data)
{
   t_env *env;

   env = data->env;
   while (env != NULL)
   {
      if (env->for_export)
         printf("%s=%s\n", env->name, env->value);
      env = env->next;
   }
   return (EXIT_SUCCESS);
}
