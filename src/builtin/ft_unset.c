/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:38 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:41:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

static void ft_error_msg(char *name)
{
    ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

int unset_var(char *name, t_env **head)
{
    t_env *tmp;
    t_env *next;

    tmp = *head;
    if (ft_strchr(name, '='))
    {
        ft_error_msg(name);
        return (EXIT_FAILURE);
    }
    while (tmp && tmp->next != NULL)
    {
        if (ft_strcmp(name, tmp->next->name))
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

int ft_unset(char **input, t_env **head)
{
    int i;
    
    i = 1;
    while (i < ft_argc(input)) 
    {
        unset_var(input[i], head);
        i++;
    }
    return (EXIT_SUCCESS);
}
