/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:38 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/23 02:55:12 by jmetzger      ########   odam.nl         */
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

/* ft_remove();
 *	- This function removes an environment variable with the given name 
 *	  from a linked list of variables. 
 *	- It iterates through the list, finds the variable, 
 *	  updates the list to exclude it, and frees the memory.
 */
void	ft_remove(char *name, t_env *tmp, t_env *prev)
{
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/* unset_var();
 *	- Parameters:
 *		- char *name: the environment variable to be unset (removed);
 *		- t_env **env: struct of the environment;
 *
 *	- This function is the entry point for removing an environment variable. 
 *	- It handles the case of removing the head of the list directly 
 *	  and delegates the task of removing from other positions to ft_remove. 
 *
 *	Note: This function is also used in add_new_env_var() 
 *		  for updating an existing variable.
 */
int	unset_var(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	if (tmp != NULL && ft_strcmp(name, tmp->name) == 0)
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return (EXIT_SUCCESS);
	}
	prev = tmp;
	ft_remove(name, tmp, prev);
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
		if (ft_is_name_valid(input[1]) == 1)
		{
			ft_error_msg(input[i]);
			return (EXIT_FAILURE);
		}
		if (ft_strchr(input[i], '='))
		{
			ft_error_msg(input[i]);
			return (EXIT_FAILURE);
		}
		unset_var(input[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
