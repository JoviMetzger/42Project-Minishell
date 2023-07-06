/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 15:51:09 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd *curr;
	pid_t	id;

	if (ft_strcmp(all->input, "exit") == 0)
		exit(0);
	//else if (ft_strcmp(all->input, "history") == 0)
	//	printf_history(all->history);
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		curr = all->cmd;
		id = fork();
		if (id == 0)
		{
			if (curr && curr->next == NULL)
			{
				last_cmd_child(curr, envp);
				exit(0);
			}
			while (curr && curr->next != NULL)
			{
				cmd_child(curr, envp);
				if (!curr->next)
					exit(0);
				curr=curr->next;
			}
			if (curr)
				last_cmd_child(curr, envp);
			exit(0);
		}
		else
		{
			waitpid(id, NULL, 0);
			free_cmd(all);
		}
	}
}


