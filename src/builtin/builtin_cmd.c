/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 14:22:31 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/25 13:12:57 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* is_builtin_cmd();
 *	- The function checks if the given command is a built-in command.
 *	- If it's a built-in command, it will be executed using exec_builtin_cmd().
 *	- Otherwise, the execution will skip the built-in handling.
 */
int	is_builtin_cmd(char *command)
{
	if ((ft_strcmp(command, "cd") == 0))
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
	return (0);
}

/* exec_builtin_cmd();
 *	- char **input: the whole input command line, split into a char**;
 * 	- t_data *data: the main struct;
 *
 *	- This function checks for specific keywords using ft_strcmp() and 
 *	  executes the corresponding behavior for each built-in command.
 *	- It saves the return value in 'data->status' to keep track of the correct 
 *	  exit value ($?).
 *	- Returns true if the command is a built-in and successfully executed, 
 *	  false otherwise (for external commands).
 */
bool	exec_builtin_cmd(char **input, t_data *data)
{
	if (ft_strcmp(input[0], "cd") == 0)
		data->status = ft_cd(input[1], data);
	else if (ft_strcmp(input[0], "echo") == 0)
		data->status = ft_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		data->status = ft_env(data);
	else if (ft_strcmp(input[0], "export") == 0)
		data->status = ft_export(input, data);
	else if (ft_strcmp(input[0], "pwd") == 0)
		data->status = ft_pwd();
	else if (ft_strcmp(input[0], "unset") == 0)
		data->status = ft_unset(input, &data->env);
	else if (ft_strcmp(input[0], "exit") == 0)
		data->status = ft_exit(input, data);
	else
		return (false);
	return (true);
}
