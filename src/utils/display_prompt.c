/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 13:54:49 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/30 12:36:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *ft_color(char *str, char *color)
{
    return (ft_strjoin(str, color));
}

char    *display_prompt()
{
    char *tmp2;
    char *tmp;
    char *color;    

    tmp2 = ft_strjoin(NULL, "minishell");
	color = ft_color(tmp2, RED);
	tmp = ft_strjoin(color, " ➔");
	ft_free(tmp2);
	ft_free(color);
	color = ft_color(tmp, RESET);
	tmp2 = ft_strjoin(color, "  ");
	ft_free(tmp);
	ft_free(color);
	return (tmp2);
}
