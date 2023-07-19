/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/19 10:57:59 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_error_msg(char *path)
{
    char *error_msg;

    error_msg = ft_strjoin("minishell: cd: ", path);
    perror(error_msg);
    free(error_msg);
    return (EXIT_FAILURE);
}

void update_pwd(t_data *data)
{
    char cwd[1024];
    char *updated_var;
    
    getcwd(cwd, 1024);
    updated_var = ft_strjoin("PWD=", cwd);
    add_new_env_var(updated_var, &data->env, true);
    free(updated_var);
}


void update_oldpwd(char *tmp, t_data *data)
{
     char *oldpwd;
     
     oldpwd = ft_strjoin("OLDPWD=", tmp);
     add_new_env_var(oldpwd, &data->env, true);
     free(oldpwd);
}

int ft_cd(char *path, t_data *data)
{
    char tmp[1024];
    
    getcwd(tmp, 1024);
    if (path == NULL || ft_strcmp(path, "~") == 0)
    {
        update_oldpwd(&tmp[0], data);
        chdir(getenv("HOME"));
        update_pwd(data);
        return (EXIT_SUCCESS);
    }
    if (chdir(path) == 0)
    {
        update_oldpwd(&tmp[0], data);
        update_pwd(data);
        return (EXIT_SUCCESS);
    }
    return (ft_error_msg(path));
}
