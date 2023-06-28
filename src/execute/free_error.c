/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:50:27 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/23 07:53:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(void)
{
	printf("error!\n");
	exit(1);
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

void	free_token(t_data *all)
{
	t_token	*tmp;

	while(all->token != NULL)
	{
		tmp = all->token;
		all->token = all->token->next;
		free(tmp);
	}
}



void	 free_cmd(t_data *all)
{
	t_cmd	*tmp;

	while(all->cmd != NULL)
	{
		tmp = all->cmd;
		free_2dstr(tmp->words);
		all->cmd = all->cmd->next;
		free(tmp);
	}
}

//free_history