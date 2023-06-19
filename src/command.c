/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/19 18:33:03 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **input, char **envp, t_history *data)
{
	char *cmd[2];
	//t_token *token;
	
	cmd[0] ="wc";
	cmd[1] = NULL;
	if (ft_strcmp(input[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(input[0], "env") == 0)
		printf("history\n");
	else if (ft_strcmp(input[0], "history") == 0)
		printf_history(data);
	else if (ft_strcmp(input[0], "ls") == 0)
	{
		/* token = tokenized(input[0]);
		cmd = token_to_cmd(&token);
		run_cmd(cmd->words, envp); */
		
		execve("/usr/bin/", cmd, envp);
		printf("lol\n");
	}
}


