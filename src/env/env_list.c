/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 12:55:56 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/12 13:07:23 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head)
		*head = new;
	if (head)
	{
        if (!*head)
            *head = new;
        else
        {
            tmp = env_lstlast(*head);
            tmp->next = new;
            new->next = NULL;  
        }
	}
}

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_env	*env_lstnew(char *name, char *value, bool for_export)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
    new->name = name;
	new->value = value;
    new->for_export = for_export;
	new->next = NULL;
	return (new);
}
