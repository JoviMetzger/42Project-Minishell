/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:41:13 by jmetzger      ########   odam.nl         */
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

bool	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "=") == 0)
		return (false);
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

bool is_onstr(const char *str, int c)
{
    int i;
    
    if (!str)
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (true);
        i++;   
    }
    return (false);
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

static void loop_and_export(char *name, t_data *data)
{
    t_env *tmp;
    
    tmp = data->env;
    while (tmp)
    {
        if (ft_strcmp(name, tmp->name) == 0)
        {
            tmp->for_export = true;
            break ;
        }
        tmp = tmp->next;
    }
}

int ft_export(char **input, t_data *data)
{
    int i;
    int exit_status;
    
    if (ft_argc(input) == 1) 
        return (empty_export(data));
    exit_status = EXIT_SUCCESS;
    i = 0;
    while (input[++i])
    {
        if (!ft_is_valid(input[i]))
            exit_status = ft_error_msg(input[i]);
        else if (is_onstr(input[i], '='))
        {
            add_new_env_var(input[i], &data->env, true);
            continue ;
        }
        else
            loop_and_export(input[i], data);
    }
    return (exit_status);
}