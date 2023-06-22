/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/22 13:44:32 by yizhang       ########   odam.nl         */
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
		//display_prompt();
		input = readline("minishell-> ");
		add_history(input);
		create_history(input, &data);
		ft_commands(input, envp, data);
	}
	return (0);
}