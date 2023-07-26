/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/26 13:02:28 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_commands(char **envp, t_data *all)
{
	int		status;
	t_cmd	*curr;
	pid_t	id;

	if (ft_strcmp(all->input, "") != 0)
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
		handle_signal(2, all); //NOT SURE IF THIS IS CORRECT PLACE(1);
		if (id == -1)
			exit(WEXITSTATUS(status));
		if (id == 0)
		{
			//handle_signal(2, all); //NOT SURE IF THIS IS CORRECT PLACE(2);
			if (curr && curr->next == NULL)
				last_cmd_child(curr, envp, all);
			else
			{
				while (curr && curr->next != NULL)
				{
					cmd_child(curr, envp, all);
					if (!curr->next)
						exit(WEXITSTATUS(status));
					curr = curr->next;
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
