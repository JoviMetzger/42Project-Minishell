/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 13:54:49 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/16 10:57:00 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*display_prompt(void)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = ft_strjoin("minishell", RED);
	tmp = ft_strjoin(tmp2, " ➔");
	ft_free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	ft_free(tmp);
	tmp = ft_strjoin(tmp2, "  ");
	ft_free(tmp2);
	return (tmp);
}
