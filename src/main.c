/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/30 14:59:40 by yizhang       ########   odam.nl         */
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
		create_history(&all);
		ft_commands(envp, &all);
	}
	return (0);
}