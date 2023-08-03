/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 12:15:21 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_error_msg();
 *	- Parameters:
 *		- char *path: the directory path that caused the error;
 *
 *	- The function displays an error message to standard output 
 *	  when the specified '*path' does not exist.
 *	- Using ft_strjoin() to combining the prefix "minishell: cd: " 
 *	  with the invalid 'path'.
 *	- The error message is then displayed using perror().
 *	- Returns EXIT_FAILURE to indicate the failure condition.
 */
static int	ft_error_msg(char *path)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: cd: ", path);
	perror(error_msg);
	free(error_msg);
	return (EXIT_FAILURE);
}

/* update_pwd();
 *	- Parameters:
 *		- t_data *data: main struct, access the environment variables;
 *
 *	- This function gets the current working directory and updates 
 *	  the 'PWD' environment variable.
 *	- It uses getcwd() to get the current directory path.
 *	- The 'PWD' variable is then constructed by combining 
 *	  the variable name and its value using ft_strjoin().
 *	- The updated 'PWD' variable is added to the environment 
 *	  using add_new_env_var().
 *	- If 'PWD' already exists in the environment, 
 *	  its value is updated with the current working directory.
 */
void	update_pwd(t_data *data)
{
	char	cwd[1024];
	char	*updated_var;

	getcwd(cwd, 1024);
	updated_var = ft_strjoin("PWD=", cwd);
	add_new_env_var(updated_var, &data->env, true);
	free(updated_var);
}

/* update_oldpwd();
 *	- Parameters:
 *		- char *current: the current working directory;
 *		- t_data *data: main struct, to access the environment variables;
 *
 *	- This function updates the 'OLDPWD' environment variable 
 *	  with the current working directory.
 *	- It constructs the 'OLDPWD' string using ft_strjoin() 
 *	  to combine the variable name and its value.
 *	- The new 'OLDPWD' variable is added to env using add_new_env_var().
 *	- If 'OLDPWD' already exists in the environment, its value is updated.
 */
void	update_oldpwd(char *current, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", current);
	add_new_env_var(oldpwd, &data->env, true);
	free(oldpwd);
}

/* ft_cd();
 *	- Parameters:
 *		- char *path: the directory to which the function should navigate;
 *		- t_data *data: main struct, for updating the environment variables;
 *
 *	- First we get the current directory with getcwd();
 *	- If 'path' is NULL or "~"(optinal), 
 *	  the function changes to the user's home directory.
 *		- It updates the "OLDPWD" environment variable to 
 *		  the previous working directory.
 *		- Then it changes the current working directory using chdir("HOME").
 *		- It updates the "PWD" env variable to the new working directory.
 *	- If 'path' is not NULL, 
 *	  it uses chdir(path) to changes the current working directory.
 *		- It updates the "OLDPWD" environment variable to 
 *		  the previous working directory.
 *		- It updates the "PWD" env variable to the new working directory.
 *	- If the change of directory fails, it displays an error message 
 *	  using ft_error_msg() and returns the error code.
 */
int	ft_cd(char *path, t_data *data)
{
	char	tmp[1024];

	getcwd(tmp, 1024);
	if (path == NULL || ft_strcmp(path, "~") == 0)
	{
		update_oldpwd(&tmp[0], data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (chdir(path) == 0)
	{
		update_oldpwd(&tmp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (ft_error_msg(path));
}
