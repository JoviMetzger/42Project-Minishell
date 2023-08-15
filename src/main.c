/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 11:37:38 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_data all;

	(void)argc;
	(void)argv;
	all.envp = envp;
	//atexit(leaks);
	while (1)
	{
		all.cmd = NULL;
		all.token = NULL;
		all.id = NULL;
		all.input = readline("minishell-> ");
		add_history(all.input);
		ft_commands(envp, &all);
		free_all(&all);
		//exit(0);//test leaks
	}
	return (0);
}