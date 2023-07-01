/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 11:42:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_data all;
    char *prompt;
    
    if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" RED "!\n" RESET);
		exit(0);
	}
    while (1)
    {
        //signals_wait();
        prompt = display_prompt();
        all.input = readline(prompt);
        //signals_run();
        ft_free(prompt);
        add_history(all.input);
        //create_history(&all);
        ft_commands(envp, &all);
    }
    return (0);
}