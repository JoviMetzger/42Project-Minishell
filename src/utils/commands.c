/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 17:25:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	ft_fork_procces(char **envp, t_data *all, t_cmd	*curr, int status)
// {
// 	if (curr && curr->next == NULL)
// 		last_cmd_child(curr, envp, all);
// 	else
// 	{
// 		while (curr && curr->next != NULL)
// 		{
// 			cmd_child(curr, envp, all);
// 			if (!curr->next)
// 				exit(WEXITSTATUS(status));
// 			curr = curr->next;
// 		}
// 		if (curr)
// 			last_cmd_child(curr, envp, all);
// 		all->status = WEXITSTATUS(status);
// 		exit(WEXITSTATUS(status));
// 	}
// }

// static void	ft_fork(char **envp, t_data *all, t_cmd	*curr)
// {
// 	int		status;
// 	pid_t	id;

// 	status = 0;
// 	id = fork();
// 	handle_signal(2, all);
// 	if (id == -1)
// 		exit(WEXITSTATUS(status));
// 	if (id == 0)
// 	{
// 		ft_fork_procces(envp, all, curr, status);
// 	}
// 	else
// 	{
// 		protect_waitpid(id, &status, 0);
// 		all->status = WEXITSTATUS(status);
// 		free_cmd(all);
// 	}
// }

/*
 * !!!NOT DONE!!!
 */
void	ft_commands(char **envp, t_data *all)
{
	t_cmd	*curr;

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
		if (curr && !curr->next)
			last_cmd_child(curr, envp, all);
		else if (curr && curr->next)
		{
			while (curr)
			{
				cmd_child(curr, envp, all);
				if (!curr->next)
					return ;
				curr = curr->next;
			}
		}
		//here should waitpid
		//ft_fork(envp, all, curr);
	}
}
