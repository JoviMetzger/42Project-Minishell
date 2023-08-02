/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 08:56:25 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 14:13:42 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* all_upper();
 *	- Check if a string contains only uppercase letters.
 *	- Returns 1 if all characters in the string are uppercase letters, 
 *	  0 otherwise.
 */
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

/* env_index();
 *	- Parameters:
 *	  - t_token *token: A pointer to the token containing 
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
char	*find_env(t_token **token, char **envp)
{
	int	index;
	int	i;

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
