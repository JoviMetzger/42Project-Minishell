/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/29 09:51:22 by yizhang       ########   odam.nl         */
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
				if (curr->infile != -1)
					dup2(curr->infile,0);
				if (curr->outfile != -1)
					dup2(curr->outfile,1);
				last_cmd_child(curr, envp);
				if (curr->infile != -1)
					close(curr->infile);
				if (curr->outfile != -1)
					close(curr->outfile);
				return ;
			}
			while (curr->next != NULL)
			{
				if (curr->infile != -1)
					dup2(curr->infile,0);
				if (curr->outfile != -1)
					dup2(curr->outfile,1);
				cmd_child(curr, envp);
				if (curr->infile != -1)
					close(curr->infile);
				if (curr->outfile != -1)
					close(curr->outfile);
				curr=curr->next;
			}
			if (curr->infile != -1)
				dup2(curr->infile,0);
			if (curr->outfile != -1)
				dup2(curr->outfile,1);
			last_cmd_child(curr, envp);
			if (curr->infile != -1)
				close(curr->infile);
			if (curr->outfile != -1)
				close(curr->outfile);
			
		}
		else
		{
			waitpid(id, NULL, 0);
			free_cmd(all);
		}
		
	}
}


