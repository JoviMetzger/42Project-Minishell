/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/04 12:58:29 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int main(int argc, char **argv, char **envp)
{
	t_data all;

	(void)argc;
	(void)argv;
	while (1)
	{
		all.input = readline("minishell-> ");
		add_history(all.input);
		//create_history(&all);
		//if (all.input)
		ft_commands(envp, &all);
		free(all.input);
	}
	return (0);
}