/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 13:54:49 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/27 15:39:49 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    display_prompt()
{
    printf("minishell" RED BOLD " ➔  " RESET);
}
