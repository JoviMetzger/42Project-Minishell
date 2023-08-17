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

void	print_error(char *str, int errcode, t_data *all)
{
	if (errcode == 127 && str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		//free_all(all);
		exit(errcode);
	}
	if (!str)
	{
		ft_putstr_fd("fork: Resource temporarily unavailable", 2);
		ft_putstr_fd("\n", 2);
		all->status = 1;
		//free_all(all);
		return ;
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free_all(all);
	if (errcode == 1 || errcode == 126)
		exit(errcode);
	else
		exit(errno);
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

	while (token != NULL)
	{
		tmp = token;
		if (tmp->str)
			free(tmp->str);
		if (token->next)
		{
			token = token->next;
			free(tmp);
		}
		else
		{
			free(tmp);
			return ;
		}
	}
}

void	free_cmd(t_data *all)
{
	t_cmd	*tmp;

	while (all->cmd != NULL)
	{
		tmp = all->cmd;
		free_2dstr(tmp->words);
		free_token(tmp->redi);
		if (all->cmd->next)
		{
			all->cmd = all->cmd->next;
			free(tmp);
		}
		else
		{
			free(tmp);
			return ;
		}
	}
}

void	free_all(t_data *all)
{
	if (all->cmd)
		free_cmd(all);
	if (all->input)
		free(all->input);
	if (all->id)
		free(all->id);
}
