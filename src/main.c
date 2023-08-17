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

static void	first_check(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" \
				RED "!\n" RESET);
		exit(0);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data all;

	char	*prompt;

	first_check(argc, argv);
	all.env = init_env(envp);
	all.status = 0;
	while (1)
	{
		all.tmp_out = dup(1);
		all.tmp_fd = dup(0);
		//all.tmp_in = dup(0);
		protect_dup2(all.tmp_out, 1, &all);
		protect_dup2(all.tmp_fd, 0, &all);
		all.cmd = NULL;
		all.token = NULL;
		all.id = NULL;
		prompt = display_prompt();
		// handle_signal(1, &all);
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
		//exit(0);//test leaks
	}
	return (0);
}