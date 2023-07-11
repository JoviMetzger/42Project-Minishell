/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 12:55:41 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 15:25:05 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool get_export_state(char *name, t_env **head)
{
    t_env *tmp;

    tmp = *head;
    while (tmp != NULL)
    {
        if (ft_strcmp(name, tmp->name))
            return (tmp->for_export);
        tmp = tmp->next;
    }
    return(false);
}

int add_new_env_var(char *statement, t_env **head, bool for_export)
{
    char **line;

    line = split_envp(statement);
    if (get_export_state(line[0], head) && !for_export)
        for_export = true;
    unset_var(line[0], head);
    env_lstadd_back(head, env_lstnew(line[0], line[1], for_export));
    free(line);
    return (EXIT_SUCCESS);
}

char **split_envp(char *env)
{
    char **split;
    int idx_equal;

    split = (char **)malloc(sizeof(char *) * 3); //split = malloc(3 * sizeof(char *));
    idx_equal = ft_strchr(env, '=') - env;
    split[0] = ft_substr(env, 0, idx_equal);
    split[1] = ft_substr(env, idx_equal + 1, ft_strlen(&env[idx_equal]));
    split[2] = NULL;
    return (split);
}

static void init_oldpwd(t_env **head)
{
    char *tmp;
    
    unset_var("OLDPWD", head);
    tmp = ft_strjoin("OLDPWD=", getenv("HOME"));
    add_new_env_var(tmp, head, true);
    free(tmp);
}

t_env *init_env(char **envp)
{
    t_env *head;
    t_env *tmp;
    char **line;
    int i;

    line = split_envp(envp[0]);
    head = env_lstnew(line[0], line[1], true);
    free(line);
    i = 1;
    tmp = head;
    while (envp[i])
    {
        line = split_envp(envp[i]);
        tmp->next = env_lstnew(line[0], line[1], true);
        free(line);
        tmp = tmp->next;
        i++;
    }
    init_oldpwd(&head);
    return (head);

}
