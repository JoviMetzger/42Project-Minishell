/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/20 09:40:58 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **input, char **envp, t_history *data)
{
	t_cmd *cmd;
	t_token *token;
	

	if (ft_strcmp(input[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(input[0], "env") == 0)
		printf("history\n");
	else if (ft_strcmp(input[0], "history") == 0)
		printf_history(data);
	else
	{
		token = tokenized(input[0]);
		cmd = token_to_cmd(&token);
		run_cmd(cmd, envp);//create child in here so it will not exit after finished one cmd
	}
}


