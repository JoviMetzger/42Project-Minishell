/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/19 10:57:32 by jmetzger      ########   odam.nl         */
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

int	ft_is_name_valid(char *str)
{
	int	i;

    i = 0;
    if (str[0] == '=')
        return (1);
	while (str[i] && str[i] != '=')
	{
        
        if (!((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
            return (1);
        if (!((str[i] == '_') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')))
            return (1);
		i++;
	}
	return (0);
}

static int empty_export(t_data *data)
{
    t_env *tmp;
    
    tmp = data->env;
    while (tmp)
    {
        if (tmp->for_export)
            printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}

static int ft_error_msg(char *input)
{
    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
    ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int ft_export(char **input, t_data *data)
{
    int i;
    int exit_status;
    
    if (ft_argc(input) == 1) 
        return (empty_export(data));
    i = 0;
    exit_status = EXIT_SUCCESS;
    if (ft_is_name_valid(input[1]) == 1)
            exit_status = ft_error_msg(input[i]);
    while (input[++i])
    {
        if (ft_strchr(input[i], '='))
            add_new_env_var(input[i], &data->env, true);
    }
    return (exit_status);
}
