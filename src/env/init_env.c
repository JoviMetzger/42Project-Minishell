/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 12:55:41 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/25 20:59:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* get_export_state();
 *  - Parameters:
 *    - char *name: The name of the environment variable to check;
 *    - t_env **env: the environment struct;
 * 
 *  - Get the export state of an environment variable by name.
 *  - Returns 'true' if the variable is marked for export, 'false' otherwise.
 */
bool	get_export_state(char *name, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name))
			return (tmp->for_export);
		tmp = tmp->next;
	}
	return (false);
}

/* add_new_env_var();
 *  - Parameters:
 *    - char *statement: The string containing the new variable 
 * 		in the format "NAME=VALUE";
 *    - t_env **env: the environment struct;
 *    - bool for_export: A boolean indicating if 
 * 		the variable is marked for export;
 * 
 *  - Add a new environment variable to the linked list.
 *  - First splits the env in 'name' and 'value'.
 * 	- Checks if the statment is marked for export
 * 		- if it isn't it will be marked as 'true'.
 * 		- Reason for this, so that the program can handle 
 * 		  environment variables with different export states and ensure that 
 * 		  only the necessary variables are made available to child processes. 
 * 	- It will unset the variable (remove it from the environment).
 * 		- Reason for this, so no duplicates are in the environment, 
 * 		  if the statment is already in the environment.
 * 	- It will add it again to the end of the linked list.
 */
int	add_new_env_var(char *statement, t_env **env, bool for_export)
{
	char	**line;

	line = split_envp(statement);
	if (get_export_state(line[0], env) && !for_export)
		for_export = true;
	unset_var(line[0], env);
	env_lstadd_back(env, env_lstnew(line[0], line[1], for_export));
	free(line);
	return (EXIT_SUCCESS);
}

/* split_envp();
 *  - Parameters:
 *    - char *env: The environment variable string in the format "NAME=VALUE";
 * 
 *  - Split an environment variable string into its 'name' and 'value'.
 * 	- First, we allocate memory to hold two pointers (name and value) 
 * 	  and a NULL terminator.
 * 	- Then we find the index of the '=' character in 
 * 	  the environment variable string.
 * 	- ft_substr() the name part of the environment variable 
 * 	  and store it in split[0].
 * 	- ft_substr() the value part of the environment variable 
 * 	  and store it in split[1].
 *  - Add a NULL terminator to the array to mark the end.
 *  - Returns a array of strings containing the name and value.
 */
char	**split_envp(char *env)
{
	char	**split;
	int		idx_equal;

	split = (char **)malloc(sizeof(char *) * 3);
	idx_equal = ft_strchr(env, '=') - env;
	split[0] = ft_substr(env, 0, idx_equal);
	split[1] = ft_substr(env, idx_equal + 1, ft_strlen(&env[idx_equal]));
	split[2] = NULL;
	return (split);
}

// static void	init_oldpwd(t_env **env)
// {
// 	char	*tmp;

// 	unset_var("OLDPWD", env);
// 	tmp = ft_strjoin("OLDPWD=", getenv("HOME"));
// 	add_new_env_var(tmp, env, true);
// 	free(tmp);
// }

/* init_env();
 *  - Parameters:
 *    - char **envp: An array of strings representing 
 * 		the initial environment variables;
 *  - We need to separate the 'name' and 'value' in the env, 
 * 	  so it is easier to work with.
 * 	- First we do split_env() and env_lstnew() once, 
 * 	  so we have a starting point, 
 * 	  otherwise we will loop forever in the while loop.
 * 	- In a while loop we split_env() by '=', 
 * 	  so we end up with 'name' and 'value'.
 * 	- We add the **str to the linked list with env_lstnew(). 
 *  	- NOTE: envp[i] starts at 'variable 1' and not 'variable 0', 
 * 				otherwise the first variable will be twice in the env.
 * 				We already have the first variable, 
 * 				because we needed a starting point.
 * 	- Lastly, we init_oldpwd(), because it is not always there 
 * 	  depending on what if you run your program in bash or sh.
 */
t_env	*init_env(char **envp)
{
	t_env	*init_env;
	t_env	*tmp;
	char	**line;
	int		i;

	line = split_envp(envp[0]);
	init_env = env_lstnew(line[0], line[1], true);
	free(line);
	i = 1;
	tmp = init_env;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		tmp->next = env_lstnew(line[0], line[1], true);
		free(line);
		tmp = tmp->next;
		i++;
	}
	return (init_env);
}
