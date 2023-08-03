/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:50:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/07/04 16:13:10 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_2dstr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while(token != NULL)
	{
		tmp = token;
		if(tmp->str)
			free(tmp->str);
		free(tmp);
		if (!token->next)
			return ;
		token = token->next;
	}
}

void	 free_cmd(t_data *all)
{
	t_cmd	*tmp;

	while(all->cmd != NULL)
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

//free_history