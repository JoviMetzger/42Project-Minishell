/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 12:55:56 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/04 14:37:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	NOTE: These functions are the same from libft, 
 *		  they just using 't_env' instead of 't_list'
 */

/* env_lstadd_back();
 *	- Parameters:
 *		- t_env **head: a pointer to the top/first node of the list;
 *		- t_env *new: the new node to be added to the back of the list;
 *
 *	- Adds a new node to the end of the list.
 *	- If the list is empty, the new node becomes the first node (head).
 *	- If the list is not empty, it finds the last node using env_lstlast() 
 *	  and appends the new node after it.
 */
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

/* env_lstlast();
 *	- Goes through the whole list till it is at the last node.
 *	- Returns the last node in the linked list 'lst'.
 */
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

/* env_lstnew();
 *	- Parameters:
 *		- char *name: The name for the node;
 *		- char *value: The value for the node;
 *		- bool for_export: Whether the node is for export (true/false);
 *
 *	- Create a new node for a linked list.
 *	- Returns the new node.
 */
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
