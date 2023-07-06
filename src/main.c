/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 13:47:03 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_data all;
    char *prompt;
    //int status = 0;
    
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
        free(all.input);
    }
    return (0);
}