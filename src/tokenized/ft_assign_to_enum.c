/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_assign_to_enum.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/01 20:55:54 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_input(t_token *curr)
{
	if (curr->prev->type == INPUT_RE && curr->type == WORD)
		curr->type = INFILE;
	else if (curr->prev->type == OUTPUT_RE && curr->type == WORD)
		curr->type = OUTFILE;
	else if (curr->prev->type == APPEND_RE && curr->type == WORD)
		curr->type = APPFILE;
	else if (curr->prev->type == HERE_DOC && curr->type == WORD)
		curr->type = DELIMI;
}

void	ft_assign_to_enum(t_token *curr)
{
	if (!curr->str || curr->type == SQUO)
		curr->type = WORD;
	else if (curr->type == EMPTY)
	{
		if (ft_strcmp(curr->str, "|") == 0)
			curr->type = PIPE;
		else if (ft_strcmp(curr->str, "<") == 0)
			curr->type = INPUT_RE;
		else if (ft_strcmp(curr->str, ">") == 0)
			curr->type = OUTPUT_RE;
		else if (ft_strcmp(curr->str, "<<") == 0)
			curr->type = HERE_DOC;
		else if (ft_strcmp(curr->str, ">>") == 0)
			curr->type = APPEND_RE;
	}
	else if (curr->prev)
	{
		ft_input(curr);
	}
	if (!curr->next)
		return ;
}
