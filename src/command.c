/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/29 17:20:36 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **envp, t_data *all)
{
	t_cmd *curr;
	pid_t	id;
	(void)envp;
	if (ft_strcmp(all->input, "exit") == 0)
		exit(0);
	else if (ft_strcmp(all->input, "history") == 0)
		printf_history(all->history);
	else
	{
		tokenized(all);
		token_to_cmd(all);
		free_token(all);
		curr = all->cmd;
		id = fork();
		if (id == 0)
		{
			if (curr->next == NULL)
			{
				//redi_in(curr);
				//redi_out(curr);
				last_cmd_child(curr, envp);
				return ;
			}
			while (curr->next != NULL)
			{
				cmd_child(curr, envp);
				curr=curr->next;
			}
			//redi_in(curr);
			//redi_out(curr);
			last_cmd_child(curr, envp);
		}
		else
		{
			waitpid(id, NULL, 0);
			free_cmd(all);
		}
		
	}
}


