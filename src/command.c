/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/22 12:22:20 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char *input, char **envp, t_history *data)
{
	t_cmd *cmd;
	t_cmd *curr;
	t_token *token;
	pid_t	id;

	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	else if (ft_strcmp(input, "history") == 0)
		printf_history(data);
	else
	{
		token = tokenized(input);
		cmd = token_to_cmd(&token);
		curr = cmd;
		id = fork();
		if (id == 0)
		{
			cmd_child(curr, envp);
			while (curr->next != NULL)
			{
				curr=curr->next;
				cmd_child(curr, envp);
			}
			last_cmd_child(curr, envp);
		}
	}
}


