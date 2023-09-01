/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/01 10:06:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_error_msg();
 *	- This function displays an error message to the standard error output 
 *	  when 'input' is not a valid identifier for an environment variable.
 */
static int	ft_error_msg(char *input)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/* empty_export();
 *	- Parameters:
 *		- t_data *data: main struct, to access the environment;
 *
 *	- For each variable marked with 'for_export', it displays 
 *	  the environment variables, with 'declare -x' at the beginning.
 */
static int	empty_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x ");
		if (tmp->for_export)
			printf("%s=%s\n", tmp->name, tmp->value);
		else if (tmp->name && tmp->value)
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/* ft_is_name_valid();
 *	- Parameters:
 *		- char *str: the export name (everything before the '=');
 *
 *	- This function checks if the 'name' is valid to use as an env variable.
 *	- The 'name' is only allowed to start with a small/capital letter or 
 *	  an underscore ('_').
 *	- The rest of the characters may be small/capital letters, digits, 
 *	  or underscores ('_').
 */
int	ft_is_name_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') 
				|| (str[0] >= 'A' && str[0] <= 'Z')))
			return (1);
		if (!((str[i] == '_') || (str[i] >= 'a' && str[i] <= 'z') 
				|| (str[i] >= 'A' && str[i] <= 'Z') 
				|| (str[i] >= '0' && str[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

/* ft_export();
 *	- Parameters:
 *		- char **input: the whole input command line, split into a char**;
 *		- t_data *data: main struct, to access the environment;
 *
 *	- This function implements the 'export' command behavior in the shell.
 *	- If there are no arguments after 'export', it calls the empty_export() 
 *	  function to display the environment variables with 'declare -x' prefix.
 *	- If there are arguments, it checks if each 'name' 
 *	  (everything before the '=' sign) is valid using ft_is_name_valid().
 *	- If a 'name' is not valid, it displays an error message using ft_error_msg() 
 *	  and returns the appropriate exit status.
 *	- For each argument that contains an equal sign '=', 
 *	  it adds or updates the environment variable with add_new_env_var().
 */
int	ft_export(char **input, t_data *data)
{
	int	i;
	int	exit_status;

	if (ft_argc(input) == 1)
		return (empty_export(data));
	i = 0;
	exit_status = EXIT_SUCCESS;
	while (input[++i])
	{
		if (ft_is_name_valid(input[i]) == 1)
		{
			exit_status = ft_error_msg(input[i]);
			break ;
		}
		else if (input[i] && input[i][0] == '=')
		{
			exit_status = ft_error_msg(input[2]);
			break ;
		}
		else if (input[i])
			add_new_env_var(input[i], &data->env, true);
	}
	return (exit_status);
}
