/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/04 13:17:26 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd *curr;
	pid_t	id;
	
	if (ft_strcmp(all->input, "history") == 0)
		printf("history\n");
	else if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all);
		token_to_cmd(all);
		free_token(all);
		curr = all->cmd;
		id = fork();
		if (id == 0)
		{
			if (curr && curr->next == NULL)
			{
				last_cmd_child(curr, envp);
				return ;
			}
			while (curr && curr->next != NULL)
			{
				cmd_child(curr, envp);
				curr=curr->next;
			}
			last_cmd_child(curr, envp);
		}
		else
		{
			waitpid(id, NULL, 0);
			free_cmd(all);
		}
	}
}
