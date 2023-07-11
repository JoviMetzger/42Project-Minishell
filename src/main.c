/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/11 10:52:44 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_data all;
    char *prompt;

    if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" RED "!\n" RESET);
		exit(0);
	}
    all.envp = envp;
    all.env = init_env(envp);
    // 
    while (1)
    {
        signals_wait();
        prompt = display_prompt();
        all.input = readline(prompt);
        signals_run();
        ft_free(prompt);
        add_history(all.input);
        ft_commands(all.envp, &all);
        free(all.input);
    }
    return (0);
}