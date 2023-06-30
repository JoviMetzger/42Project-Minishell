/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/30 14:47:08 by jmetzger      ########   odam.nl         */
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
    // signal(SIGINT, handle_ctrl_c);
	// signal(SIGQUIT, handle_ctrl_bs);
    while (1)
    {
        prompt = display_prompt();
        ft_signal_handler(3);
        all.input = readline(prompt);
        ft_free(prompt);
        add_history(all.input);
        //create_history(&all);
        ft_commands(envp, &all);
    }
    return (0);
}