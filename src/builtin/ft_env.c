/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 12:15:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_env();
 *	- Parameters:
 *		- t_data *data: main struct, access the environment variables;
 *
 *	- This function prints the environment variables that are marked 
 *	  with the 'for_export' state.
 *	- It loops through the linked list of environment variables 'data->env'.
 *	- If an environment variable has the 'for_export' state set to true, 
 *	  it will be printed in the format "name=value".
 *	- Returns EXIT_SUCCESS to indicate successful execution.
 */
int	ft_env(t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env != NULL)
	{
		if (env->for_export)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
