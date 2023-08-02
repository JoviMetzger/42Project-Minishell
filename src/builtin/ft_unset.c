/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:38 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 12:17:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_error_msg();
 *	- This function displays an error message to the standard error output 
 *	  when 'name' is not a valid identifier for an environment variable.
 */
static void	ft_error_msg(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

/* unset_var();
 *	- Parameters:
 *		- char *name: the environment variable to be unset (removed);
 *		- t_env **env: struct of the environment;
 *
 *	- This function is used to remove an environment variable specified 
 *	  by 'name' from the linked list 'env'.
 *	- If the 'name' contains an equal sign '=' (invalid format),
 *	  it displays an error message using ft_error_msg().
 *	- The function loops through the linked list and removes the matching 
 *	  environment variable from 'env'.
 *	- Returns EXIT_FAILURE if the 'name' contains an equal sign '=' or if 
 *	  the specified variable is not found.
 *
 *	Note: This function is also used in add_new_env_var() 
 *		  for updating an existing variable.
 */
int	unset_var(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	if (ft_strchr(name, '='))
	{
		ft_error_msg(name);
		return (EXIT_FAILURE);
	}
	while (tmp && tmp->next != NULL)
	{
		if (ft_strcmp(name, tmp->next->name) == 0)
		{
			next = tmp->next->next;
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			tmp->next = next;
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/* ft_unset();
 *	- Parameters:
 *		- char **input: the whole input command line, split into a char**;
 *		- t_env **env: struct of the environment (env);
 *
 *	- This function removes environment variables specified in 
 *	  the 'input' command line.
 *	- It iterates through the 'input' arguments 
 *	  starting from index 1 (skipping the command name).
 *	- For each argument, it calls the unset_var() function to remove 
 *	  the corresponding environment variable from 'env'.
 */
int	ft_unset(char **input, t_env **env)
{
	int	i;

	i = 1;
	while (i < ft_argc(input))
	{
		unset_var(input[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
