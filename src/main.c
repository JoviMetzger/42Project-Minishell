/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/16 10:56:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //___________________________________________
// // FOR LEAKS
// void ft_systemleaks(void)
// {
//     system("leaks -q minishell"); //remove
// }
// //  - atexit(ft_systemleaks); // USE FOR LEAKS
// //____________________________________________

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
	char	*prompt;

	first_check(argc, argv);
	all.env = init_env(envp);
	while (1)
	{
		
		all.status = 0;
		all.cmd = 0;
		all.token = 0;
		all.id = 0;
		prompt = display_prompt();
		handle_signal(1, &all);
		all.input = readline(prompt);
		ft_free(prompt);
		if (all.input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (all.input[0] != '\0')
			add_history(all.input);
		ft_commands(&all);
		free(all.input);
	}
	return (0);
}
