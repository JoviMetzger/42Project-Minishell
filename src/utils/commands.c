/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 13:47:46 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd *curr;
	pid_t	id;
	
	if (ft_strcmp(all->input, "history") == 0)
		printf("history");//printf_history(all->history);//
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all);
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
				//dup2(stdin, 0);
				//dup2(stdout, 1);
				//close(stdin);
				//close(stdout);
				if (!curr->next)
					exit(0);
				curr=curr->next;
			}
			if (curr)
				last_cmd_child(curr, envp);
			/* dup2(stdin, 0);
			dup2(stdout, 1);
			close(stdin);
			close(stdout); */
			exit(0);
		}
		else
		{
			waitpid(id, NULL, 0);
			free_cmd(all);
		}
	}
}
