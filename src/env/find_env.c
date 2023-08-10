/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 08:56:25 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/10 14:46:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* env_index();
 *	- Parameters:
 *	  - t_token *token: the token containing 
 *		the environment variable name (starting with '$');
 *	  - char *envp: The array of strings representing the environment variables;
 *
 *	- Find the index of the matching environment variable in 'envp'.
 *	- Returns the index of the matching environment variable in 'envp' 
 *	  or -1 if not found.
 */
static int	env_index(t_token *token, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(&token->str[1], "=");
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], tmp, ft_strlen(tmp)) != NULL)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}

/* find_env();
 *	- Parameters:
 *	  - t_token **token: A double pointer to the token containing 
 *		the environment variable name (starting with '$');
 *	  - char **envp: The array of strings representing the environment variables;
 *
 *	- Find the value of the environment variable represented by 'token'.
 *	- Returns a pointer to the value of the environment variable in 'envp' 
 *	  or NULL if not found.
 */
char	*find_env(t_token **token, t_data *all)
{
	int		index;
	int		i;
	char	**envp;

	envp = ft_get_envp(all->env);
	i = 0;
	if (!*token)
		return (NULL);
	index = env_index(*token, envp);
	if (index == -1 || !envp[index])
		return (NULL);
	while (envp[index][i] != '=')
		i++;
	return (&envp[index][i + 1]);
}

/* ft_protect_and_free();
 *	- This function is responsible for freeing memory allocated 
 *	  for environment variables and their values.
 */
static void	ft_protect_and_free(int i, char **envp)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(envp[j]);
		j++;
	}
	free(envp);
	return ;
}

/* ft_loop();
 *	- Parameters:
 *		- char **envp: array of strings (environment variables);
 *		- int i: The index where the new environment variable entry should 
 *		  be added;
 *		- t_env *current: copy of the environment struct;
 *
 *	- This function creates and adds variables to the envp array.
 *	- It allocates memory for the new entry using malloc() and copies 
 *	  the 'name' and 'value' into it.
 *	- The function then copies the new entry into the envp array at index i.
 *	- If any memory allocation fails during this process, 
 *	  it calls ft_protect_and_free() to release allocated memory.
 */
static char	**ft_loop(char **envp, int i, t_env *current)
{
	char	*temp;
	char	*separator;
	char	*pair;
	char	*full_entry;
	size_t	length;

	length = ft_strlen(current->name) + ft_strlen(current->value) + 2;
	envp[i] = (char *)malloc(length * sizeof(char));
	if (!envp[i])
		ft_protect_and_free(i, envp);
	temp = ft_strdup(current->name);
	separator = "=";
	pair = ft_strjoin(temp, separator);
	free(temp);
	if (!pair)
		ft_protect_and_free(i, envp);
	full_entry = ft_strjoin(pair, current->value);
	free(pair);
	if (!full_entry)
		ft_protect_and_free(i, envp);
	ft_strcpy(envp[i], full_entry);
	free(full_entry);
	return (envp);
}

/* ft_get_envp();
 *	- Parameter:
 *		- t_env *env: the environment struct;
 *
 *	- This function turns the env struct into a char**.
 *	- The function calculates the total number of environment variable 
 *	  entries in the linked list by counting the nodes.
 *	- It allocates memory for an array of strings 'envp' to store 
 *	  the environment variables and their values.
 *	- The function then iterates through the linked list using ft_loop(), 
 *	  to create and populate each environment variable entry in the envp array.
 *	- Once all entries are added, a NULL pointer is placed at the end of 
 *	  the envp array to indicate the end.
 *	- The function returns the envp array containing the environment variables 
 *	  and values.
 */
char	**ft_get_envp(t_env *env)
{
	int		count;
	t_env	*current;
	char	**envp;
	int		i;

	count = 0;
	current = env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (envp == NULL)
		return (NULL);
	current = env;
	i = -1;
	while (++i < count)
	{
		envp = ft_loop(envp, i, current);
		current = current->next;
	}
	envp[count] = NULL;
	return (envp);
}

// // -------------------------------------------------	
// // -------------------------------------------------
// static void free_envp(char **envp)
// {
// 	int i;
//     if (envp != NULL)
//     {
// 		i = 0;
//         while (envp[i] != NULL)
//         {
//             free(envp[i]);
// 			i++;
//         }
//         free(envp);
//     }
// }
// // -------------------------------------------------	
// // -------------------------------------------------
