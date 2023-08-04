/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:50:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 12:32:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* print_error();
 *	- Parameters:
 *	  - char *str: A custom error message to be displayed 
 *		(can be NULL for system errors);
 *	  - int errcode: The error code to exit the program with;
 *
 *	- The function displays an error message and exit the program 
 *	  with the specified error code.
 *	- If 'errcode' is 127, it displays "command not found" 
 *	  along with the 'str'.
 *	- For other error codes, it displays the 'str' followed 
 *	  by the system error message.
 */
void	print_error(char *str, int errcode)
{
	if (errcode == 127)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(errcode);
	}
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(errno);
	}
}

/* free_2dstr();
 *	- Parameters:
 *	  - char **str: The 2D string array to be freed;
 *
 *	- Free memory occupied by a NULL-terminated 
 *	  array of strings (2D string array).
 *	- This function iterates through each string 
 *	  in 'str' and then frees 'str' itself.
 */
void	free_2dstr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
}

int	print_error_noexit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (errno);
}

/* free_token();
 *	- Parameters:
 *	  - t_token *token: The head of the linked list of 't_token' structures;
 *
 *	- Free memory occupied by a linked list of 't_token' structures.
 *	- This function iterates through each node in the linked list 
 *	  and frees its memory.
 */
void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		free(tmp->str);
		free(tmp);
		if (!token->next)
			return ;
		token = token->next;
	}
}

/* free_cmd();
 *	- Parameters:
 *	  - t_data *all: A pointer to the 't_data' structure containing 
 *		the head of the linked list;
 *	- Free memory occupied by a linked list of 't_cmd' structures.
 *	- This function iterates through each node in the linked list 
 *	  and frees its memory.
 *	- It also calls 'free_2dstr()' and 'free_token()' 
 *	  to free memory in 't_cmd' structure.
 */
void	free_cmd(t_data *all)
{
	t_cmd	*tmp;

	while (all->cmd != NULL)
	{
		tmp = all->cmd;
		free_2dstr(tmp->words);
		free_token(tmp->redi);
		free(tmp);
		if (!all->cmd->next)
			return ;
		all->cmd = all->cmd->next;
	}
}
