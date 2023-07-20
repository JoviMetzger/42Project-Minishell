/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/19 11:51:37 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd 	*curr;
	pid_t	id;
	int		status;

	if (ft_strcmp(all->input, "history") == 0)
		printf("HISTORY\n");
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all, envp);
		token_to_cmd(all);
		free_token(all->token);
		curr = all->cmd;
		if (is_builtin_cmd(all->cmd->words[0]) == 1)
		{
			exec_builtin_cmd(all->cmd->words, all);
			return ;
		}
		id = fork();
		if (id == -1)
			exit(WEXITSTATUS(status));
		if (id == 0)
		{
			signal(SIGINT, child_signals);
			if (curr && curr->next == NULL)
				last_cmd_child(curr, envp, all);
			else
			{
				while (curr && curr->next != NULL)
				{
					cmd_child(curr, envp, all);
					if (!curr->next)
						exit(WEXITSTATUS(status));
					curr=curr->next;
				}
				if (curr)
					last_cmd_child(curr, envp, all);
				all->status = WEXITSTATUS(status);	
				exit(WEXITSTATUS(status));
			}
		}
		else
		{
			protect_waitpid(id, &status, 0);
			all->status = WEXITSTATUS(status);
			free_cmd(all);
		}
	}
}
