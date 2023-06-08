/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/07 08:31:08 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_commands(char **input, char **envp, t_history *data)
{
	(void)envp;
	if (ft_strcmp(input[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(input[0], "env") == 0)
		printf("history\n");
	else if (ft_strcmp(input[0], "history") == 0)
		printf_history(data);
}


