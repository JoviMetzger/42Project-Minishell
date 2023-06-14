/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_and_execute.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/08 13:53:27 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_builtin_cmd(char *current_token)
{
    if (current_token == ECHO) 
        return (1);
    else if (current_token == CD) 
        return (1);        
    else if (current_token == PWD) 
        return (1);
    else if (current_token == EXPORT) 
        return (1);
    else if (current_token == UNSET) 
        return (1);
    else if (current_token == ENV)
        return (1);
    else
        return (0);
}

void    parse_and_execute(t_token *tokens, char **envp)
{
    while (tokens != NULL) 
    {
        if (is_builtin_cmd(tokens->type) == 1) 
            exec_builtin_cmd(tokens->type, envp);
        //else if () 
            //return ;    //    
        else 
            printf("error 1\n");
    }
}