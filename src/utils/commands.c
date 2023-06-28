/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:42:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/28 11:03:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_builtin_cmd(char *command)
{
    if (ft_strcmp(command, "cd") == 0) 
        return (1);
    if (ft_strcmp(command, "echo") == 0) 
        return (1);
    if (ft_strcmp(command, "env") == 0) 
        return (1);
    if (ft_strcmp(command, "export") == 0) 
        return (1);
    if (ft_strcmp(command, "pwd") == 0) 
        return (1);
    if (ft_strcmp(command, "unset") == 0) 
        return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "history") == 0)
		return (1);
    return (0);
}

void    exec_builtin_cmd(char **input) //, t_data *all)
{
   //(void)envp;
	if (ft_strcmp(input[0], "cd") == 0) 
        ft_cd(input);
    else if (ft_strcmp(input[0], "echo") == 0) 
        ft_echo(input);
    // else if (ft_strcmp(input[0], "env") == 0) 
    //     ft_env(all->env);
    // else if (ft_strcmp(input[0], "export") == 0) 
    //     ft_export(input);
    else if (ft_strcmp(input[0], "pwd") == 0) 
        ft_pwd();
    // else if (ft_strcmp(input[0], "unset") == 0) 
    //     ft_unset(input);
	else if (ft_strcmp(input[0], "exit") == 0)
		ft_exit(input); 
	// else if (ft_strcmp(*input, "history") == 0)
	// 	printf_history(all->history);
}

void ft_commands(char **envp, t_data *all)
{
	t_cmd *curr;
	pid_t	id;
	
	if (ft_strcmp(all->input, "history") == 0)
		printf_history(all->history);
	// if ((is_builtin_cmd(all->input)) == 1) 
	// 	exec_builtin_cmd(&all->input, all);
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
				last_cmd_child(curr, envp);
				return ;
			}
			while (curr->next != NULL)
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