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

static void	first_check(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" \
				RED "!\n" RESET);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	all;
	//char	*prompt;

	first_check(argc, argv);
	all.envp = envp;
	all.env = init_env(envp);
	all.status = 0;
	while (1)
	{
		//prompt = display_prompt();
		display_prompt();
		//handle_signal(1, &all);
		all.input = readline(NULL);
		//ft_free(prompt);
		if (all.input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (all.input[0] != '\0')
			add_history(all.input);
		ft_commands(all.envp, &all);
		free(all.input);
	}
	return (0);
}
