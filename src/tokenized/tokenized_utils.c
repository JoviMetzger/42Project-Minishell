/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 15:15:27 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/31 15:21:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_type_break(t_token *curr)
{
	if (!curr->next || (curr->next && (curr->next->type == SPACES
				|| curr->next->type == PIPE 
				|| curr->next->type == INPUT_RE
				|| curr->next->type == OUTPUT_RE 
				|| curr->next->type == HERE_DOC
				|| curr->next->type == APPEND_RE)))
		return (1);
	return (0);
}
