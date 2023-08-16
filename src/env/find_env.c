/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 08:56:25 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/16 11:02:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			return (0);
		i++;
	}
	return (1);
}

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

char	*find_env(t_token **token, char	**envp)
{
	int		index;
	int		i;
	
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
