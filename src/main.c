/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/20 18:00:50 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_history *data;
    
(void)argc;
(void)argv;
    while (1)
    {
        display_prompt();
        input = readline(NULL);
        create_history(input, &data);
        if (input != NULL)
            ft_commands(input, envp, data);
        
    }
    //free_history();
    return (0);
}