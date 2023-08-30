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


// void leaks(void)
// {
// 	system("leaks -q minishell");
// }
int	g_exit_status;

static void	first_check(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" \
				RED "!\n" RESET);
		exit(0);
	}
}

static void	init_all(t_data *all)
{
	all->tmp_out = dup(1);
	all->tmp_fd = dup(0);
	protect_dup2(all->tmp_out, 1, all);
	protect_dup2(all->tmp_fd, 0, all);
	all->cmd = NULL;
	all->token = NULL;
	all->id = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	all;
	char	*prompt;
	char	*input;

	first_check(argc, argv);
	all.env = init_env(envp);
	while (1)
	{
		init_all(&all);
		handle_signal(1);
		prompt = display_prompt();
		input = readline(prompt);
		all.input = input;
		ft_free(prompt);
		if (all.input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(all.input);
		ft_commands(&all);
		free(input);
		//free_all(&all);
	}
	return (0);
}
