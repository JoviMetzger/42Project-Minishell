/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/24 18:42:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int check_name(char *name)
// {
//     int j;

//     j = 0;
//     while (name[j])
//     {
//         if (!ft_isalnum(name[j]) && name[j] != '_')
//             printf("Invalid variable name\n");
//     }
//     j++;
// }

// void        ft_export(char **arg)
// {
//     int i;
//     char *name;
//     char *value;
    
//     i = 0;
//     if (!arg[1] || !ft_strrchr(arg[1], '='))
//         return ;
    
//     while (arg[1][i] && arg[1][i] != '=')
//         i++;
//     name = ft_substr(arg[1], 0, i);
//     if (check_name(name))
//         free(name);
//     i++;
//     value = ft_strdup(arg[1] + 1);
//     // add_env(name, value);
//     free(name);
//     free(value);
// }